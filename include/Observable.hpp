#ifndef OBSERVABLE
#define OBSERVABLE

#include <list> 

namespace SoundCity {

template <class Observer>
class Observable {
public:
  Observable() {

  }

  ~Observable() {
    for (Observer *observer : linkedObservers) {
      delete observer;
    }
  }

  /**
   * Attache un observer.
   * @param observer L'observer à ajouter.
   */
  void attach(const Observer &observer) {
    linkedObservers.push_back(new Observer(observer));
  }

  /**
   * Détache un observer.
   * @param observer l'observer à détacher.
   */
  void detach(const Observer &observer) {
    linkedObservers.remove(new Observer(observer));
  }

protected:
  std::list<Observer*> linkedObservers; ///< Liste d'observers interne.
};

} // end namespace SoundCity

#endif
