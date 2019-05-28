#pragma once

#include <list>
#include "Vec.h"
#include "CollisionSphere.h"

class Component;
class DrawComponent;
class Animation;

class GameObject
{
	DrawComponent* drawComponent = nullptr;

	std::list<Component*> components;
	std::list<Animation*> animations;
public:
	GameObject();
	~GameObject();

	CollisionSphere sphere;
	Vec3f position;
	Vec3f rotation;
	Vec3f scale = Vec3f(1, 1, 1);


	void addComponent(Component* component);
	std::list<Component*> getComponents();
	void addAnimation(Animation* animation);
	std::list<Animation*> getAnimations();
	void update(float elapsedTime);
	void draw();

	template <class T>
	T* getComponent()
	{
		for (auto c : components)
		{
			T* t = dynamic_cast<T*>(c);
			if (t)
				return t;
		}
	}

	template <class T>
	void removeComponent()
	{
		components.remove_if([](Component* c)
		{
			T* t = dynamic_cast<T*>(c);
			return t != nullptr;
		});
	}

	template<class T>
	T* getAnimation()
	{
		for (auto a : animations)
		{
			T* t = dynamic_cast<T*>(a);
			if (t)
				return t;
		}
	}

	template<class T>
	void removeAnimation()
	{
		animations.remove_if([](Animation* a)
		{
			T* t = dynamic_cast<T*>(a);
			return t != nullptr;
		});
	}
};
