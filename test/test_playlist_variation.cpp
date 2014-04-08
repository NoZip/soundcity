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
  OptionList options("",1,3000,0,0,0,0,25);
  Generator generator(database, similarity);

  if(generator.initialization() == 0)
  {
    cout << "Erreur d'initialisation" << endl;
    exit(EXIT_FAILURE);
  }
  Playlist playlist = generator.generate(options);
  auto first = playlist.begin();
  int i = 1;
  for(auto it = playlist.begin(); it != playlist.end(); ++it)
    cout << "Similarité entre le morceau 1 et " << i++ << " : " << similarity.compute(*first,*it) << endl;


  return EXIT_SUCCESS;
}