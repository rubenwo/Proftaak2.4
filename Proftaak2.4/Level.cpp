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
#include "MusicLoader.hpp"
#include <iostream>
#include "SoundPlayer.hpp"
#include "PlayerComponent.h"
#include "HTTPRequest.hpp"

using std::string;
#define OBJECT_OUT_OF_BOUNDS -4.0f
GameObject* player;

MusicDataStructures::MusicTrack* track;
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
	//use texture 7 instead of 12 for hand textures..
	player->addComponent(new PlayerComponent(&objects, texturess->textures[12], 0.25f));
	player->getComponent<PlayerComponent>()->setCollisionCallback([](GameObject* obj)
	{
		obj->position = Vec3f(0, 0, -4);
		obj->getComponent<CubeComponent>()->isHit = true;
	});

	score = 0;
	//loadTextures();
	createRoom();
	srand(static_cast<unsigned>(time(0)));
	initMusic();
}

void Level::loadTextures()
{
	texturess = new Texture("texture");
	texturess->initTextures();
}

void Level::initMusic()
{
	string path = exePath;
	track = MusicLoader::LoadMusicFile(path + DATA_BOOMx4);
	SoundPlayer& soundPlayer = SoundPlayer::getInstance();
	soundPlayer.addSound(path + MUSIC_BOOMx4, track->title, true); //..\\music\\Boom Boom Boom Boom\\Music.ogg"

	soundPlayer.addSound(path + SOUND_ENGINE, SOUND_ENGINE, true);
}

void Level::startMusic(int)
{
	SoundPlayer& soundPlayer = SoundPlayer::getInstance();
	//irrklang::ISound * sound = soundPlayer.getSound(track->title);
	soundPlayer.playSound(track->title, false);
}

void Level::draw()
{
	player->draw();

	glRotatef(180, 1, 0, 0);
	player->draw();

	//TODO: draw score

	for (const auto& o : objects)
		o->draw();
}

void Level::update(float deltaTime)
{
	player->update(deltaTime);

	auto result = track->update(deltaTime);

	if (std::get<0>(result) == MusicDataStructures::MusicAction::Left)
		createRandomLocCube(std::get<1>(result));
	else if (std::get<0>(result) == MusicDataStructures::MusicAction::Right)
		createRandomLocCube(std::get<1>(result));

	std::list<GameObject*>::iterator itr = objects.begin();

	while (itr != objects.end())
	{
		auto o = (*itr);
		if (isObjectOutOfBounds(o))
		{
			if (!o->getComponent<CubeComponent>()->isHit)
				combo = 1;
			else
			{
				std::cout << "HIT";
				if (combo < 8)
					combo++;
				score += combo;
			}
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

MusicDataStructures::MusicTrack* Level::getTrack()
{
	return track;
}

void Level::start()
{
	glutTimerFunc(MUSIC_TIME_OFFSET, startMusic, 0);
}

void Level::stop()
{
	//TODO stop level, return to menu
	try
	{
		http::Request request("http://rubenwoldhuis.nl/highscore/test/" + std::to_string(score));
		http::Response response = request.send("GET");
		if (response.status == 200)
		{
			string result(response.body.begin(), response.body.end());
			std::cout << result << std::endl;
			highScore = std::stoi(result);
		}
		else
		{
			std::cout << "internal server error occurred" << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Request failed, error: " << e.what() << std::endl;
	}
}

void Level::createRoom()
{
	GameObject* room = new GameObject();
	room->addComponent(new StageComponent(texturess->textures[1]));
	objects.push_back(room);
}

bool isObjectOutOfBounds(GameObject* o)
{
	//std::cout << "DESPAWN";
	return o->position.z <= OBJECT_OUT_OF_BOUNDS;
}

void Level::createRandomLocCube(ARROWDIRECTION direction, float maxX, float maxY)
{
	GameObject* o = new GameObject();
	o->addComponent(new MoveToComponent());

	float rX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float rY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

	float randNumX = rX * maxX;
	float randNumY = rY * maxY;

	//string path = "..";

	if (randNumX > maxX / 2)
	{
		o->addComponent(new CubeComponent(0.2f, 1, HAND::leftHand, direction));
		o->position = Vec3f(randNumX, -randNumY, 30);

		AudioComponent* a = new AudioComponent(SOUND_ENGINE);
		o->addComponent(a);
		o->addAnimation(new TrailAnimation());
		a->playAudio(true);
		o->getComponent<MoveToComponent>()->target = Vec3f(randNumX - (maxX / 2) + 0.3, randNumY - 0.4f, -5.0f);
		//+0.3 to avoid the player
	}
	else
	{
		o->addComponent(new CubeComponent(0.2f, 1, HAND::rightHand, direction));
		o->position = Vec3f(randNumX, -randNumY, 30);

		AudioComponent* a = new AudioComponent(SOUND_ENGINE);
		o->addComponent(a);
		o->addAnimation(new TrailAnimation());

		a->playAudio(true);
		o->getComponent<MoveToComponent>()->target = Vec3f(randNumX - (maxX / 2) - 0.4, randNumY - 0.4f, -5.0f);
		//+0.4 to avoid the player
	}


	lastObjectAdded = 0;
	objects.push_back(o);
}
