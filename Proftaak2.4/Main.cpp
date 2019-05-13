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

cv::Ptr<cv::Tracker> createTrackerByName(cv::String name)
{
	cv::Ptr<cv::Tracker> tracker;

	if (name == "KCF")
		tracker = cv::TrackerKCF::create();
	else if (name == "TLD")
		tracker = cv::TrackerTLD::create();
	else if (name == "BOOSTING")
		tracker = cv::TrackerBoosting::create();
	else if (name == "MEDIAN_FLOW")
		tracker = cv::TrackerMedianFlow::create();
	else if (name == "MIL")
		tracker = cv::TrackerMIL::create();
	else if (name == "GOTURN")
		tracker = cv::TrackerGOTURN::create();
	else if (name == "MOSSE")
		tracker = cv::TrackerMOSSE::create();
	else if (name == "CSRT")
		tracker = cv::TrackerCSRT::create();
	else
		CV_Error(cv::Error::StsBadArg, "Invalid tracking algorithm name\n");

	return tracker;
}
int main(int argc, char** argv) {
	// show help

	// set the default tracking algorithm
	std::string trackingAlg = "MOSSE";

	// create the tracker
	MultiTracker trackers;

	// container of the tracked objects
	vector<Rect2d> objects;

	// set input video
	VideoCapture cap(1);

	Mat frame;

	// get bounding box
	cap >> frame;
	vector<Rect> ROIs;
	selectROIs("tracker", frame, ROIs);

	//quit when the tracked object(s) is not provided
	if (ROIs.size() < 1)
		return 0;

	// initialize the tracker
	std::vector<Ptr<Tracker> > algorithms;
	for (size_t i = 0; i < ROIs.size(); i++)
	{
		algorithms.push_back(createTrackerByName(trackingAlg));
		objects.push_back(ROIs[i]);
	}

	trackers.add(algorithms, frame, objects);

	// do the tracking
	printf("Start the tracking process, press ESC to quit.\n");
	for (;; ) 
	{
		// get frame from the video
		cap >> frame;

		// stop the program if no more images
		if (frame.rows == 0 || frame.cols == 0)
			break;

		//update the tracking result
		trackers.update(frame);

		// draw the tracked object
		for (unsigned i = 0; i < trackers.getObjects().size(); i++)
			rectangle(frame, trackers.getObjects()[i], Scalar(255, 0, 0), 2, 1);

		// show image with the tracked object
		imshow("tracker", frame);

		//quit on ESC button
		if (waitKey(1) == 27)break;
	}

}
