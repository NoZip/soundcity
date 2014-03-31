#include <SelectionObservable.h>

using namespace SoundCity;

SelectionObservable::SelectionObservable()
: Observable<ISelectionObserver>() {

}

void SelectionObservable::notifyAll(std::size_t size, const TrackPool &pool)
{
  for (ISelectionObserver *observer : linkedObservers)
  {
    observer->notify(size, pool);
  }
}
