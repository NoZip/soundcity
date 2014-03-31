#include <NaiveSimilarityStrategy.h>
#include <iostream>
#include <cmath>
#include <cassert>

using namespace SoundCity;
using namespace std;

const int ALBUM_RELEASE_DATE_THRESHOLD = 10;
const float DALBUM_RELEASE_DATE_THRESHOLD = 0.8;

NaiveSimilarityStrategy::NaiveSimilarityStrategy() {}

float NaiveSimilarityStrategy::compute(Track track1, Track track2) const
{
  int date1 = track1.getAlbumReleaseDate();
  int date2 = track2.getAlbumReleaseDate();
  int dAlbumReleaseDate = abs(date1 - date2);

  if(dAlbumReleaseDate == 0)
  {
    return 1;
  }
  if(dAlbumReleaseDate <= ALBUM_RELEASE_DATE_THRESHOLD)
  {
    return DALBUM_RELEASE_DATE_THRESHOLD;
  }

  return 0;
}

