#ifndef ARTIST_H
#define ARTIST_H

#include <string>
#include <list>

namespace SoundCity
{
/**
 * Classe contenant les données relatives à un artiste
 */
class Artist {
  public:
    Artist(int id, const std::string &name, float familiarity, float popularity);

    /**
     * Ajoute un artiste à la liste des artistes similaires
     * @param artist Le nom de l'artiste
     */
    void addSimilarArtist(int artist_id);
    int getId() const {return id;}
    std::string getName() const {return name;}
    float getFamiliarity() const {return familiarity;}
    float getPopularity() const {return popularity;}
    const std::list<int>& getSimilarArtists() const {return similar;}

  protected:
    int id;
    std::string name;
    float familiarity;
    float popularity;
    std::list<int> similar;
};

}

#endif