#include <iostream>
#include "Level.h"
#include "GameObject.h"
#include "CubeComponent.h"
#include "MoveToComponent.h"
#include "StageComponent.h"
#include "ObjectModel.h"
#include "TrailAnimation.hpp"
#include <iostream>

#define OBJECT_OUT_OF_BOUNDS -4.0f

std::list<GameObject*> objects;
Texture *texturess;

bool isObjectOutOfBounds(GameObject* o);


Texture* texturess;

Level::Level(Texture* texture)
{
	texturess = texture;
}

Level::Level()
{

}

void Level::loadContent()
{
	//loadTextures();
	createRoom();
	createMovingCubeLeft(1);
	createMovingCubeRight(1);
}

void Level::loadTextures()
{
	texturess = new Texture("texture");
	texturess->initTextures();
}

void Level::draw()
{
	glRotatef(180, 1, 0, 0);
	for (const auto& o : objects)
		o->draw();
}

void Level::update(float deltaTime)
{
	std::list<GameObject*>::iterator itr = objects.begin();

	while (itr != objects.end())
	{
		auto o = (*itr);
		if (isObjectOutOfBounds(o))
		{
			itr = objects.erase(itr);
			delete o;
		}
		else
		{
			o->update(deltaTime);
			++itr;
		}
	}
}

void Level::start()
{
	//TODO start level
}

void Level::stop()
{
	//TODO stop level, return to menu
}

void Level::createRoom()
{
	GameObject* room = new GameObject();
	room->addComponent(new StageComponent(texturess->textures[1]));
	objects.push_back(room);
}

void Level::createMovingCubeLeft(float height) //blue color
{
	//Add moving cube right side of platform, TODO zorg ervoor dat dit gebaseerd op muziek gebeurt
	GameObject* o = new GameObject();
	o->addComponent(new CubeComponent(0.2f, 1, HAND::leftHand, ARROWDIRECTION::up));
	o->addComponent(new MoveToComponent());
	o->addAnimation(new TrailAnimation());
	o->position = Vec3f(2, 0, 30);
	o->getComponent<MoveToComponent>()->target = Vec3f(+1.5f, -height + 0.6f, -5.0f);

	objects.push_back(o);
}

void Level::createMovingCubeRight(float height) //red color
{
	//Add moving cube right side of platform, TODO zorg ervoor dat dit gebaseerd op muziek gebeurt
	GameObject* o = new GameObject();
	o->addComponent(new CubeComponent(0.2f, 1, HAND::rightHand, ARROWDIRECTION::right));
	o->addComponent(new MoveToComponent());
	o->addAnimation(new TrailAnimation());

	o->position = Vec3f(-2, 0, 30);
	o->getComponent<MoveToComponent>()->target = Vec3f(-1.5f, -height + 0.6f, -5.0f);

	objects.push_back(o);
}

bool isObjectOutOfBounds(GameObject* o)
{
	return o->position.z <= OBJECT_OUT_OF_BOUNDS;
}