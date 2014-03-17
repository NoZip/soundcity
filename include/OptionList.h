#ifndef OPTIONLIST_H
#define OPTIONLIST_H

#include <string>

namespace SoundCity
{
/**
 * Classe contenant une liste d'options dans le cadre d'une requete
 */
class OptionList {
  public:
    OptionList(const std::string &artist, int startYear, int endYear, float popularity, float energy, float rhythm, float mood, std::size_t size);
    //Getters
    std::string getArtist() const {return artist;}
    int getStartYear() const {return startYear;}
    int getEndYear() const {return endYear;}
    float getPopularity() const {return popularity;}
    float getRhythm() const {return rhythm;}
    float getEnergy() const {return energy;}
    float getMood() const {return mood;}
    std::size_t getSize() const {return size;}

  private:
    std::string artist;
    int startYear;
    int endYear;
    float popularity;
    float energy;
    float rhythm;
    float mood;
    std::size_t size;
};

}

#endif