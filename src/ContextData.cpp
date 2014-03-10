#include <ContextData.h>
#include <cassert>

using namespace SoundCity;

ContextData::ContextData(const Artist &artist, const Album &album, float popularity) :
  artist(artist),
  album(album),
  popularity(popularity)
  {
    assert(&artist);
    assert(&album);
    assert(popularity >= 0 && popularity <= 1);
  }