#include <Track.h>
#include <cassert>

using namespace SoundCity;

Track::Track(int id, const std::string &title, const SignalData &signal, const ContextData &context) :
  id(id),
  title(title),
  signal(signal),
  context(context)
  {
    assert(id >= 0);
    assert(&title);
    assert(&signal);
    assert(&context);
  }