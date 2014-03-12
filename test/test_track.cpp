#include <Track.h>
#include <iostream>
#include <string>

using namespace SoundCity;

int main()
{
  std::string name, albumName, name2;
  name = "Test";
  Artist art(1,name,0.4,1.0);
  //std::cout << art.getName() << "\n";
  albumName = "Testalbum";
  name2 = "Test";
  Album alb(1,albumName,name2,2012);
  ContextData data(art,alb,0.5);
  //std::cout << data.getArtistName() << "\n";
  SignalData sign(0.2,0.3,0.4);
  Track test(1,sign,data);
  std::cout << "Track id : " << test.getId() << "\n";
  std::cout << "Artist id : " << test.getArtistId() << "\n";
  Artist a = test.getContextData().getArtist();
  std::cout << "Artist name : " <<  a.getName() << "\n";
  std::cout << "Artist name : " << test.getArtistName() << "\n";
  std::cout << "Artist familiarity : " << test.getArtistFamiliarity() << "\n";
  std::cout << "Artist popularity : " << test.getArtistPopularity() << "\n";
  std::cout << "Album Title : " << test.getAlbumTitle() << "\n";
  std::cout << "Album Artist : " << test.getAlbumArtist() << "\n";
  std::cout << "Album Release : " << test.getAlbumReleaseDate() << "\n";
  std::cout << "Track Popularity : " << test.getPopularity() << "\n";
  std::cout << "Track Rhythm : " << test.getRhythm() << "\n";
  std::cout << "Track Energy : " << test.getEnergy() << "\n";
  std::cout << "Track Tonality : " << test.getTonality() << "\n";
}