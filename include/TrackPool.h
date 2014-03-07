#ifndef TRACKPOOL_H
#define TRACKPOOL_H

#include <unordered_set>
#include <functional>

#include <Track.h>

/*
  Fichier de test, je suis absolument pas sûr que ça marche.
 */

/**
 * Spécialisation de template pour pouvoir créer un set de pistes.
 * @see http://www.cplusplus.com/reference/unordered_set/unordered_set/
 */
template <>
struct std::hash<SoundCity::Track> {
  std::size_t operator(const SoundCity::Track &track) {
    return std::hash<int>()(track.getId());
  }
};

namespace Soundcity {
  /**
   * Définition de Trackpool.
   */
  using TrackPool = std::set<Track>;
}



#endif