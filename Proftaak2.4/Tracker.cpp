#include "Tracker.hpp"
#include <opencv2/highgui.hpp>
#include <iostream>
#include <opencv2/tracking/tracker.hpp>
#include <thread>

#define camera_width 1240
#define camera_height 720


float map(float input, float srcRangeLow, float srcRangeHigh, float dstRangeLow, float dstRangeHigh)
{
	return dstRangeLow + (input - srcRangeLow) * (dstRangeHigh - dstRangeLow) / (srcRangeHigh - srcRangeLow);
}

void HandTracker::track(const std::function<void(std::array<hand, HANDS_AMOUNT>)>& callback)
{
	const auto orange_lower = cv::Scalar(10, 150, 20);
	const auto orange_upper = cv::Scalar(20, 255, 255);

	cv::UMat frame, scaled_frame, flipped_frame, blurred, hsv;
	cv::UMat orange_mask;

	std::vector<cv::Mat> blue_contours;
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
		blue_contours.clear();
		hierarchy.clear();

		if (vcap.read(frame))
		{
			//-------PRE-PROCESSING--------//
			cv::resize(frame, scaled_frame, cv::Size(camera_width, camera_height));
			//Resize the image to a easier resolution.
			cv::flip(scaled_frame, flipped_frame, +1);
			cv::GaussianBlur(flipped_frame, blurred, cv::Size(13, 13), 0); //Blur the image in order to remove noise.
			cv::cvtColor(blurred, hsv, CV_BGR2HSV); //Convert the blurred image to HSV.

			cv::inRange(hsv, orange_lower, orange_upper, orange_mask); //Create a binary output with only the blue's.

			//Erode & Dilate to remove smaller objects
			cv::erode(orange_mask, orange_mask, element, cv::Point(-1, -1), 5);
			cv::dilate(orange_mask, orange_mask, element, cv::Point(-1, -1), 5);

			//-------OBJECT-DETECTION------//
			cv::findContours(orange_mask, blue_contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
			//Find the contours of the blue objects.
			std::vector<cv::Moments> mu(blue_contours.size());

			for (auto i = 0; i < blue_contours.size(); i++)
			{
				mu[i] = cv::moments(blue_contours[i], false); //Add the contours to the moments vector
			}

			// get the centroid of the objects.
			std::vector<cv::Point2f> mc(blue_contours.size());
			for (auto i = 0; i < blue_contours.size(); i++)
			{
				mc[i] = cv::Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
			}
			if (hands.size() < mc.size())
			{
				for (auto i = 0; i < hands.size(); i++)
				{
					hands[i].x = -map(mc[i].x, 0, camera_width, -1, 1);
					hands[i].y = -map(mc[i].y, 0, camera_height, -1, 1);
				}
			}
			else
			{
				for (auto i = 0; i < mc.size(); i++)
				{
					hands[i].x = -map(mc[i].x, 0, camera_width, -1, 1);
					hands[i].y = -map(mc[i].y, 0, camera_height, -1, 1);
				}
			}

			if (TRACKER_DEBUG)
			{
				// draw the contours of the objects.
				for (auto i = 0; i < blue_contours.size(); i++)
				{
					cv::Scalar color = cv::Scalar(0, 0, 255); // B G R values
					drawContours(flipped_frame, blue_contours, i, color, 2, 8, hierarchy, 0, cv::Point());
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


void HandTracker::startTracking(const std::function<void(std::array<hand, HANDS_AMOUNT>)>& callback)
{
	callback(hands);
	std::thread tracking_thread(&HandTracker::track, this, callback);
	tracking_thread.detach();
}
