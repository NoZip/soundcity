#include <Track.h>
#include <cassert>

using namespace SoundCity;

Track::Track(int id, const SignalData &signal, const ContextData &context) :
  id(id),
  signal(signal),
  context(context)
  {
    assert(id);
    assert(&signal);
    assert(&context);
  }