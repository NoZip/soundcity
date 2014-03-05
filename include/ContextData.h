#ifndef CONTEXTDATA_H
#define CONTEXTDATA_H

#include <Artist>
#include <Album>

namespace SoundCity
{
/**
 * Classe contenant les données contextuelles d'un morceau
 */
class ContextData {
  public:
    ContextData(Artist artist, Album album, float popularity);

    int getArtistId() const {return artist.getId();}
    String getArtistName() const {return artist.getName();}
    float getArtistFamiliarity() const {return artist.getFamiliarity();}
    float getArtistPopularity() const {return artist.getPopularity()}
    std::List<String> getSimilarArtists() const {return artist.getSimilarArtists();}
    String getAlbumTitle() const {return album.getTitle();}
    String getAlbumArtist() const {return album.getArtist();}
    int getAlbumReleaseDate() const {return album.getReleaseDate();}
    float getPopularity() const {return popularity;}

  private:
    Artist artist;
    Album album;
    float popularity;
};

}

#endif