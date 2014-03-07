#include <../include/Track.h>

using namespace SoundCity;

Track::Track(int id, const SignalData &signal, const ContextData &context) :
  id(id),
  signal(signal),
  context(context)
  {}