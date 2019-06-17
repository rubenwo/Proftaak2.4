#pragma once
#include "GameObject.h"
#include "Enums.h"
#include "SoundPlayer.hpp"
#include "MusicTrack.h"

class Texture;

class Level
{
private:
	void createRoom();
	// void createMovingCubeRight(ARROWDIRECTION arrowdirection);
	// void createMovingCubeLeft(ARROWDIRECTION arrowdirection);
	// void createRandomLocCube(float maxX = 2, float maxY = 1);
	void createRandomLocCube(ARROWDIRECTION arrowDirection, float maxX = 1.5f, float maxY = 1.2f);
public:
	Level() = default;
	Level(Texture* texture);
	std::list<GameObject*> objects;

	int score = 0;
	int highScore = 0;
	float combo = 1;

	//Load all content, gets called before starting a level.
	void loadContent();
	//Load all textures
	void loadTextures();
	void initMusic();
	//Inits song
	static void initSong();
	static void startMusic(int);
	//Gets called on every draw, draw level components
	void draw();
	//Gets called at the beginning of a level.
	void start();
	//Gets called when the level is opted to stop.
	void stop();
	//Gets called every update, update level logic
	void update(float deltaTime);
	//Returns the current track.
	MusicDataStructures::MusicTrack* getTrack();
};
