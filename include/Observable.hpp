#ifndef OBSERVABLE
#define OBSERVABLE

#include <list> 

namespace SoundCity {

template <class IObserver>
class Observable {
public:
  Observable() {

  }

  ~Observable() {
    for (IObserver *observer : linkedObservers) {
      delete observer;
    }
  }

  /**
   * Attache un observer.
   * @param observer L'observer à ajouter.
   */
  template <class Observer>
  void attach(const Observer &observer) {
    linkedObservers.push_back(new Observer(observer));
  }

  /**
   * Détache un observer.
   * @param observer l'observer à détacher.
   */
  template <class Observer>
  void detach(const Observer &observer) {
    linkedObservers.remove(new Observer(observer));
  }

protected:
  std::list<IObserver*> linkedObservers; ///< Liste d'observers interne.
};

} // end namespace SoundCity

#endif
