#ifndef GAME_HPP
#define GAME_HPP
#include "Engine.hpp"
class Game : public Engine
{
public:
	Game();
	~Game();

	virtual void update(float elapsedTime) override;
	virtual void draw() override;
	virtual void loadContent() override;
};

#endif
