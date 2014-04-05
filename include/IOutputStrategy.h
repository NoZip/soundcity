#ifndef IOUTPUTSTRATEGY_H
#define IOUTPUTSTRATEGY_H

#include <Playlist.h>
#include <string>

namespace SoundCity
{
  /**
   * Interface pour le module de sortie
   */

  class IOutputStrategy{
  public:
    /**
     * Permet de restituer la playlist générée à l'utilisateur.
     * @param playlist La playlist générée.
     */
    
    virtual void format(std::string fileName, Playlist playlist) = 0;
  };
}

#endif
