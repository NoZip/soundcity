#ifndef SELECTIONOBSERVABLE_H
#define SELECTIONOBSERVABLE_H

#include <list>

#include <TrackPool>
#include <ISelectionObserver>

namespace Soundcity {

/**
 * Gère le feedback de l'étape de sélection.
 */
class SelectionObservable {
public:
  SelectionObservable();

  /**
   * Attache un observer.
   * @param observer L'observer à ajouter.
   */
  void attach(const ISelectionObserver &observer);

  /**
   * Détache un observer.
   * @param observer l'observer à détacher.
   */
  void detach(const ISelectionObserver &observer);

  /**
   * Appelé quand la selection est terminée. 
   * @param size Le nombre de pistes sélectionnés.
   * @param pool La TrackPool des morceaux sélectionnés
   */
  void notifyAll(std::size_t size, const TrackPool &pool);

protected:
  std::list<ISelectionObserver>; ///< La liste d'observers interne.
};

} // end namespace SoundCity

#endif