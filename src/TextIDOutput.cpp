#include <fstream>
#include <cassert>
#include <string>
#include <TextIDOutput.h>

using namespace SoundCity;

TextIDOutput::TextIDOutput() {}

void TextIDOutput::format(std::string fileName, Playlist playlist)
{
	file.open(fileName, std::ofstream::out | std::ofstream::trunc);
	assert(file.is_open());

	for(auto i = playlist.begin(); i != playlist.end(); i++)
	{
  	file << i->getId() << std::endl;
	}
	file.close();
}
