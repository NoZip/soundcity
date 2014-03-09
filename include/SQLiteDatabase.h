#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include <list>
#include <string>

#include <TrackPool.h>
#include <IDatabase.h>

namespace SoundCity
{
  /**
   * Module de base de données SQLite.
   */
  class SQLiteDatabase{
 public:
  SQLiteDatabase();

  /**
   * Initialise et vérifie que la base de données est présente
   * et fonctionnelle.
   */
  int initialization();

  /**
   * Sélectionne des morceaux correspondants aux options
   * passées en paramètres.
   * @param options Une liste des options pour la
   * sélection des morceaux.
   * @param size le nombre de morceaux à sélectionner.
   */
  
  TrackPool select(std::list<std::string> options,
    std::size_t size);
};
  
} //end namespace SoundCity

#endif
