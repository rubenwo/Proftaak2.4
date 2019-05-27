#include "MusicTrack.h"

MusicDataStructures::MusicTrack::MusicTrack(Song * songData)
{
	this->title = "title";
	this->bpms = 0.0;
	this->offset = 0.0;
	this->songData = songData;
}

