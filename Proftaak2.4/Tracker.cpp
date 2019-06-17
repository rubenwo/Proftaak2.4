#include "Tracker.hpp"
#include <iostream>
#include <opencv2/tracking/tracker.hpp>
#include <thread>

#define camera_width 1240
#define camera_height 720
const auto element = getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(4, 4));

//compareContourAreas
//It returns a True when the i is smaller than j and it returns false when i is bigger than 
//parm @ countour1: the first contour that needs to be compared
//parm @ countour2: the second contour that needs to be compared
bool compareContourAreas(std::vector<cv::Point> contour1, std::vector<cv::Point> contour2)
{
	double i = fabs(contourArea(cv::Mat(contour1)));
	double j = fabs(contourArea(cv::Mat(contour2)));
	return (i < j);
}

inline float map(float input, float srcRangeLow, float srcRangeHigh, float dstRangeLow, float dstRangeHigh)
{
	return dstRangeLow + (input - srcRangeLow) * (dstRangeHigh - dstRangeLow) / (srcRangeHigh - srcRangeLow);
}

//trackByColor
//It sets the color you want to search
// It checks if the webcam is active and sends a feed
//Shows the feed with contours
//If it can find a webcam feed it will print a error
//Param @ callback: it calls the callback with an array of hands
void HandTracker::trackByColor(const std::function<void(std::array<hand, HANDS_AMOUNT>)>& callback)
{
	const auto color_sensitivity = 15;

	//const auto orange_lower = cv::Scalar(10, 150, 20);
	//const auto orange_upper = cv::Scalar(20, 255, 255);

	//const auto blue_lower = cv::Scalar(100, 55, 55);
	//const auto blue_upper = cv::Scalar(130, 255, 255);

	const auto green_lower = cv::Scalar(60 - color_sensitivity, 100, 100);
	const auto green_upper = cv::Scalar(60 + color_sensitivity, 255, 255);


	cv::UMat frame, scaled_frame, flipped_frame, blurred, hsv;
	cv::UMat orange_mask;

	std::vector<cv::Mat> contours;
	std::vector<cv::Vec4i> hierarchy;


	cv::useOpenVX();

	// Open video resource
	cv::VideoCapture vcap(0);

	if (!vcap.isOpened())
	{
		std::cout << "Cannot open the video" << std::endl;
		return;
	}
	// Create structuring element once
	const auto element = getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(4, 4));

	// processing loop
	for (;;)
	{
		contours.clear();
		hierarchy.clear();

		if (vcap.read(frame))
		{
			//-------PRE-PROCESSING--------//
			cv::resize(frame, scaled_frame, cv::Size(camera_width, camera_height));
			//Resize the image to a easier resolution.
			cv::flip(scaled_frame, flipped_frame, +1);
			cv::GaussianBlur(flipped_frame, blurred, cv::Size(13, 13), 0); //Blur the image in order to remove noise.
			cv::cvtColor(blurred, hsv, CV_BGR2HSV); //Convert the blurred image to HSV.

			cv::inRange(hsv, green_lower, green_upper, orange_mask); //Create a binary output with only the blue's.

			//Erode & Dilate to remove smaller objects
			cv::erode(orange_mask, orange_mask, element, cv::Point(-1, -1), 4);
			cv::dilate(orange_mask, orange_mask, element, cv::Point(-1, -1), 4);

			//-------OBJECT-DETECTION------//
			cv::findContours(orange_mask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

			std::sort(contours.begin(), contours.end(), compareContourAreas);
			//Find the contours of the blue objects.
			std::vector<cv::Moments> mu(contours.size());

			for (auto i = 0; i < mu.size(); i++)
			{
				mu[i] = cv::moments(contours[i], false); //Add the contours to the moments vector
			}

			// get the centroid of the objects.
			std::vector<cv::Point2f> mc(mu.size());
			for (auto i = 0; i < mc.size(); i++)
			{
				mc[i] = cv::Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
			}
			if (hands.size() < mc.size())
			{
				for (auto i = 0; i < hands.size(); i++)
				{
					hands[i].x = map(mc[i].x, 0, camera_width, -1, 1);
					hands[i].y = -map(mc[i].y, 0, camera_height, -1, 1);
				}
			}
			else
			{
				for (auto i = 0; i < mc.size(); i++)
				{
					hands[i].x = map(mc[i].x, 0, camera_width, -1, 1);
					hands[i].y = -map(mc[i].y, 0, camera_height, -1, 1);
				}
			}

			if (TRACKER_DEBUG)
			{
				// draw the contours of the objects.
				for (auto i = 0; i < contours.size(); i++)
				{
					cv::Scalar color = cv::Scalar(0, 0, 255); // B G R values
					drawContours(flipped_frame, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
					circle(flipped_frame, mc[i], 4, color, -1, 8, 0);
				}
				cv::imshow("Contours", flipped_frame); //Finally show the image with the contours
			}
			callback(hands);
		}
		else
		{
			std::cout << "couldn't read frame" << std::endl;
			break;
		}
		if (cv::waitKey(1) == 27)
		{
			break;
		}
	}
}

void findCentroid(std::vector<cv::Mat>& contours, float* x, float* y)
{
	if (!contours.empty())
	{
		std::sort(contours.begin(), contours.end(), compareContourAreas);
		cv::Moments mu = cv::moments(contours[0], false);
		cv::Point2f mc = cv::Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
		*x = map(mc.x, 0, camera_width, -1, 1);
		*y = -map(mc.y, 0, camera_height, -1, 1);
	}
}

void HandTracker::resize(int, int)
{
}

std::vector<cv::Mat> blue_contours, green_contours;
std::vector<cv::Vec4i> blue_hierarchy, green_hierarchy;

void HandTracker::track(const std::function<void(std::array<hand, HANDS_AMOUNT>)>& callback)
{
	hand left = {0, 0, 0};
	hand right = {1, 0, 0};

	cv::useOpenVX();

	cv::UMat frame, scaled_frame, flipped_frame, blurred, hsv;
	cv::VideoCapture vcap(1);
	for (;;)
	{
		if (vcap.read(frame))
		{
			//-------PRE-PROCESSING--------//
			cv::resize(frame, scaled_frame, cv::Size(camera_width, camera_height));
			//Resize the image to a easier resolution.
			cv::flip(scaled_frame, flipped_frame, +1);
			cv::GaussianBlur(flipped_frame, blurred, cv::Size(13, 13), 0); //Blur the image in order to remove noise.
			cv::cvtColor(blurred, hsv, CV_BGR2HSV); //Convert the blurred image to HSV.

			trackBlue(hsv, &left);
			trackGreen(hsv, &right);

			//hands_.push_back(&left);
			//hands_.push_back(&right);
			hands[0] = left;
			hands[1] = right;
			callback(hands);


			if (TRACKER_DEBUG)
			{
				for (auto i = 0; i < green_contours.size(); i++)
				{
					cv::Scalar color = cv::Scalar(0, 0, 255); // B G R values
					drawContours(flipped_frame, green_contours, i, color, 2, 8, green_hierarchy, 0, cv::Point());
					//circle(flipped_frame, mc[i], 4, color, -1, 8, 0);
				}
				for (auto i = 0; i < blue_contours.size(); i++)
				{
					cv::Scalar color = cv::Scalar(0, 0, 255); // B G R values
					drawContours(flipped_frame, blue_contours, i, color, 2, 8, blue_hierarchy, 0, cv::Point());
					//circle(flipped_frame, mc[i], 4, color, -1, 8, 0);
				}
				cv::imshow("Contours", flipped_frame); //Finally show the image with the contours
			}
		}
		else
		{
			std::cout << "couldn't read frame" << std::endl;
			break;
		}
		if (cv::waitKey(1) == 27)
		{
			break;
		}
	}
}


void HandTracker::trackBlue(cv::UMat& hsv, hand* hand)
{
	blue_contours.clear();
	blue_hierarchy.clear();
	const auto blue_lower = cv::Scalar(78, 102, 77);
	const auto blue_upper = cv::Scalar(102, 255, 255);
	cv::UMat blue_mask;


	cv::inRange(hsv, blue_lower, blue_upper, blue_mask); //Create a binary output with only the blue's.

	//Erode & Dilate to remove smaller objects
	cv::erode(blue_mask, blue_mask, element, cv::Point(-1, -1), 4);
	cv::dilate(blue_mask, blue_mask, element, cv::Point(-1, -1), 4);

	//-------OBJECT-DETECTION------//
	cv::findContours(blue_mask, blue_contours, blue_hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	findCentroid(blue_contours, &hand->x, &hand->y);
}

void HandTracker::trackGreen(cv::UMat& hsv, hand* hand)
{
	green_contours.clear();
	green_hierarchy.clear();
	int color_sensitivity = 15;
	const auto green_lower = cv::Scalar(60 - color_sensitivity, 100, 100);
	const auto green_upper = cv::Scalar(60 + color_sensitivity, 255, 255);

	cv::UMat green_mask;


	cv::inRange(hsv, green_lower, green_upper, green_mask); //Create a binary output with only the blue's.

	//Erode & Dilate to remove smaller objects
	cv::erode(green_mask, green_mask, element, cv::Point(-1, -1), 4);
	cv::dilate(green_mask, green_mask, element, cv::Point(-1, -1), 4);

	//-------OBJECT-DETECTION------//
	cv::findContours(green_mask, green_contours, green_hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	findCentroid(green_contours, &hand->x, &hand->y);
}


HandTracker::HandTracker()
{
	for (auto i = 0; i < HANDS_AMOUNT; i++)
	{
		this->hands[i] = {i, -1, -1};
	}
}

HandTracker::~HandTracker()
{
}

/*//startTracking
//Starts a tracking thread
//Param @ callback: it calls the callback with an array of hands
void HandTracker::startTracking(const std::function<void(std::array<hand, HANDS_AMOUNT>)>& callback)
{
	callback(hands);
	std::thread tracking_thread(&HandTracker::trackByColor, this, callback);
	tracking_thread.detach();
}*/

void HandTracker::startTracking(const std::function<void(std::array<hand, HANDS_AMOUNT>)>& callback)
{
	callback(hands);
	std::thread tracking_thread(&HandTracker::track, this, callback);
	tracking_thread.detach();
}
