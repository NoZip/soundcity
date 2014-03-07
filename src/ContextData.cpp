#include <../include/ContextData.h>

using namespace SoundCity;

ContextData::ContextData(const Artist &artist, const Album &album, float popularity) :
  artist(artist),
  album(album),
  popularity(popularity)
  {}