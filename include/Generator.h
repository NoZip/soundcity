#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include <list>

#include <IDatabase.h>
#include <ISimilarityStrategy.h>
#include <SelectionObservable.h>
#include <GenerationObservable.h>
#include <Playlist.h>
#include <OptionList.h>

namespace SoundCity
{
  /**
   * Classe contenant les données pour le générateur
   */
  class Generator{
  public:
    Generator(IDatabase &db, const ISimilarityStrategy &similarity);

    SelectionObservable& getSelectionObservable() {return selectionFeedback;}
    GenerationObservable& getGenerationObservable() {return generationFeedback;}

    /**
     * Initialise le générateur et vérifie que tout est 
     * fonctionnel.
     */
    int initialization() const;
    
    /**
     * Génère la playlist
     * @param optionList Une liste des options pour la génération.
     */
    Playlist generate(OptionList optionList);
    
    /**
     * Regénère la playlist
     */
    Playlist regenerate(OptionList optionList, Playlist playlist);

  protected:
    void generationLoop(Playlist * playlist, TrackPool &pool, std::size_t playlistSizeToReach);

    IDatabase &db;
    SelectionObservable selectionFeedback;
    GenerationObservable generationFeedback;
    const ISimilarityStrategy &similarity;
    
  };
}

#endif
