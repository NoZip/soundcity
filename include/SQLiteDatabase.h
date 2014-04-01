#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include <string>

#include <sqlite3.h>

#include <TrackPool.h>
#include <OptionList.h>
#include <IDatabase.h>

namespace SoundCity
{

const float POPULARITY_THRESHOLD = 0.1f;

/**
 * Module de base de données SQLite.
 */
class SQLiteDatabase : public IDatabase {
public:
  SQLiteDatabase(const std::string &file);
  virtual ~SQLiteDatabase();

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
  TrackPool select(const OptionList &options, std::size_t size);

protected:
  std::string filename; ///< Le nom du fichier contenant la database.
  sqlite3 *dbConnection; ///< La connection à la database sqlite3.
};
  
} //end namespace SoundCity

#endif
