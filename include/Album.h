#ifndef ALBUM_H
#define ALBUM_H

#include <string>

namespace SoundCity
{
/**
 * Classe contenant les données relatives à un album
 */
class Album {
  public:
    Album(int id, const std::string &title, const std::string &artist, int release);
    //Getters
    int getId() const {return id;}
    std::string getTitle() const {return title;}
    std::string getArtist() const {return artist;}
    int getReleaseDate() const {return release;}

  private:
    int id;
    std::string title;
    std::string artist;
    int release;
};

}

#endif