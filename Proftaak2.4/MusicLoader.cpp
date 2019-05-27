#include "MusicLoader.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "MusicTrack.h"
#include <algorithm>

using namespace std;
using namespace MusicDataStructures;

namespace MusicLoader
{
	MusicTrack * LoadMusicFile()
	{
		ifstream inFile;
		inFile.open("..\\music\\Boom Boom Boom Boom\\Simfile.sm");
		if (!inFile) {
			cerr << "Unable to open file datafile.txt";
			return nullptr;
		}

		locale loc;
		string line;
		bool readingNotes = false;
		Bar * bar = new Bar();
		Song * song = new Song();
		auto * track = new MusicTrack(song);
		const string noteTypes = "01234M";

		while (std::getline(inFile, line))
		{
			if (line.find("//") == 0) continue;
			if (line.find("#") == 0)
			{
				//the # symbol indicates a line of generic data for the song
				string key = line.substr(1, line.find(':') - 1);
				std::transform(key.begin(), key.end(), key.begin(), ::toupper);
				string value = line.substr(line.find(":") + 1, line.find(";") - 1);
				if (0 == key.compare("TITLE"))
				{
					track->title = value;
				}
				if (0 == key.compare("BPMS"))
				{
					int pos = line.find("=");
					string value_bpms = line.substr(pos + 1, line.find(";") - pos);
					track->bpms = stof(value_bpms);
				}
				if (key == "OFFSET")
				{
					track->offset = stof(value);
				}
				if (key == "NOTES")
				{
					readingNotes = true;
				}
			}

			if (readingNotes)
			{
				if (0 == line.find(",") || 0 == line.find(";"))
				{
					song->bars.push_back(*bar);
					delete(bar);
					bar = new Bar();
					//song->bars[song->bars.size()] = *bar;
				}
				else if (line.find("//") != string::npos || line.find(":") != string::npos) continue;
				else
				{
					Notes * note = new Notes();
					for (int i = 0; i < 4; ++i)
					{
						int l = noteTypes.find(line[i]);
						switch (i)
						{
						case 0:note->left = static_cast<NoteType>(l); break;
						case 1:note->down = static_cast<NoteType>(l); break;
						case 2:note->up = static_cast<NoteType>(l); break;
						case 3:note->right = static_cast<NoteType>(l); break;
						}
					}
					bar->notes.push_back(*note);
					delete(note);
					// int k = bar->notes.size();
					//
					// bar->notes[k] = *note;
				}
			}
		}



		delete(bar);
		inFile.close();
		return track;
	}
}

