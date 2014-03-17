#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <Track.h>

namespace SoundCity
{
/**
 * Classe contenant une liste ordonnée de morceaux
 */
class Playlist : public std::list<Track> {
  public:
    Playlist();
    //Setters
    void setValid(bool newValid) {valid = newValid;}
    //Getters
    bool isValid() const {return valid;}

  private:
    bool valid;
};

}

#endif