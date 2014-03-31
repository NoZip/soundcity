#include <iostream>
#include <OptionList.h>
#include <SQLiteDatabase.h>
#include <NaiveSimilarityStrategy.h>
#include <Generator.h>

#define PARAMS 1

using namespace SoundCity;
using std::cout;
using std::endl;

void 
usage (char *s)
{
  fprintf(stderr, "Usage: %s <database>\n", s);
  exit(EXIT_FAILURE);
}

int 
main(int argc, char *argv[])
{
  if (argc != PARAMS+1)
    usage(argv[0]);

  NaiveSimilarityStrategy similarity;
  SQLiteDatabase database(argv[1]);
  cout << "Crétation d'une liste d'options" << endl;
  OptionList options("",0,0,0,0,0,0,10);
  Generator generator(database, similarity);

  if(generator.initialization() == 0)
  {
    cout << "Erreur d'initialisation" << endl;
    exit(EXIT_FAILURE);
  }
  cout << "Lancement de la génération" << endl;
  Playlist playlist = generator.generate(options);
  cout << "Génération terminée" << endl;
  for(auto it = playlist.begin(); it != playlist.end(); ++it)
    cout << (*it).getTitle() << " - " << it->getArtistName() << " (" <<  it->getAlbumReleaseDate() << ")" << endl;
  cout << "Taille de la playlist générée : " << playlist.size() << endl;


  return EXIT_SUCCESS;
}
