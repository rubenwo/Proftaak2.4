#ifndef TRACKER_HPP
#define TRACKER_HPP
#include <functional>

struct hand
{
	int id, x, y;
};


class HandTracker
{
private:
	int width, height;
	hand hands[2];
	//std::function<void(hand[2])> callback;
	void track(const std::function<void(hand[])>& callback);

public:
	HandTracker(int, int);
	~HandTracker();

	//void set_callback(const std::function<void(hand[])>& callback);
	void start_tracking(const std::function<void(hand[])>& callback);
};


#endif
