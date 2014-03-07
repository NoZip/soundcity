#include <../include/Artist.h>

using namespace SoundCity;

Artist::Artist(int id, const std::string &name, float familiarity, float popularity) :
	id(id),
	name(name),
	familiarity(familiarity),
	popularity(popularity)
	{}

Artist::Artist(int id, const std::string &name, float familiarity, float popularity, const std::list<std::string> &similar) :
  id(id),
  name(name),
  familiarity(familiarity),
  popularity(popularity),
  similar(similar)
  {}

void Artist::addSimilarArtist(const std::string &artist)
{
  similar.push_back(artist);
}
