#include <iostream>
#include "Level.h"
#include <iostream>
#include "GameObject.h"
#include "CubeComponent.h"
#include "MoveToComponent.h"
#include "StageComponent.h"
#include "ObjectModel.h"
#include "AudioComponent.hpp"
#include "TrailAnimation.hpp"
#include "Util.hpp"
#include "Assets.hpp"
#include <ctime>
#include "PlayerComponent.h"

using std::string;
#define OBJECT_OUT_OF_BOUNDS -4.0f
GameObject* player;

Texture* texturess;
Vec2f lastRandLoc;
int lastObjectAdded = 0;
string exePath;


bool isObjectOutOfBounds(GameObject* o);
void createRoom(void);

Level::Level(Texture* texture)
{
	texturess = texture;
}

//Level::Level() {}

void Level::loadContent()
{
	exePath = Util::getExePath();

	player = new GameObject();
	player->position = Vec3f(0, 0, -1);
	player->addComponent(new PlayerComponent(&objects, texturess->textures[3], 0.25f));		//fix texturess->textures[3]
	player->getComponent<PlayerComponent>()->setCollisionCallback([](GameObject* obj)
	{
		obj->removeComponent<DrawComponent>();
		std::cout << "Hit an object";
		//TODO explosion
	});

	score = 0;
	//loadTextures();
	createRoom();
	srand(static_cast<unsigned>(time(0)));
	createRandomLocCube();
	createRandomLocCube();
}

void Level::draw()
{
	player->draw();

	glRotatef(180, 1, 0, 0);
	player->draw();

	for (const auto& o : objects)
		o->draw();
}

void Level::update(float deltaTime)
{
	player->update(deltaTime);

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

	if (objects.size() < 25)
	{
		createRandomLocCube();
	}

	//DEBUG CODE
	if (lastObjectAdded > 10)
		createRandomLocCube();
	lastObjectAdded++;*/
	//END DEBUG CODE
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
	o->position = Vec3f(2, 0, 30);
	o->addComponent(new CubeComponent(0.2f, 1, HAND::leftHand, ARROWDIRECTION::up));
	o->addComponent(new MoveToComponent());

	o->addAnimation(new TrailAnimation());
	o->position = Vec3f(2, 0, 50);
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

	o->position = Vec3f(-2, 0, 50);
	o->getComponent<MoveToComponent>()->target = Vec3f(-1.5f, -height + 0.6f, -5.0f);

	objects.push_back(o);
}

bool isObjectOutOfBounds(GameObject* o)
{
	return o->position.z <= OBJECT_OUT_OF_BOUNDS;
}

void Level::createRandomLocCube(float maxX, float maxY)
{
	GameObject* o = new GameObject();
	o->addComponent(new MoveToComponent());

	float rX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float rY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

	float randNumX = rX * maxX;
	float randNumY = rY * maxY;

	const int arrowDirection = rand() % 4;
	ARROWDIRECTION direction;
	if (arrowDirection == 0)
		direction = ARROWDIRECTION::left;
	else if (arrowDirection == 1)
		direction = ARROWDIRECTION::up;
	else if (arrowDirection == 2)
		direction = ARROWDIRECTION::right;
	else
		direction = ARROWDIRECTION::down;

	if (randNumX > maxX / 2)
	{
		o->addComponent(new CubeComponent(0.2f, 1, HAND::leftHand, direction));
		o->position = Vec3f(randNumX, -randNumY, 50);

		AudioComponent* a = new AudioComponent(exePath + SOUND_ENGINE);
		o->addComponent(a);
		o->addAnimation(new TrailAnimation());
		a->playAudio();
		o->getComponent<MoveToComponent>()->target = Vec3f(randNumX - (maxX / 2) + 0.3, randNumY - 0.4f, -5.0f); //+0.3 to avoid the player
	}
	else
	{
		o->addComponent(new CubeComponent(0.2f, 1, HAND::rightHand, direction));
		o->position = Vec3f(randNumX, -randNumY, 50);

		AudioComponent* a = new AudioComponent(exePath + SOUND_ENGINE);
		o->addComponent(a);
		o->addAnimation(new TrailAnimation());

		a->playAudio();
		o->getComponent<MoveToComponent>()->target = Vec3f(randNumX - (maxX / 2) - 0.4, randNumY - 0.4f, -5.0f); //+0.4 to avoid the player
	}


	lastObjectAdded = 0;
	objects.push_back(o);
}
