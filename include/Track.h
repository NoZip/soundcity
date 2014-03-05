#ifndef TRACK_H
#define TRACK_H

#include <ContextData>
#include <SignalData>

namespace SoundCity
{
/**
 * Classe contenant les données contextuelles d'un morceau
 */
class Track {
  public:
    Track(int id, SignalData signal, ContextData context);

    int getId() const {return id;}
    int getArtistId() const {return context.getArtistId();}
    String getArtistName() const {return context.getArtistName();}
    float getArtistFamiliarity() const {return context.getArtistFamiliarity());}
    float getArtistPopularity() const {return context.getArtistPopularity();}
    std::List<String> getSimilarArtists() const {return context.getSimilarArtists();}
    String getAlbumTitle() const {return context.getAlbumTitle();}
    String getAlbumArtist() const {return context.getAlbumArtist();}
    int getAlbumReleaseDate() const {return context.getAlbumReleaseDate();}
    float getPopularity() const {return context.getPopularity();}
    float getRhythm() const {return signal.getRhythm();}
    float getEnergy() const {return signal.getEnergy();}
    float getTonality() const {return signal.getTonality();}

  private:
    int id;
    SignalData signal;
    ContextData context;
};

}

#endif