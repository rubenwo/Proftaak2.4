#include "MusicLoader.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "MusicTrack.h"
#include <algorithm>

using namespace std;

namespace MusicLoader
{
	void LoadMusicFile()
	{
		ifstream inFile;
		inFile.open("..\\music\\Boom Boom Boom Boom\\Simfile.sm");
		if (!inFile) {
			cerr << "Unable to open file datafile.txt";
			return;
		}

		locale loc;
		string line;
		MusicTrack* track = new MusicTrack();

		while(std::getline(inFile, line))
		{
			if (line.find("//") == 0) continue;
			else if(line.find("#") == 0)
			{
				//the # symbol indicates a line of generic data for the song
				string key = line.substr(1, line.find(':') - 1);
				std::transform(key.begin(), key.end(), key.begin(), ::toupper);

				if(0 == key.compare("TITLE"))
				{
					track->title = key;
				}
				if (0 == key.compare("BPMS"))
				{
					int pos = line.find("=");
					string value = line.substr(pos, line.find(";") - pos);
					track->bpms = stof(value);
				}

			}
		}


		inFile.close();
	}
}

