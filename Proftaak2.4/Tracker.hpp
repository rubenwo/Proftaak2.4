#ifndef TRACKER_HPP
#define TRACKER_HPP
#include <functional>

class Hand
{
private:
	int id;
	std::pair<int, int> position;
public:
	Hand();
	Hand
	(int);
	~Hand();

	int getId();
	int getX();
	int getY();
	void setX(int);
	void setY(int);
};


class HandTracker
{
private:
	int width, height;
	Hand hands[2];
	std::function<void(Hand [2])> callback;
	void track();

public:
	HandTracker(int, int);
	~HandTracker();

	void set_callback(const std::function<void(Hand [])>& callback);
	void start_tracking();
};


#endif
