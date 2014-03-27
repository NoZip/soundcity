#include <fstream>
#include <cassert>
#include <string>

#include <TextOutput.h>

void TextOutput::format(Playlist &playlist)
{
  file.open("resultat.txt", std::ofstream::out | std::ofstream::app);
  assert(file.is_open());

  for(auto i = Playlist.begin(); i != Playlist.end(); i++)
  {
  	file << *i.getTitle() << " - " << *i.getContextData().getArtist().getName()
  		<< "(" << *i.getContextData().getAlbum().getName() << " - " <<
  		*i.getContextData().getAlbum().getReleaseDate() << ")" << endl;
	}
	file.close();
}