#ifndef TRACK_H
#define TRACK_H

#include <ContextData.h>
#include <SignalData.h>
#include <string>

namespace SoundCity
{
/**
 * Classe contenant les données contextuelles d'un morceau
 */
class Track {
  public:
    Track(int id, const SignalData &signal, const ContextData &context);

    int getId() const {return id;}
    int getArtistId() const {return context.getArtistId();}
    std::string getArtistName() const {return context.getArtistName();}
    float getArtistFamiliarity() const {return context.getArtistFamiliarity();}
    float getArtistPopularity() const {return context.getArtistPopularity();}
    std::list<std::string> getSimilarArtists() const {return context.getSimilarArtists();}
    std::string getAlbumTitle() const {return context.getAlbumTitle();}
    std::string getAlbumArtist() const {return context.getAlbumArtist();}
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