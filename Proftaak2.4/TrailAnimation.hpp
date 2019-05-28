#ifndef TRAIL_ANIMATION_HPP
#define TRAIL_ANIMATION_HPP

#include "Animation.hpp"
class TrailAnimation : public Animation
{
public:
	TrailAnimation();
	~TrailAnimation() {}

	//virtual void update(float elapsedTime) override;
	virtual void draw() override;
};

#endif // !TRAIL_ANIMATION_HPP

