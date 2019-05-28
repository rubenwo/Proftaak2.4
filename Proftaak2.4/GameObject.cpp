#include "GameObject.h"
#include "DrawComponent.h"
#include "Animation.hpp"
#include <GL/freeglut.h>

GameObject::GameObject()
{
	this->sphere = CollisionSphere(&this->position.x, &this->position.y, 0.25);
}

GameObject::~GameObject()
{
}

void GameObject::addComponent(Component* component)
{
	component->setGameObject(this);
	components.push_back(component);

	if (!drawComponent)
		drawComponent = dynamic_cast<DrawComponent*>(component);
}

std::list<Component*> GameObject::getComponents()
{
	return components;
}

void GameObject::addAnimation(Animation* animation)
{
	animation->setGameObject(this);
	animations.push_back(animation);
}

std::list<Animation*> GameObject::getAnimations()
{
	return animations;
}


void GameObject::draw()
{
	if (!drawComponent)
		return;

	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	glScalef(scale.x, scale.y, scale.z);
	drawComponent->draw();
	for (auto& a : animations)
		a->draw();
	glPopMatrix();
}

void GameObject::update(float elapsedTime)
{
	for (auto& c : components)
		c->update(elapsedTime);
	for (auto& a : animations)
		a->update(elapsedTime);
}
