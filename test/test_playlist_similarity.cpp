#include <iostream>
#include <OptionList.h>
#include <SQLiteDatabase.h>
#include <SimilarityStrategy.h>
#include <Generator.h>

#define PARAMS 2

using namespace SoundCity;
using std::cout;
using std::endl;

void 
usage (char *s)
{
  fprintf(stderr, "Usage: %s <database> <k> \n", s);
  exit(EXIT_FAILURE);
}

int 
main(int argc, char *argv[])
{
  if (argc != PARAMS+1)
    usage(argv[0]);
  int k = atoi(argv[2]);
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
  int i = 1;
  auto it = playlist.begin();
  for(int n = 0; n < k-1; n++)
  {
    ++i; ++it;
  }
  while(it != playlist.end())
  {
    ++it; ++i;
    auto next = it; ++next;
    auto previous = it;
    for(int n = 0; n < k; n++)
    {
      --previous;
    }
    if(next != playlist.end() && it != playlist.end())
    {
      cout << "Similarité entre le le morceau " << i <<  " et le morceau " << i+1 << " : " << similarity.compute(*it,*next) << endl;
      cout << "Similarité entre le le morceau " << i-k <<  " et le morceau " << i+1 << " : " << similarity.compute(*previous,*next) << endl;
      cout << "Différence " << i << "-" << i+1 << " | " << i-k << "-" << i+1 << " : "<< similarity.compute(*it,*next)-similarity.compute(*previous,*next) << endl;
    }
  }

  return EXIT_SUCCESS;
}
