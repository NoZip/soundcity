#include <NaiveSimilarityStrategy.h>
#include <iostream>
#include <cmath>
#include <cassert>

using namespace SoundCity;
using namespace std;

const float ALBUM_RELEASE_DATE_THRESHOLD = 0.3;

NaiveSimilarityStrategy::NaiveSimilarityStrategy() {}

float NaiveSimilarityStrategy::compute(Track track1, Track track2) const
{
  float date1 = track1.getAlbumReleaseDate();
  float date2 = track2.getAlbumReleaseDate();
  float dAlbumReleaseDate = log10(abs(date1 - date2));
  if(dAlbumReleaseDate > 1)
  {
    dAlbumReleaseDate = 1;
  }
  if(dAlbumReleaseDate < ALBUM_RELEASE_DATE_THRESHOLD)
  {
    dAlbumReleaseDate = 0;
  }
  return 1 - dAlbumReleaseDate;
}

