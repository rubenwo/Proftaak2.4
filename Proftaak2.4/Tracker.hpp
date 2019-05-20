#ifndef TRACKER_HPP
#define TRACKER_HPP
#include <functional>
#include <array>

#define TRACKER_DEBUG true
#define HANDS_AMOUNT 2

struct hand
{
	int id, x, y;
};


class HandTracker
{
private:
	int width, height;
	std::array<hand, HANDS_AMOUNT> hands;

	void track(const std::function<void(std::array<hand, HANDS_AMOUNT>)>& callback);
	void translate_coordinates();

public:
	HandTracker(int, int);
	~HandTracker();

	void resize(int, int);
	void start_tracking(const std::function<void(std::array<hand, HANDS_AMOUNT>)>& callback);
};


#endif
