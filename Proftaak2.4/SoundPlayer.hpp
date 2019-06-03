#ifndef SOUND_PLAYER_HPP
#define SOUND_PLAYER_HPP

#include <irrKlang.h>
#include <map>
#include <string>
#include "Vec.h"
#pragma comment(lib, "irrKlang.lib")

typedef std::string SoundID;
class SoundPlayer
{
private:
	irrklang::ISoundEngine* engine;
	std::map<SoundID, irrklang::ISound*> sounds;
	SoundPlayer();
	~SoundPlayer();
	void cleanupSound(irrklang::ISound* sound);

public:
	static SoundPlayer& getInstance()
	{
		static SoundPlayer instance;
		return instance;
	}
	// Add a sound to the soundplayer.
	void addSound(const std::string& file, const SoundID& id, bool loop);
	// Add a 3d sound to the soundplayer. 
	void addSound3D(const std::string& file, const SoundID& id, bool loop, const Vec3f& pos);
	// Get a sound from the soundplayer using an id.
	irrklang::ISound* getSound(const SoundID& id);
	// Delete a sound from the soundplayer.
	void deleteSound(const SoundID& id);
	// Sets the 3d listener position
	void setListenerPosition(const Vec3f& pos, const Vec3f& heading);
	// Gets an available sound id.
	static SoundID getAvailableSoundID();
};

#endif // !SOUND_PLAYER_HPP
