#include <Artist.h>
#include <cassert>

using namespace SoundCity;

Artist::Artist(int id, const std::string &name, float familiarity, float popularity) :
	id(id),
	name(name),
	familiarity(familiarity),
	popularity(popularity)
{
  //assert(id);
  assert(&name);
  assert(familiarity >= 0 && familiarity <= 1);
  //solution temporaire pour combler à un soucis de BDD
  if(popularity > 1)
  {
    popularity = 1;
  }
  assert(popularity >= 0 && popularity <= 1);
}

void Artist::addSimilarArtist(int artist_id)
{
  similar.push_back(artist_id);
}
