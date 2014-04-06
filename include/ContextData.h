#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H

#include <Artist.h>
#include <Album.h>
#include <string>

namespace SoundCity
{
/**
 * Classe contenant les données contextuelles d'un morceau
 */
class ContextData {
  public:
    ContextData(const Artist &artist, const Album &album, float popularity);

    //Getters
    const Artist& getArtist() const {return artist;}
    const Album& getAlbum() const {return album;}
    Artist& getArtist() {return artist;}
    Album& getAlbum() {return album;}
    float getPopularity() const {return popularity;}

    //Raccourcis
    int getArtistId() const {return artist.getId();}
    std::string getArtistName() const {return artist.getName();}
    float getArtistFamiliarity() const {return artist.getFamiliarity();}
    float getArtistPopularity() const {return artist.getPopularity();}
    std::list<int> getSimilarArtists() const {return artist.getSimilarArtists();}
    std::string getAlbumTitle() const {return album.getTitle();}
    std::string getAlbumArtist() const {return album.getArtist();}
    int getAlbumReleaseDate() const {return album.getReleaseDate();}

  private:
    Artist artist;
    Album album;
    float popularity;
};

}

#endif
