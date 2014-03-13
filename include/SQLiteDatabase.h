#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include <string>

#include <sqlite3.h>

#include <TrackPool.h>
#include <OptionList.h>
#include <IDatabase.h>

namespace SoundCity
{

/**
 * Module de base de données SQLite.
 */
class SQLiteDatabase : public IDatabase {
public:
  SQLiteDatabase(const std::string &filename);

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
  std::string filename;
  sqlite3 *dbConnection;
  sqlite3_stmt *preparedRequest;
};
  
} //end namespace SoundCity

#endif
