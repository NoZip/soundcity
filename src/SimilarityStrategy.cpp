#include <SimilarityStrategy.h>
#include <cmath>
#include <cassert>

using namespace SoundCity;

/* Coefficients de pondération de l'importance
* des données relatives aux morceaux 
*/
const int RHYTHM_WEIGHT = 4;
const int ENERGY_WEIGHT = 3;
const int ALBUM_RELEASE_DATE_WEIGHT = 2;
const int ARTIST_ID_WEIGHT = 1;

/*Seuil représentant un écartement entre deux morceaux
* assez faible pour être considéré nul 
*/
const int ALBUM_RELEASE_DATE_THRESHOLD = 5;

float SimilarityStrategy::compute(Track track1, Track track2)
{
  float dRhythm = 1 - abs(track1.getRhythm() - track2.getRhythm());
  float dEnergy = 1 - abs(track1.getEnergy() - track2.getEnergy());
  float dArtistId = (track1.getArtistId() == track2.getArtistId()) ? 1 : 0;
  
  /*float dAlbumReleaseDate = 1 - log10(abs(track1.getAlbumReleaseDate()
     - track2.getAlbumReleaseDate()) / ALBUM_RELEASE_DATE_THRESHOLD);*/

  float similarityScore = (dRhythm * RHYTHM_WEIGHT 
      + dEnergy * ENERGY_WEIGHT
      + dArtistId * ARTIST_ID_WEIGHT);

  similarityScore /= (RHYTHM_WEIGHT + ENERGY_WEIGHT + ARTIST_ID_WEIGHT);

  assert(similarityScore >=0 && similarityScore <=1);
  
  return  similarityScore;
}