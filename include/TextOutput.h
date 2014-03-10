#ifndef TEXTOUTPUT_H
#define TEXTOUTPUT_H

#include <cstdio>

#include <Playlist.h>
#include <IOutputStrategy.h>

namespace SoundCity
{
  /**
   * Module de sortie au format texte.
   */
  
  class TextOutput{
  public:
    /**
     * Permet de restituer la playlist générée à l'utilisateur.
     * @param playlist La playlist générée.
     */
    void format(Playlist playlist);
    
  private:
    FILE * file;
  };
}
