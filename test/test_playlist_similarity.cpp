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
  int i = 1;
  for(auto it = playlist.begin(); it != playlist.end();)
  {
    ++it; ++i;
    auto next = it; ++next;
    auto previous = it; --previous;
    if(next != playlist.end() && it != playlist.end())
    {
      cout << "Similarité entre le le morceau " << i <<  " et le morceau " << i+1 << " : " << similarity.compute(*it,*next) << endl;
      cout << "Similarité entre le le morceau " << i-1 <<  " et le morceau " << i+1 << " : " << similarity.compute(*previous,*next) << endl;
    }
  }

  return EXIT_SUCCESS;
}
