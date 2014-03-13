#include <GenerationObservable.h>

using namespace SoundCity;

GenerationObservable::GenerationObservable()
: Observable<IGenerationObserver>() {

}

void GenerationObservable::notifyAll(
  std::size_t index,
  std::size_t size,
  const Track &track
)
{
  for (IGenerationObserver &observer : linkedObservers)
  {
    observer.notify(index, size, track);
  }
}
