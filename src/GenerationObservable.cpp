#include <GenerationObservable.h>

using namespace SoundCity;

GenerationObservable::GenerationObservable()
{

}

void GenerationObservable::attach(const IGenerationObserver &observer)
{
  linkedObservers.push_back(observer);
}

void GenerationObservable::detach(const IGenerationObserver &observer)
{
  linkedObservers.remove(observer);
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