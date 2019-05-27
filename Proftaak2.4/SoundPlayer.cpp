#include "SoundPlayer.hpp"

#include <iostream>

using std::string;
using namespace irrklang;

SoundPlayer::SoundPlayer()
{
	engine = irrklang::createIrrKlangDevice();
	//TODO Set engine->setListenerPosition(vec3df(0,0,0), vec3df(0,0,1));
	if (!engine)
		std::cout << "Failed to create irrklang device\n";

}
SoundPlayer::~SoundPlayer()
{
	engine->drop();
}

void SoundPlayer::cleanupSound(ISound* sound)
{
	if (sound)
	{
		sound->stop();
		sound->drop();
		sound = NULL;
	}
}

void SoundPlayer::addSound(const std::string& file, const SoundID& id, bool loop)
{
	ISound* sound = engine->play2D(file.c_str(), loop, true, false);
	sounds.insert(std::make_pair(id, sound));
}

void SoundPlayer::addSound3D(const std::string& file, const SoundID& id, bool loop, const Vec3f& pos)
{
	ISound* sound = engine->play3D(file.c_str(), vec3df(pos.x, pos.y, pos.z), loop,	true, false);
	sounds.insert(std::make_pair(id, sound));
}

ISound* SoundPlayer::getSound(const SoundID& id)
{
	if (sounds.find(id) == sounds.end())
		return nullptr; // Sound not found
	return sounds[id];
}

void SoundPlayer::deleteSound(const SoundID& id)
{
	if (sounds.find(id) != sounds.end())
	{
		ISound* sound = sounds[id];
		cleanupSound(sound);
		sounds.erase(id);
	}
}