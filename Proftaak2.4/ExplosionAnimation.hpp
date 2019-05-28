#ifndef EXPLOSION_ANIMATION_HPP
#define EXPLOSION_ANIMATION_HPP

#include "Animation.hpp"
#include <vector>
#include "Vec.h"


class ExplosionAnimation : public Animation
{
public:
	ExplosionAnimation();
	~ExplosionAnimation() {}

	virtual void update(float elapsedTime) override;
	virtual void draw() override;
	void explode();
private:
	struct ExplosionParticle
	{
		Vec3f pos;
		Vec3f dir;
		Vec3f rot;
		float speed;
		ExplosionParticle(const Vec3f& pos, const Vec3f& dir, const Vec3f& rot, float speed)
			: pos(pos), dir(dir), rot(rot), speed(speed) {}
	};
	std::vector<ExplosionParticle> particles;
};



#endif // !EXPLOSION_ANIMATION_HPP
