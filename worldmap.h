#ifndef WORLD_MAP_H_
#define WORLD_MAP_H_

#include "mymap.h"

class World_map
{
  private:
    Map*** maps;
    void initialize_connections();
    int width;
    int height;
  public:
    World_map();
    ~World_map();
    Map* north_of(int, int);
    Map* west_of(int, int);
    Map* south_of(int, int);
    Map* east_of(int, int);
    Map* get_start() const {return maps[2][3];};
};

#endif
