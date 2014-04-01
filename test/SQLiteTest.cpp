
#include <cmath>
#include <string>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

#include <OptionList.h>
#include <TrackPool.h>
#include <SQLiteDatabase.h>

const std::string DB_FILENAME = "../../scripts/test2.sqlite";
const int POOL_SIZE = 100;

using namespace SoundCity;

class SQLiteTest : public CppUnit::TestFixture
{
private:
  SQLiteDatabase *db;

public:
  void setUp()
  {
    db = new SQLiteDatabase(DB_FILENAME);
    db->initialization();
  }

  void tearDown()
  {
    delete db;
  }

  void random()
  {
    OptionList options("", 0, 0, 0.f, 0, 0, 0, 10);

    TrackPool pool1 = db->select(options, POOL_SIZE);
    TrackPool pool2 = db->select(options, POOL_SIZE);

    bool identical = true;
    for (const Track &track : pool1) {
      auto it = pool2.find(track);

      if (it == pool1.end())
      {
        identical = false;
        break;
      }
    }

    CPPUNIT_ASSERT(!identical);
  }

  void yearFiltering()
  {
    static const int START_YEAR = 1990;
    static const int END_YEAR = 2000;

    OptionList options("", START_YEAR, END_YEAR, 0.f, 0, 0, 0, 10);

    TrackPool pool = db->select(options, POOL_SIZE);

    for (const Track &track : pool)
    {
      int release = track.getContextData().getAlbum().getReleaseDate();

      CPPUNIT_ASSERT(release >= START_YEAR && release <= END_YEAR);
    }
  }

  void popularityFiltering()
  {
    static const float POPULARITY = 0.8;

    OptionList options("", 0, 0, POPULARITY, 0, 0, 0, 10);

    TrackPool pool = db->select(options, POOL_SIZE);

    for (const Track &track : pool)
    {
      float popularity = track.getContextData().getArtist().getFamiliarity();

      CPPUNIT_ASSERT(abs(POPULARITY - popularity) < POPULARITY_THRESHOLD);
    }
  }

  CPPUNIT_TEST_SUITE( SQLiteTest );
  CPPUNIT_TEST( random );
  CPPUNIT_TEST( yearFiltering );
  CPPUNIT_TEST( popularityFiltering );
  CPPUNIT_TEST_SUITE_END();
};


int main(int argc, const char *argv[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( SQLiteTest::suite() );
  runner.run();
  return 0;
}
