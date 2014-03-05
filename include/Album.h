#ifndef ALBUM_H
#define ALBUM_H

#include <String>

namespace SoundCity
{
/**
 * Classe contenant les données relatives à un album
 */
class Album {
  public:
    Artist(int id, String title, String artist, int release);

    int getId() const {return id;}
    String getTitle() const {return title;}
    String getArtist() const {return artist;}
    int getReleaseDate() const {return release;}

  private:
    int id;
    String title;
    String artist;
    int release;
};

}

#endif