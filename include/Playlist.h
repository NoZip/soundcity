#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <Track.h>

namespace SoundCity
{
/**
 * Classe contenant une liste ordonnée de morceaux
 */
class Playlist {
  public:
    Playlist();
    //Setters
    void setValid(bool newValid) {valid = newValid;}
    //Getters
    std::list<Track>& getList() {return playlist;}
    bool isValid() const {return valid;}

  private:
    std::list<Track> playlist;
    bool valid;
};

}

#endif