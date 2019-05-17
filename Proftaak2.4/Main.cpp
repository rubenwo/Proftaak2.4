#include "Tracker.hpp"

int main(int argc, char** argv)
{
	HandTracker tracker(1920, 1080);

	tracker.start_tracking();
	return 0;
}
