#include <fstream>
#include <cassert>
#include <string>

#include <TextOutput.h>

using namespace SoundCity;

void TextOutput::format(Playlist &playlist)
{
  file.open("resultat.txt", std::ofstream::out | std::ofstream::app);
  assert(file.is_open());

  for(auto i = playlist.begin(); i != playlist.end(); i++)
  {
  	file << i->getTitle() << " - " << i->getArtistName()
  		<< "(" << i->getAlbumTitle() << " - " <<
  		i->getAlbumReleaseDate() << ")" << std::endl;
	}
	file.close();
}
