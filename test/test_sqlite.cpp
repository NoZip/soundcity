#include <iostream>

#include <OptionList.h>
#include <SQLiteDatabase.h>

using namespace SoundCity;
using namespace std;

int main(int argc, char * argv[])
{
  SQLiteDatabase db(argv[1]);
  OptionList options("", 0, 0, 0, 0, 0, 0);
  db.initialization();
  TrackPool pool = db.select(options, 10);

  //cout << pool.size() << endl;

  for (const Track &track : pool)
  {
    cout << track.getArtistName() << " - " << track.getAlbumTitle() << endl;
  }
}
// 
// #include <stdio.h>
// #include <sqlite3.h>
// #include <string>

// static int callback(void *NotUsed, int argc, char **argv, char **azColName){
// int i;
// for(i=0; i<argc; i++){
// printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
// }
// printf("\n");
//     return 0;
//   }
  
//   int main(int argc, char **argv){
//     sqlite3 *db;
//     char *zErrMsg = 0;
//     int rc;
  
//     if( argc!=3 ){
//       fprintf(stderr, "Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
//       return(1);
//     }
//     printf("Database: %s", argv[1]);
//     rc = sqlite3_open_v2(std::string(argv[1]).c_str(), &db, SQLITE_OPEN_READONLY, nullptr);
//     if( rc ){
//       fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//       sqlite3_close(db);
//       return(1);
//     }
//     rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
//     if( rc!=SQLITE_OK ){
//       fprintf(stderr, "SQL error: %s\n", zErrMsg);
//       sqlite3_free(zErrMsg);
//     }
//     sqlite3_close(db);
//     return 0;
//   }
