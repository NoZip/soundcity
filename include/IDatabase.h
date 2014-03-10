#ifndef IDATABASE_H
#define IDATABASE_H

#include <string>
#include <list>

#include <TrackPool.h>

namespace SoundCity
{

  /**
   * Interface de la database
   */

  class IDatabase{
  public:
    
    /**
     * Initialise et vérifie que la base de données est présente et 
     * fonctionnelle.
     */
    virtual int initialization() = 0;

    /**
     * Selectionne des morceaux conrrespondants aux options 
     * dans la base de données.
     * @param options Une liste des options pour la 
     * sélection des morceaux.
     * @param size Le nombre de morceaux à sélectionner.
     */

    virtual TrackPool select(std::list<std::string> options,
			     std::size_t size) =0;
  };

}

#endif
