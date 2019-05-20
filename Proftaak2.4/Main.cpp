#include "Tracker.hpp"
#include <iostream>

void callback(hand* hands)
{
	for (int i = 0; i < 2; i++)
	{
		std::cout << hands[i].id;
	}
}

int main(int argc, char** argv)
{
	HandTracker tracker(1920, 1080);

	tracker.start_tracking(callback);
	return 0;
}
