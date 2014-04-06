#include <iostream>
#include <string.h>
#include <OptionList.h>
#include <SQLiteDatabase.h>
#include <SimilarityStrategy.h>
#include <Generator.h>
#include <TextOutput.h>

#define PARAMS 1

using namespace SoundCity;
using std::cout;
using std::endl;
using std::cin;
using std::string;

class GenerationObserver : public IGenerationObserver
{
  void notify(std::size_t index, std::size_t size, const Track &track)
  {
    float percent = ((float) index / (float) size) * 100;
    cout << (int) percent << "%\t";
    cout << track.getTitle() << " by " << track.getArtistName() << endl;
  }
};

void 
usage (char *s)
{
  fprintf(stderr, "Usage: %s <database>\n", s);

  fprintf(stderr, "Options :\n");

  fprintf(stderr, "-h : Affiche l'aide.\n");

  fprintf(stderr, "-y <startYear[1-3000]> <endYear[1-3000]> : Définit un intervalle d'années de morceaux.\n");

  fprintf(stderr, "-e <energy[0.0-1.0]> : Impose une valeur d'énergie dans la playlist générée.\n");

  fprintf(stderr, "-p <popularity[0.0-1.0]> : Impose une valeur de popularité dans la playlist générée.\n");

  fprintf(stderr, "-r <rhythm[0.0-1.0]> : Impose un rythme dans la playlist générée.\n");

  fprintf(stderr, "-m <mood[0.0-1.0]> : Impose une humeur dans la playlist générée (plus la valeur est grande plus le morceau est joyeux).\n");

  fprintf(stderr, "-s <size[1-100]> : Choix de la taille de la playlist générée (10 par défaut).\n");

  fprintf(stderr, "-o <fileName> : Choix du nom du fichier de sortie.\n");

  fprintf(stderr, "-v : activation du mode verbeux.\n");
  exit(EXIT_FAILURE);
}

int 
main(int argc, char *argv[])
{
  if (argc < PARAMS+1)
    usage(argv[0]);

  cout << "Création de la liste d'options." << endl; 

  int size = 10;
  float energy = 0;
  float mood = 0;
  float rhythm = 0;
  float popularity = 0;
  int startYear = 0;
  int endYear = 3000;
  string fileName = "playlist.txt";
  bool verbose = false;

  //Lecture des paramètres
  for(int i = PARAMS; i < argc; ++i)
  {
    if(strcmp(argv[i],"-h") == 0) usage(argv[0]);
    else if(strcmp(argv[i],"-e") == 0) energy = atof(argv[++i]);
    else if(strcmp(argv[i],"-s") == 0) size = atoi(argv[++i]);
    else if(strcmp(argv[i],"-m") == 0) mood = atof(argv[++i]);
    else if(strcmp(argv[i],"-p") == 0) popularity = atof(argv[++i]);
    else if(strcmp(argv[i],"-r") == 0) rhythm = atof(argv[++i]);
    else if(strcmp(argv[i],"-o") == 0) fileName = argv[++i];
    else if(strcmp(argv[i],"-y") == 0)
    {
      startYear = atoi(argv[++i]);
      endYear = atoi(argv[++i]);
    }
    else if(strcmp(argv[i],"-v") == 0) verbose = true;
  }

  //Création de la liste d'options
  OptionList options("",startYear,endYear,popularity,energy,rhythm,mood,size);

  cout << "Initialisation du générateur." << endl;
  SimilarityStrategy similarity;
  SQLiteDatabase database(argv[1]);
  Generator generator(database, similarity);
  if (verbose) generator.getGenerationObservable().attach(GenerationObserver());

  if(generator.initialization() == 0)
  {
    cout << "Erreur d'initialisation." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Lancement de la génération" << endl;
  Playlist playlist = generator.generate(options);
  cout << "Génération terminée" << endl;
  if(!playlist.isValid())
  {
    cout << "La génération n'a pas été satisfaisante, voulez-vous relancer une génération ? (O/N) : ";
    char answer;
    cin >> answer;
    if(answer == 'o' || answer == 'O')
    {
      cout << "Lancement de la re-génération" << endl;
      generator.regenerate(options, playlist);
      cout << "Re-génération terminée" << endl;
    }
  }
  TextOutput output;
  output.format(fileName,playlist);
  cout << "Taille de la playlist générée : " << playlist.size() << endl;


  return EXIT_SUCCESS;
}
