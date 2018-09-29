#include "opencv2/opencv.hpp"
#include <iostream>  
#include <stdio.h>
#include <stdlib.h>
using namespace cv;  
using namespace std; 
String face_cascade_name = "haarcascade_frontalcatface.xml";
CascadeClassifier cat_cascade;
int main (int argc, char **argv)  
{  
	std::vector<Rect> faces;
	Mat frame_gray;
	VideoCapture capture(0);
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	Mat frame;
	if (!cat_cascade.load(face_cascade_name)) { printf("--(!)Error loading cat cascade\n"); return -1; };
	float threshold = 0;
	int k = 0;
	while (1) {
		if (k < 10)
			k++;
		else
			k = 0;
		capture >> frame;
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);
		cat_cascade.detectMultiScale(frame_gray, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
		for (vector<Rect>::const_iterator iter = faces.begin(); iter != faces.end(); iter++)
		{
			rectangle(frame, *iter, Scalar(0, 0, 255), 2, 8);
			threshold += 1;
		}
		threshold = threshold / 2;
		printf("%f %d\n", threshold, k);
		imshow("MyTest", frame);
		if (threshold > 0.999&&k%10==0)
		{
			imwrite("cat.jpg", frame);
			printf("cat\n", threshold);
			system("echo \"cat face\" | mutt -s \"RaspberryCamera\" news@news.ickey.cn -a cat.jpg");
		}
		waitKey(1);
	}
		
	return 0;
}  
