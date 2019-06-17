#ifndef MUSICLOADER_HPP
#define MUSICLOADER_HPP
#include <vector>
#include "MusicTrack.h"

#define MUSIC_TIME_OFFSET (6000 - 100) //milliseconds

namespace MusicLoader
{
	MusicDataStructures::MusicTrack* LoadMusicFile(std::string fileLocation);
}

#endif
