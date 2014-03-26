#include <Generator.h>
#include <IDatabase.h>
#include <OptionList.h>
#include <TrackPool.h>
#include <cassert>

using namespace SoundCity;
const float SIMILARITY_THRESHOLD = 0.5;
const int POOL_SIZE_FACTOR = 10; //Taille de la pool en fonction de la taille de la playlist demandée

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

void generationLoop(Playlist playlist, TrackPool pool, std::size_t playlistSizeToReach, const ISimilarityStrategy &similarity)
{
  //On place le premier morceau de la pool dans la playlist
  Track poolFirstTrack = *pool.begin();
  playlist.push_back(poolFirstTrack);
  pool.erase(poolFirstTrack);

  Track playlistLastTrack = poolFirstTrack; //Dernier morceau dans la playlist
  Track playlistFirstTrack = poolFirstTrack; //Premier morceau de la playlist
  float playlistSimilarity = 0; //Initialisation du score de similarité de la playlist

  //Boucle de remplissage de la playlist
  while(playlist.size() < playlistSizeToReach || pool.size() > 0)
  {
    float maxSimilarityAtStart = 0;
    Track * bestTrackAtStart;
    float maxSimilarityAtEnd = 0;
    Track * bestTrackAtEnd;
    //Recherche du morceau à ajouter dans la pool
    for(auto it = pool.begin(); it != pool.end(); ++it)
    {
      Track actual = *it;
      //On calcule la similarité avec le premier morceau de la playlist
      float similarityAtStart = similarity.compute(playlistFirstTrack,actual);
      //On cherche le morceau le plus similaire
      if(similarityAtStart > maxSimilarityAtStart)
      {
        maxSimilarityAtStart = similarityAtStart;
        bestTrackAtStart = &actual;
      }
      //Même opération que précédent avec le dernier morceau de la playlist
      float similarityAtEnd = similarity.compute(playlistLastTrack,actual);
      if(similarityAtEnd > maxSimilarityAtEnd)
      {
        maxSimilarityAtEnd = similarityAtEnd;
        bestTrackAtEnd = &actual;
      }
    }

    //On ajoute le morceau le plus similaire à l'extrimité
    if(maxSimilarityAtStart > maxSimilarityAtEnd)
    {
      playlist.push_front(*bestTrackAtStart);
      pool.erase(*bestTrackAtStart);
      playlistFirstTrack = *bestTrackAtStart;
      playlistSimilarity += maxSimilarityAtStart;
    }
    else
    {
      playlist.push_back(*bestTrackAtEnd);
      pool.erase(*bestTrackAtEnd);
      playlistLastTrack = *bestTrackAtEnd;
      playlistSimilarity += maxSimilarityAtEnd;
    }
  }
  //Vérification finale de la playlist
  if(playlistSimilarity/playlist.size() > SIMILARITY_THRESHOLD && playlist.size() == playlistSizeToReach)
  {
    playlist.setValid(1);
  }
}

Playlist Generator::generate(OptionList optionList)
{
  //Recupération d'une pool de morceaux
  TrackPool pool = db.select(optionList,optionList.getSize()*POOL_SIZE_FACTOR);
  Playlist playlist;
  if(pool.size() == 0)
    return playlist;
  //On lance la génération
  generationLoop(playlist, pool, optionList.getSize(), similarity);
  return playlist;
}

Playlist Generator::regenerate(OptionList optionList, Playlist playlist)
{
  //Recupération d'une pool de morceaux
  TrackPool pool = db.select(optionList,optionList.getSize()*POOL_SIZE_FACTOR);
  if(pool.size() == 0)
    return playlist;
  //On remplit la pool avec les morceaux de la playlist précédente
  for(auto it = playlist.begin(); it != playlist.end(); ++it)
    pool.insert(*it);
  Playlist newPlaylist;
  //On lance la génération
  generationLoop(newPlaylist, pool, optionList.getSize(), similarity);
  return newPlaylist;
}