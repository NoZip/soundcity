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
    Track(int id, const std::string &title, const SignalData &signal, const ContextData &context);

    //Getters
    int getId() const {return id;}
    const ContextData &getContextData() const {return context;}
    const SignalData &getSignalData() const {return signal;}
    std::string getTitle() const {return title;}

    //Raccourcis
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

    bool operator==(const Track &track) const {return (id == track.id);}

  private:
    int id;
    std::string title;
    SignalData signal;
    ContextData context;
};

}

#endif
