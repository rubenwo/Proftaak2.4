#pragma once
#include "GameObject.h"

class Level
{
private:
	void createRoom();
	void createMovingCubeLeft(float height);
	void createMovingCubeRight(float height);
public:
	//Texture *texturess;


	Level(Texture* texture);
	Level();
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
