#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstring>
#include <ctime>
//#include "samples_utility.hpp"

using namespace std;
using namespace cv;


Scalar orange_lower, orange_upper, green_lower, green_upper;
Mat frame, blurred, hsv;
Mat greenMask, orangeMask;

void initColors()
{
	orange_lower = Scalar(20, 62, 99); //orange lower
	orange_upper = Scalar(50, 100, 100); //orange upper
	green_lower = Scalar(38, 200, 102); //green lower
	green_upper = Scalar(75, 255, 225); //green upper
}


int main(int argc, char** argv)
{
	initColors();

	VideoCapture cap(0); // Get camera

	if (!cap.isOpened())
	{
		cout << "Cannot open the video cam" << endl;
		return -1;
	}


	while (true)
	{
		vector<Mat> greenContours, orangeContours;
		vector<Vec4i> hierarchy;

		bool bSuccess = cap.read(frame);

		flip(frame, frame, ROTATE_180);

		if (!bSuccess)
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		GaussianBlur(frame, blurred, Size(11, 11), 0);
		cvtColor(blurred, hsv, COLOR_BGR2HSV);

		// Construct Mask for the green stuff
		inRange(hsv, green_lower, green_upper, greenMask);
		erode(greenMask, greenMask, NULL, Point(-1, -1), 2);
		dilate(greenMask, greenMask, NULL, Point(-1, -1), 2);

		// Construct Mask for the orange stuff
		inRange(hsv, orange_lower, orange_upper, orangeMask);
		erode(orangeMask, orangeMask, NULL, Point(-1, -1), 2);
		dilate(orangeMask, orangeMask, NULL, Point(-1, -1), 2);

		//	findContours(greenMask.clone(), greenContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		//	findContours(orangeMask.clone(), orangeContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		findContours(orangeMask.clone(), orangeContours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		if (!hierarchy.empty())
		{
			cout << "Hierarchy size: " << hierarchy.size() << endl;
		}

		if (!orangeContours.empty())
		{
			cout << "Found contours: " << orangeContours.size() << endl;
		}

		imshow("Original", frame);
		if (waitKey(30) == 27)
		{
			break;
		}
	}

	return 0;
}
