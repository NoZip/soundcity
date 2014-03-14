#include <Album.h>
#include <cassert>

using namespace SoundCity;

Album::Album(int id, const std::string &title, const std::string &artist, int release) :
  id(id),
  artist(artist),
  title(title),
  release(release)
  {
    assert(&title);
    assert(&artist);
    assert(release > 0);
  }