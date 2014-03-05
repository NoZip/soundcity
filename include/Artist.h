#ifndef ARTIST_H
#define ARTIST_H

#include <String>

namespace SoundCity
{
/**
 * Classe contenant les données relatives à un artiste
 */
class Artist {
  public:
    Artist(int id, String name, float familiarity, float popularity);
    Artist(int id, String name, float familiarity, float popularity, std::List<String> similar);

    /**
     * Ajoute un artiste à la liste des artistes similaires
     * @param artist Le nom de l'artiste
     */
    void addSimilarArtist(String artist);
    int getId() const {return id;}
    String getName() const {return name;}
    float getFamiliarity() const {return familiarity;}
    float getPopularity() const {return popularity;}
    std::List<String> getSimilarArtists() const {return similar;}

  protected:
    int id;
    String name;
    float familiarity;
    float popularity;
    std::List<String> similar;
};

}

#endif