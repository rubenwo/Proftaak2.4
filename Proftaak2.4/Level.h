#pragma once

class Level
{
public:
	Level();

	//Load all content, gets called before starting a level.
	void loadContent();
	//Load all textures
	void loadTextures();
	//Gets called on every draw, draw level components
	void draw();
	//Gets called at the beginning of a level.
	void start();
	//Gets called when the level is opted to stop.
	void stop();
	//Gets called every update, update level logic
	void update(float deltaTime);
};

