#include <Track.h>
#include <iostream>
#include <string>

using namespace SoundCity;
using namespace std;

int main()
{
  Artist artist(1, "The White Stripes", 0.4, 1.0);
  //cout << artist.getName() << endl;
  Album album(1, "Elephant", "The White Stripes", 2012);
  //cout << album.getArtist() << endl;
  ContextData data(artist, album, 0.5);
  //cout << data.getArtistName() << endl;
  SignalData sign(0.2,0.3,0.4);
  Track test(1, sign ,data);
  cout << "Track id : " << test.getId() << endl;
  cout << "Artist id : " << test.getContextData().getArtist().getId() << endl;
  cout << "Artist name : " <<  test.getContextData().getArtist().getName() << endl;
  cout << "Artist familiarity : " << test.getContextData().getArtist().getFamiliarity() << endl;
  cout << "Artist popularity : " << test.getContextData().getArtist().getPopularity() << endl;
  cout << "Album Title : " << test.getContextData().getAlbum().getTitle() << endl;
  cout << "Album Artist : " << test.getContextData().getAlbum().getArtist() << endl;
  cout << "Album Release : " << test.getContextData().getAlbum().getReleaseDate() << endl;
  cout << "Track Popularity : " << test.getContextData().getPopularity() << endl;
  cout << "Track Rhythm : " << test.getSignalData().getRhythm() << endl;
  cout << "Track Energy : " << test.getSignalData().getEnergy() << endl;
  cout << "Track Tonality : " << test.getSignalData().getTonality() << endl;
}
