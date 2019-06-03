#include "AudioComponent.hpp"
#include "GameObject.h"
#include "SoundPlayer.hpp"

AudioComponent::AudioComponent(const std::string& audioFile)
{
	soundPlayer = &SoundPlayer::getInstance();
	soundID = SoundPlayer::getAvailableSoundID();
	soundPlayer->addSound3D(audioFile, soundID, true, Vec3f(0,0,0));
	sound = soundPlayer->getSound(soundID);
}

AudioComponent::~AudioComponent()
{
	soundPlayer->deleteSound(soundID);
}

void AudioComponent::update(float elapsedTime)
{
	const Vec3f pos = gameObject->position;
	sound->setPosition(irrklang::vec3df(pos.x, pos.y, pos.z));
}

void AudioComponent::playAudio()
{
	sound->setPosition(irrklang::vec3df(gameObject->position.x, gameObject->position.y, gameObject->position.z));
	sound->setIsPaused(false);
}