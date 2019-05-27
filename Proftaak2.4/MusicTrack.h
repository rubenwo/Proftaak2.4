#pragma once
#include <string>
#include <vector>

namespace MusicDataStructures
{
	enum class NoteType { Zero = 0, One = 1, Two = 2, Three = 3, Four = 4, Mine = 5 };

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

		Song * songData;

		MusicTrack(Song * songData);
	};

}
