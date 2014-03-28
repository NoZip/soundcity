#include <iostream>
#include <OptionList.h>
#include <SQLiteDatabase.h>
#include <SimilarityStrategy.h>
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

  SimilarityStrategy similarity;
  SQLiteDatabase database(argv[1]);
  cout << "Crétation d'une liste d'options" << endl;
  OptionList options("",0,0,0,0,0,0,1);
  Generator generator(database, similarity);

  if(generator.initialization() == 0)
  {
    cout << "Erreur d'initialisation" << endl;
    exit(EXIT_FAILURE);
  }
  cout << "Lancement de la génération" << endl;
  Playlist playlist = generator.generate(options);
  cout << "Génération terminée" << endl;
  cout << "Taille de la playlist générée : " << playlist.size() << endl;
  for(auto it = playlist.begin(); it != playlist.end(); ++it)
    cout << (*it).getTitle() << " - " << it->getArtistName() << " (" <<  it->getAlbumReleaseDate() << ")" << endl;


  return EXIT_SUCCESS;
}
