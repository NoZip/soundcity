#include <iostream>

#include <OptionList.h>
#include <SQLiteDatabase.h>

using namespace SoundCity;
using namespace std;

int main(int argc, char * argv[])
{
  SQLiteDatabase db(argv[1]);
  OptionList options("", 0, 0, 0, 0, 0, 0, 10);
  db.initialization();
  TrackPool pool = db.select(options, 10);

  //cout << pool.size() << endl;

  for (const Track &track : pool)
  {
    cout << track.getTitle()
         << " (" << track.getRhythm() << ", "
         << track.getEnergy() << ")" << endl;
  }
}
