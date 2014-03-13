#ifndef TRACKPOOL_H
#define TRACKPOOL_H

#include <unordered_set>
#include <functional>

#include <Track.h>

/*
  Fichier de test, je suis absolument pas sûr que ça marche.
 */

namespace std {
/**
 * Spécialisation de template pour pouvoir créer un set de pistes.
 * @see http://www.cplusplus.com/reference/unordered_set/unordered_set/
 */
template <>
struct hash<SoundCity::Track> {
  std::size_t operator()(const SoundCity::Track &track) const {
    return std::hash<int>()(track.getId());
  }
};
}

namespace SoundCity {
  /**
   * Définition de Trackpool.
   * @see http://www.cplusplus.com/reference/unordered_set/unordered_set/
   */
  using TrackPool = std::unordered_set<Track>;
}



#endif