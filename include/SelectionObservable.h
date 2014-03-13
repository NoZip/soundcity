#ifndef SELECTIONOBSERVABLE_H
#define SELECTIONOBSERVABLE_H

#include <TrackPool.h>
#include <Observable.hpp>
#include <ISelectionObserver.h>

namespace SoundCity {

/**
 * Gère le feedback de l'étape de sélection.
 */
class SelectionObservable : public Observable<ISelectionObserver> {
public:
  SelectionObservable();

  /**
   * Appelé quand la selection est terminée. 
   * @param size Le nombre de pistes sélectionnés.
   * @param pool La TrackPool des morceaux sélectionnés
   */
  void notifyAll(std::size_t size, const TrackPool &pool);
};

} // end namespace SoundCity

#endif
