#include <SignalData.h>
#include <cassert>

using namespace SoundCity;

SignalData::SignalData(float rhythm, float energy, float tonality) :
  rhythm(rhythm),
  energy(energy),
  tonality(tonality)
  {
    assert(rhythm >= 0 && rhythm <= 1);
    assert(energy >= 0 && energy <= 1);
    assert(tonality >= 0 && tonality <= 1);
  }