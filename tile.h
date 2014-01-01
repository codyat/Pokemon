#ifndef TILE_H_
#define TILE_H_

#include <iostream>
#include "instinct.h"

class Tile
{
  private:
    Image level1;
    Image level2;
    Image level3;
    string name1;
    string name2;
    string name3;
    bool over;
  public:
    Tile(){over = false;};
    Tile(Point, string);
    Tile(Point, string, string);
    Tile(Point, string, string, string);
    Image get_image() const {return level1;};
    Image get_image2() const {return level2;};
    Image get_image3() const {return level3;};
    bool get_over() const {return over;};
    
    string get_file1() const {return name1;};
    string get_file2() const {return name2;};
    string get_file3() const {return name3;};
    
};

#endif
