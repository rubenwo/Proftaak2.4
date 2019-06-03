#pragma once
#include "GameObject.h"

class Texture;

class Level
{
private:
	void createRoom();
	void createMovingCubeRight(float height = 0);
	void createMovingCubeLeft(float height = 0);
	void createRandomLocCube(float maxX = 2, float maxY = 1);
public:
	Level() = default;
	Level(Texture* texture);
	std::list<GameObject*> objects;

	float score;
	float combo;

	//Load all content, gets called before starting a level.
	void loadContent();
	//Load all textures
	//void loadTextures();
	//Gets called on every draw, draw level components
	void draw();
	//Gets called at the beginning of a level.
	void start();
	//Gets called when the level is opted to stop.
	void stop();
	//Gets called every update, update level logic
	void update(float deltaTime);
};
