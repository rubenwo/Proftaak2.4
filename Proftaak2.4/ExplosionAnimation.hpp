#ifndef EXPLOSION_ANIMATION_HPP
#define EXPLOSION_ANIMATION_HPP

#include "Animation.hpp"
class ExplosionAnimation : public Animation
{
public:
	ExplosionAnimation();
	~ExplosionAnimation() {}

	virtual void draw() override;
	void explode();
};

#endif // !EXPLOSION_ANIMATION_HPP
