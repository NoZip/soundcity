#include <iostream>

#include <OptionList.h>
#include <SQLiteDatabase.h>

using namespace SoundCity;
using namespace std;

int main(int argc, char * argv[])
{
  SQLiteDatabase db(argv[1]);
  int poolSize = atoi(argv[2]);
  int startYear = atoi(argv[3]);
  int endYear = atoi(argv[4]);
  float popularity = atof(argv[5]);

  OptionList options("", startYear, endYear, popularity, 0, 0, 0, 10);
  db.initialization();
  TrackPool pool = db.select(options, poolSize);

  cout << pool.size() << endl;

  for (const Track &track : pool)
  {
    cout << track.getTitle()
         << " "
         << track.getContextData().getArtist().getName()
         << " "
         << track.getContextData().getAlbum().getReleaseDate()
         << " "
         << track.getContextData().getArtist().getFamiliarity()
         << endl;
  }
}
