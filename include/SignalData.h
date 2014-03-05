#ifndef SIGNALDATA_H
#define SIGNALDATA_H

namespace SoundCity
{
/**
 * Classe contenant les données signal d'un morceau
 */
class SignalData {
  public:
    SignalData(Artist artist, Album album, float popularity);

    float getRhythm() const {return rhythm;}
    float getEnergy() const {return energy;}
    float getTonality() const {return tonality;}
  private:
    float rhythm;
    float energy;
    float tonality;
};

}

#endif