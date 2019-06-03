#ifndef TRACKER_HPP
#define TRACKER_HPP
#include <functional>
#include <array>

#define TRACKER_DEBUG true
#define HANDS_AMOUNT 2

struct hand
{
	int id;
	float x, y;
};


class HandTracker
{
private:
	std::array<hand, HANDS_AMOUNT> hands;

	void trackByColor(const std::function<void(std::array<hand, HANDS_AMOUNT>)>& callback);
	void trackByTracker(const std::function<void(std::array<hand, HANDS_AMOUNT>)>& callback);

public:
	HandTracker();
	~HandTracker();

	void resize(int, int);
	void startTracking(const std::function<void(std::array<hand, HANDS_AMOUNT>)>& callback);
};


#endif
