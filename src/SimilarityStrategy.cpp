#include <iostream>
#include <list>
#include <algorithm>
#include <cmath>
#include <cassert>

#include <SimilarityStrategy.h>

using namespace SoundCity;
using namespace std;

/* Coefficients de pondération de l'importance
* des données relatives aux morceaux 
*/
const int RHYTHM_WEIGHT = 4;
const int ENERGY_WEIGHT = 3;
const int ALBUM_RELEASE_DATE_WEIGHT = 2;
const int ARTIST_WEIGHT = 1;

/*Seuil représentant un écartement entre deux morceaux
* assez faible pour être considéré nul 
*/
const int ALBUM_RELEASE_DATE_THRESHOLD = 5;

SimilarityStrategy::SimilarityStrategy() {}

float SimilarityStrategy::compute(Track track1, Track track2) const
{
  float dRhythm = 1 - abs(track1.getRhythm() - track2.getRhythm());

  float dEnergy = 1 - abs(track1.getEnergy() - track2.getEnergy());
  
  const Artist &artist1 = track1.getContextData().getArtist();
  const Artist &artist2 = track2.getContextData().getArtist();

  const std::list<int> &similar = artist1.getSimilarArtists();

  float dArtist = 0.f;
  if (artist1.getId() == artist2.getId())
  {
    dArtist = 1.f;
  }
  else if (std::find(similar.begin(), similar.end(), artist2.getId()) != similar.end())
  {
    dArtist = 0.75f;
  }
  
  float date1 = track1.getAlbumReleaseDate();
  float date2 = track2.getAlbumReleaseDate();
  float dAlbumReleaseDate = log10(abs(date1 - date2));
  if(dAlbumReleaseDate < 0 
    || dAlbumReleaseDate < ALBUM_RELEASE_DATE_THRESHOLD)
  {
    dAlbumReleaseDate = 0;
  }
  if(dAlbumReleaseDate > 1)
  {
    dAlbumReleaseDate = 1;
  }
  dAlbumReleaseDate = 1 - dAlbumReleaseDate;
  

  float similarityScore = (dRhythm * RHYTHM_WEIGHT 
      + dEnergy * ENERGY_WEIGHT
      + dArtist * ARTIST_WEIGHT
      + dAlbumReleaseDate * ALBUM_RELEASE_DATE_WEIGHT);

  similarityScore /= (RHYTHM_WEIGHT + ENERGY_WEIGHT + ARTIST_WEIGHT + ALBUM_RELEASE_DATE_WEIGHT);

  assert(similarityScore >=0 && similarityScore <=1);
  
  return  similarityScore;
}