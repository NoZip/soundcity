#ifndef NAIVESIMILARITYSTRATEGY_H
#define NAIVESIMILARITYSTRATEGY_H 

#include <Track.h>
#include <ISimilarityStrategy.h>

namespace SoundCity
{

  /**
  * Header pour la gestion d'une similarité naïve 
  * entre les morceaux basée sur un calcul simple
  * sur le rythme
  */

 class NaiveSimilarityStrategy : public ISimilarityStrategy {
  public: 

      NaiveSimilarityStrategy();
      /**
      * Permet de donner un score de similarité entre les
      * deux morceaux passés en paramètre à partir de leur
      * rythme.
      * @param track1 Premier morceaux à comparer
      * @param track2 Deuxième morceaux à comparer
      */
      float compute(Track track1, Track track2) const;
      
      };

} //end of namespace Soundcity

#endif