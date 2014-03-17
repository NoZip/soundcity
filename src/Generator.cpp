#include <Generator.h>
#include <IDatabase.h>
#include <OptionList.h>
#include <TrackPool.h>
#include <cassert>

using namespace SoundCity;
const float SIMILARITY_THRESHOLD = 0.5;

Generator::Generator(IDatabase &db, const ISimilarityStrategy &similarity) :
similarity(similarity),
selectionFeedback(),
generationFeedback(),
db(db)
{
  assert(&similarity);
  assert(&selectionFeedback);
  assert(&generationFeedback);
  assert(&db);
}

int Generator::initialization() const
{
  return db.initialization();
}

void generationLoop(Playlist playlist, TrackPool pool, std::size_t size, const ISimilarityStrategy &similarity)
{
  Track first = *pool.begin();
  playlist.push_back(first);
  pool.erase(first);
  Track actual = first;
  float total = 0;
  while(playlist.size() < size || pool.size() > 0)
  {
    float max = 0;
    Track * next;
    for(auto it = pool.begin(); it != pool.end(); ++it)
    {
      Track track = *it;
      float sim = similarity.compute(actual,track);
      if(sim > max)
      {
        max = sim;
        next = &track;
      }
    }
    playlist.push_back(*next);
    pool.erase(*next);
    actual = *next;
    total += max;
  }
  if(total/playlist.size() > SIMILARITY_THRESHOLD)
  {
    playlist.setValid(1);
  }
}

Playlist Generator::generate(OptionList optionList)
{
  TrackPool pool = db.select(optionList,optionList.getSize()*10);
  Playlist playlist;
  if(pool.size() == 0)
    return playlist;
  generationLoop(playlist, pool, optionList.getSize(), similarity);
  return playlist;
}

Playlist Generator::regenerate(OptionList optionList, Playlist playlist)
{
  TrackPool pool = db.select(optionList,optionList.getSize()*10);
  Playlist newPlaylist;
  if(pool.size() == 0)
    return playlist;
  for(auto it = playlist.begin(); it != playlist.end(); ++it)
    pool.insert(*it);
  generationLoop(newPlaylist, pool, optionList.getSize(), similarity);
  return newPlaylist;
}