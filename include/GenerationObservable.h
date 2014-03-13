#ifndef GENERATIONOBSERVABLE_H
#define GENERATIONOBSERVABLE_H

#include <Track.h>
#include <Observable.hpp>
#include <IGenerationObserver.h>

namespace SoundCity {

/**
 * Gère le feedback de l'étape de génération.
 */
class GenerationObservable : public Observable<IGenerationObserver> {
public:
  GenerationObservable();

  /**
   * Envoie une notification à tous les observers pour qu'ils puissent esecuter
   * leur routine liée. Cette notification est liéeé à l'étape de génération.
   * Elle est exécutée chaque fois qu'une piste est ajoutée à la playlist.
   * @param index Le numero de la piste qui vient d'être ajoutée.
   * @param size  Le nombre de piste demandé pour la playlist.
   * @param track La piste qui vient d'être ajoutée.
   */
  void notifyAll(std::size_t index, std::size_t size, const Track &track);
};

} // end namespace SoundCity

#endif
