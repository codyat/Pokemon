#include "tile.h"

using namespace std;

Tile::Tile(Point p, string s)
:name1(s), name2("0"), name3("0")
{
  over = false;
  s = "./images/" + s + ".png";
  level1 = Image(p, 1, 1, s);
}

Tile::Tile(Point p, string s1, string s2)
:name1(s1), name2(s2), name3("0")
{
  over = true;
  s1 = "./images/" + s1 + ".png";
  s2 = "./images/" + s2 + ".png";
  level1 = Image(p, 1, 1, s1);
  level2 = Image(p, 1, 1, s2);
}

Tile::Tile(Point p, string s1, string s2, string s3)
:name1(s1), name2(s2), name3(s3)
{
  over = true;
  s1 = "./images/" + s1 + ".png";
  s2 = "./images/" + s2 + ".png";
  s3 = "./images/" + s3 + ".png";
  level1 = Image(p, 1, 1, s1);
  level2 = Image(p, 1, 1, s2);
  level3 = Image(p, 1, 1, s3);
}
