#include <../include/Track.h>
#include <iostream>
#include <string>

using namespace SoundCity;

int main()
{
  std::string s("Test");
  Artist a(1,s,0.4,1.3);
  std::cout << a.getName() << "\n";
}