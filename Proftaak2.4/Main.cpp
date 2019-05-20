#include "Tracker.hpp"
#include <iostream>
#include <atomic>
#include <opencv2/highgui.hpp>

std::atomic<std::array<hand, 2>> atomic_hands;

void callback(std::array<hand, 2> hands)
{
	atomic_hands = hands;
}

int main(int argc, char** argv)
{
	HandTracker tracker(1920, 1080);

	tracker.start_tracking(callback);
	while (1)
	{
		cv::waitKey(1000);

		for (int i = 0; i < atomic_hands._My_val.size(); i++)
		{
			std::cout << "ID: " << atomic_hands._My_val[i].id << " X: " << atomic_hands._My_val[i].x << " Y: " <<
				atomic_hands._My_val[i].y << std::endl;
		}
	}
	return 0;
}
