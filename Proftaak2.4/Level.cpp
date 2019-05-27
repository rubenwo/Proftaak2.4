#include "Level.h"
#include "GameObject.h"
#include "CubeComponent.h"
#include "MoveToComponent.h"
#include "StageComponent.h"
#include "ObjectModel.h"
#include <iostream>

Texture *texturess;
std::list<GameObject*> objects;

void createRoom(void);
void createMovingCubeRight(float height = 0);
void createMovingCubeLeft(float height = 0);

Level::Level()
{
}

void Level::loadContent()
{
	loadTextures();
	createRoom();
	createMovingCubeLeft();
	createMovingCubeRight(1);
}

void Level::loadTextures() {
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
	for (const auto& o : objects)
	{
		if (o->position.z <= -4) {
			std::cout << "\r\nDelete object: ";
			objects.remove(o);
			break;
		}
		o->update(deltaTime);
		//TODO delete objects if behind player
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

void createRoom() {
	GameObject* room = new GameObject();
	room->addComponent(new StageComponent(texturess->textures[1]));
	objects.push_back(room);
}

void createMovingCubeLeft(float height) //blue color
{
	//Add moving cube right side of platform, TODO zorg ervoor dat dit gebaseerd op muziek gebeurt
	GameObject* o = new GameObject();
	o->addComponent(new CubeComponent(0.2f, 1, HAND::leftHand, ARROWDIRECTION::up));
	o->addComponent(new MoveToComponent());

	o->position = Vec3f(2, 0, 30);
	o->getComponent<MoveToComponent>()->target = Vec3f(1.5f, -height + 0.6f, -5.0f);

	objects.push_back(o);
}

void createMovingCubeRight(float height) //red color
{
	//Add moving cube right side of platform, TODO zorg ervoor dat dit gebaseerd op muziek gebeurt
	GameObject* o = new GameObject();
	o->addComponent(new CubeComponent(0.2f, 1, HAND::rightHand, ARROWDIRECTION::right));
	o->addComponent(new MoveToComponent());

	o->position = Vec3f(-2, 0, 30);
	o->getComponent<MoveToComponent>()->target = Vec3f(-1.5f, -height + 0.6f, -5.0f);

	objects.push_back(o);
}
