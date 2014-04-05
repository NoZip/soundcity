#include <fstream>
#include <cassert>
#include <string>
#include <TextOutput.h>

using namespace SoundCity;

TextOutput::TextOutput() {}

void TextOutput::format(std::string fileName, Playlist playlist)
{
  file.open(fileName, std::ofstream::out | std::ofstream::trunc);
  assert(file.is_open());

  for(auto i = playlist.begin(); i != playlist.end(); i++)
  {
  	file << i->getTitle() << " - " << i->getArtistName()
  		<< "(" << i->getAlbumTitle() << " - " <<
  		i->getAlbumReleaseDate() << ")" << std::endl;
	}
	file.close();
}
