#ifndef ISELECTIONOBSERVER_H
#define ISELECTIONOBSERVER_H

#include <TrackPool.h>

namespace SoundCity
{

/**
 * Interface pour observer la selection des morceaux dans le module de
 * données.
 */
class ISelectionObserver
{
public:
  /**
   * Appelé quand la selection est terminée. 
   * @param size Le nombre de pistes sélectionnés.
   * @param pool La TrackPool des morceaux sélectionnés
   */
  virtual void notify(std::size_t size, const TrackPool &pool) = 0;
};

} // end namespace SoundCity

#endif
