#include "SoundPlayer.hpp"

#include <iostream>
#include <random>

using std::string;
using namespace irrklang;

SoundPlayer::SoundPlayer()
{
	engine = irrklang::createIrrKlangDevice();
	//TODO Set engine->setListenerPosition(vec3df(0,0,0), vec3df(0,0,1));
	if (!engine)
		std::cout << "Failed to create irrklang device\n";
	else
		engine->setSoundVolume(1.0f);
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

void SoundPlayer::setListenerPosition(const Vec3f& pos, const Vec3f& heading)
{
	engine->setListenerPosition(vec3df(pos.x, pos.y, pos.z), vec3df(heading.x, heading.y, heading.z));
}
SoundID SoundPlayer::getAvailableSoundID()
{
	size_t length = 16;
	static auto& chrs = "0123456789"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	thread_local static std::mt19937 rg{ std::random_device{}() };
	thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

	std::string s;

	s.reserve(length);

	while (length--)
		s += chrs[pick(rg)];

	return s;
}