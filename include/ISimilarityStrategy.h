#ifndef ISIMILARITYSTRATEGY_H
#define ISIMILARITYSTRATEGY_H

#include <Track.h>

namespace SoundCity
{

  /**
   * Interface pour la gestion de la similarité entre les morceaux
   */

  class ISimilarityStrategy{
  public:

    /**
     * Permet de donner un score de similarité entre les deux morceaux
     * passés en paramètre.
     * @param track1 Premier morceau à comparer
     * @param track2 Deuxième morceau à comparer
     */
    virtual float compute(Track track1, Track track2) = 0;
  };

}

#endif
