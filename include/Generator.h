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
    Generator(const IDatabase &db,
	      const ISelectionObservable &selection_feedback,
	      const IGenerationObservable &generation_feedback, 
	      const ISimilarityStrategy &similarity);

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
    IDatabase db;
    ISelectionObservable selection_feedback;
    IGenerationObservable generation_feedback;
    ISimilarityStrategy similarity;
    
  };
}

#endif
