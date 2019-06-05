#pragma once
#include <string>
#include <vector>
#include <tuple>
#include "Enums.h"

namespace MusicDataStructures
{
	enum class NoteType { Zero = 0, One = 1, Two = 2, Three = 3, Four = 4, Mine = 5 };
	enum class MusicAction {None = 0, Left = 1, Right = 2};
	//enum class MusicDirection {West, East,North,South,Nowhere};

	struct Notes
	{
	public:
		NoteType left;
		NoteType down;
		NoteType up;
		NoteType right;
	};

	struct Bar
	{
		std::vector<Notes> notes;
	};

	struct Song
	{
		std::vector<Bar> bars;
	};

	class MusicTrack
	{
	public:
		std::string title;
		float bpms;
		float offset;
		float totalTime;
		float barTime;

		Song * songData;
		//default constructor;
		MusicTrack();

		//normal constructor
		MusicTrack(Song * songData);

		//update method for checking
		std::tuple<MusicAction, ARROWDIRECTION> update(float deltaTime);

	private:
		ARROWDIRECTION getDirection() const;
		int barCount;
		int noteCount;
		MusicAction currentMusicAction;
	};

}
