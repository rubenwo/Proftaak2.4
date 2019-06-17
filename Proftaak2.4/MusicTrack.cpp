#include "MusicTrack.h"
#include "SoundPlayer.hpp"
#include "MusicLoader.hpp"
#include "Enums.h"

using namespace MusicDataStructures;

MusicTrack::MusicTrack()
{
}

MusicTrack::MusicTrack(Song * songData)
{
	this->title = "title";
	this->bpms = 0.0;
	this->offset = 0.0;
	this->songData = songData;
	this->barCount = 0;
	this->noteCount = 0;
	this->barTime = (60.0f / bpms) * 4.0f * 1000.0f;//time of one bar in milliseconds
	this->totalTime = MUSIC_TIME_OFFSET;
	currentMusicAction = MusicAction::Left;
}

ARROWDIRECTION MusicTrack::getDirection() const
{
	Notes note = songData->bars[barCount].notes[noteCount];
	if (note.left != NoteType::Zero && note.left != NoteType::Mine) return left;
	if (note.right != NoteType::Zero && note.right != NoteType::Mine) return right;
	if (note.up != NoteType::Zero && note.up != NoteType::Mine) return up;
	if (note.down != NoteType::Zero && note.down != NoteType::Mine) return down;
	return nowhere;
}

std::tuple<MusicAction, ARROWDIRECTION> MusicTrack::update(float deltaTime)
{
	//int position = -1;
	this->totalTime += deltaTime * 1000.0f;
	// irrklang::ISound * sound = SoundPlayer::getInstance().getSound(title);
	// if (sound != nullptr)
	// 	position = sound->getPlayPosition();

	//if (-1 == position)
	// 	return {MusicDataStructures::MusicAction::None, nowhere };

	if(barCount < static_cast<int>(songData->bars.size()))
	{
		float diffTime = static_cast<float>(totalTime) - (barCount * barTime);
		if(diffTime >= 0)
		{
			currentMusicAction = (currentMusicAction == MusicAction::Left) ? MusicAction::Right : MusicAction::Left;
			int noteSize = songData->bars[barCount].notes.size();
			const int divideRate = 4;
			float noteTime = barTime / (noteSize / divideRate);
			if(diffTime > barTime)
			{
				//noteTime = barTime / 2;//songData->bars[barCount].notes.size();
				barCount++;
				noteCount = 0;
				float restTime = diffTime - barTime;
				if(restTime > noteTime)
				{
					noteCount++;
					ARROWDIRECTION direction = getDirection();
					if (getDirection() != nowhere)
						return { currentMusicAction, direction };
				}
			}
			else
			{
				float restTime = diffTime - (noteCount * noteTime);
				if (restTime > noteTime)
				{
					noteCount = noteCount + (1);
					ARROWDIRECTION direction = getDirection();
					if (getDirection() != nowhere)
						return { currentMusicAction, direction };
				}
			}
		}		
	}
	return { MusicAction::None, nowhere };
}

