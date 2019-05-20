#ifndef TRACKER_HPP
#define TRACKER_HPP
#include <functional>
#include <array>

#define TRACKER_DEBUG true

struct hand
{
	int id, x, y;
};


class HandTracker
{
private:
	int width, height;
	std::array<hand, 2> hands;

	void track(const std::function<void(std::array<hand, 2>)> &callback);
	void translate_coordinates();

public:
	HandTracker(int, int);
	~HandTracker();

	void resize(int, int);
	void start_tracking(const std::function<void(std::array<hand, 2>)> &callback);
};


#endif
