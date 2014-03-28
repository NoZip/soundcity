#ifndef TEXTOUTPUT_H
#define TEXTOUTPUT_H

#include <fstream>

#include <Playlist.h>
#include <IOutputStrategy.h>

namespace SoundCity
{
  /**
   * Module de sortie au format texte.
   */
  
  class TextOutput : public IOutputStrategy{
  public:
    /**
     * Permet de restituer la playlist générée à l'utilisateur.
     * @param playlist La playlist générée.
     */
    void format(Playlist &playlist);
    
  private:
    std::ofstream file;
  };
}

#endif //TEXTOUTPUT_H