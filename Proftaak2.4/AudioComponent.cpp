#include "AudioComponent.hpp"
#include "GameObject.h"

AudioComponent::AudioComponent(const SoundID& id)
{
	soundPlayer = &SoundPlayer::getInstance();
	soundID = id;
	//soundPlayer->addSound3D(id, soundID, true, Vec3f(0,0,0));
	//sound = soundPlayer->getSound(soundID);
}

AudioComponent::~AudioComponent()
{
	stopAudio();
}

void AudioComponent::update(float elapsedTime)
{
	if (!sound) return;

	const Vec3f* pos = &gameObject->position;
	sound->setPosition(irrklang::vec3df(pos->x, pos->y, pos->z));
}

void AudioComponent::playAudio(bool loop)
{
	if (!sound || (sound && sound->isFinished()))
	{
		stopAudio();
		sound = soundPlayer->playSound3D(soundID, gameObject->position, loop);
	}
}

void AudioComponent::stopAudio()
{
	if (sound)
	{
		sound->setIsPaused(true);
		sound->drop();
		sound = nullptr;
	}
}