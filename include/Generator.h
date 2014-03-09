#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include <list>

#include <IDatabase.h>
#include <ISimilarityStrategy.h>
#include <ISelectionObserver.h>
#include <IGenerationObserver.h>
#include <Playlist.h>

namespace SoundCity
{
  /**
   * Classe contenant les données pour le générateur
   */
  class Generator{
  public:
    Generator(const Database &db,
	      const SelectionObservable &selection_feedback,
	      const GenerationObservable &generation_feedback, 
	      const SimilarityStrategy &similarity);

    /**
     * Initialise le générateur et vérifie que tout est 
     * fonctionnel.
     */
    int initialization();
    
    /**
     * Génère la playlist
     * @param options Une liste des options pour la génération.
     * @param size La taille de la playlist à générer.
     * @param is_duration indique si la durée est en nombre de 
     * morceaux ou en temps
     */
    Playlist generate(std::list<std::string> options,
		      std::size_t size, 
		      int is_duration);
    
    /**
     * Regénère la playlist
     */
    Playlist regenerate(std::list<std::string> options, 
			Playlist playlist);

  private:
    Database db;
    SelectionObservable selection_feedback;
    GenerationObservable generation_feedback;
    SimilarityStrategy similarity;
    
  };
}

#endif
