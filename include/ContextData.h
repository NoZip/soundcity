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

    int getArtistId() const {return artist.getId();}
    std::string getArtistName() const {return artist.getName();}
    float getArtistFamiliarity() const {return artist.getFamiliarity();}
    float getArtistPopularity() const {return artist.getPopularity();}
    std::list<std::string> getSimilarArtists() const {return artist.getSimilarArtists();}
    std::string getAlbumTitle() const {return album.getTitle();}
    std::string getAlbumArtist() const {return album.getArtist();}
    int getAlbumReleaseDate() const {return album.getReleaseDate();}
    float getPopularity() const {return popularity;}

  private:
    Artist artist;
    Album album;
    float popularity;
};

}

#endif