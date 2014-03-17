#include <OptionList.h>
#include <cassert>

using namespace SoundCity;

OptionList::OptionList(const std::string &artist, int startYear, int endYear, float popularity, float energy, float rhythm, float mood, std::size_t size):
  artist(artist),
  startYear(startYear),
  endYear(endYear),
  popularity(popularity),
  energy(energy),
  rhythm(rhythm),
  mood(mood),
  size(size)
  {
    assert(popularity >= 0 && popularity <= 1);
    assert(energy >= 0 && energy <= 1);
    assert(rhythm >= 0 && rhythm <= 1);
    assert(mood >= 0 && mood <= 1);
    assert(size > 0);
  }