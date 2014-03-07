#include <SelectionObservable.h>

using namespace SoundCity;

SelectionObservable::SelectionObservable()
{

}

void SelectionObservable::attach(const ISelectionObserver &observer)
{
  linkedObservers.push_back(observer);
}

void SelectionObservable::detach(const ISelectionObserver &observer)
{
  linkedObservers.remove(observer);
}

void SelectionObservable::notifyAll(std::size_t size, const TrackPool &pool)
{
  for (ISelectionObserver &observer : linkedObservers)
  {
    observer.notify(size, pool);
  }
}