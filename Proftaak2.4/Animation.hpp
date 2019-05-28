#ifndef ANIMATION_HPP
#define ANIMATION_HPP
class GameObject;

class Animation
{
protected:
	GameObject* gameObject;
	bool drawAllowed = true;
public:
	Animation();
	~Animation();
	virtual void update(float elapsedTime) {};
	virtual void draw() = 0;
	inline void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
	// Starts the animation
	inline void animate(bool start) { drawAllowed = start; }
};
#endif