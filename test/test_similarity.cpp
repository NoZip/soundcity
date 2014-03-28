#include <Track.h>
#include <SimilarityStrategy.h>
#include <iostream>
#include <cassert>

using namespace SoundCity;
using namespace std;

int main()
{
  Artist artist1(1, "The White Stripes", 0.4, 1.0);
  Album album1(1, "Elephant", "The White Stripes", 2012);
  ContextData data1(artist1, album1, 0.5);
  SignalData sign1(0.2,0.3,0.4);
  Track track1(1, "Seven Nations Army", sign1 ,data1);

  Artist artist2(2, "The Strokes", 0.4, 1.0);
  Album album2(2, "Room On Fire", "The Strokes", 2003 );
  ContextData data2(artist2, album2, 0.5);
  SignalData sign2(0.2,0.3,0.5);
  Track track2(2, "Reptilia", sign2, data2);

  Artist artist3(3, "Jacques Brel", 0.4, 1.0);
  Album album3(3, "Ces gens-là", "Jacques Brel" ,1965);
  ContextData data3(artist3, album3, 0.5);
  SignalData sign3(0.8,0.8,0.8);
  Track track3(3, "Ces gens-là", sign3, data3);

  SimilarityStrategy similarity;
  assert(similarity.compute(track1, track1) == 1);
  cout << "similarity( track1, track1 ) == 1\n" << endl;

  cout << similarity.compute(track1, track2) << " = similarity t1, t2\n" << endl;
  cout << similarity.compute(track2, track3) << " = similarity t1, t3 \n" << endl;
  //assert(similarity.compute(track1, track2) > similarity.compute(track1, track3));
  //cout << "similarity( track1, track 2 ) >  similarity( track1, track3 )" << endl;

}
