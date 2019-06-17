#ifndef AUDIO_COMPONENT_HPP
#define AUDIO_COMPONENT_HPP

#include "Component.h"
#include <string>
#include "SoundPlayer.hpp"

class AudioComponent : public Component
{
public:
	AudioComponent(const SoundID& soundID);
	~AudioComponent();

	virtual void update(float elapsedTime) override;
	void playAudio(bool loop);
	void stopAudio();
private:
	SoundPlayer* soundPlayer;
	SoundID soundID;
	irrklang::ISound* sound;
};

#endif // !AUDIO_COMPONENT_HPP