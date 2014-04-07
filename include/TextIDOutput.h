#ifndef TEXTIDOUTPUT_H
#define TEXTIDOUTPUT_H

#include <fstream>
#include <string>

#include <Playlist.h>
#include <IOutputStrategy.h>

namespace SoundCity
{
  /**
   * Module de sortie au format texte.
   */
  
  class TextIDOutput : public IOutputStrategy{
  public:
    TextIDOutput();
    /**
     * Permet de restituer la playlist générée à l'utilisateur.
     * @param playlist La playlist générée.
     */
    void format(std::string fileName, Playlist playlist);
    
  private:
    std::ofstream file;
  };
}

#endif //TEXTIDOUTPUT_H