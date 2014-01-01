#include "world_map.h"

using namespace std;

World_map::World_map()
{
  string map_name;
  
  fstream world_input;
  world_input.open("world_map.txt");
  
  world_input >> width >> height;
  
  maps = new Map**[width];
  for(int i = 0; i < width; i++) maps[i] = new Map*[height];
  for(int j = height - 1; j >= 0; j--)
    for(int i = 0; i < width; i++)
    {    
      world_input >> map_name;
      maps[i][j] = new Map(map_name);
    }
  world_input.close();
  initialize_connections();
}

World_map::~World_map()
{
  for(int i = 0; i < width; i++) delete[] maps[i];
  delete[] maps;
}

void World_map::initialize_connections() 
{
  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      if(maps[i][j]->get_name() != "0" && maps[i][j]->get_name() != "-1")
      {
        maps[i][j]->set_north(north_of(i, j));
        maps[i][j]->set_west(west_of(i, j));
        maps[i][j]->set_south(south_of(i, j));
        maps[i][j]->set_east(east_of(i, j));
      }
}

Map* World_map::north_of(int i, int j)
{
  if((j < height-1) && (maps[i][j+1]->get_name() == "-1")) 
    return north_of(i, j+1);
  else if((j < height-1) && (maps[i][j+1]->get_name() != "0")) 
    return maps[i][j+1];
  else return NULL;
}

Map* World_map::west_of(int i, int j)
{
  if((i > 0) && (maps[i-1][j]->get_name() == "-1"))
    return west_of(i-1, j);
  else if((i > 0) && (maps[i-1][j]->get_name() != "0")) 
    return maps[i-1][j];
  else return NULL;
}

Map* World_map::south_of(int i, int j)
{
  if((j > 0) && (maps[i][j-1]->get_name() == "-1")) 
    return south_of(i, j-1);
  else if((j > 0) && (maps[i][j-1]->get_name() != "0")) 
    return maps[i][j-1];
  else return NULL;
}

Map* World_map::east_of(int i, int j)
{
  if((i < width-1) && (maps[i+1][j]->get_name() == "-1")) 
    return east_of(i+1, j);
  else if((i < width-1) && (maps[i+1][j]->get_name() != "0")) return maps[i+1][j];
  else return NULL;
}
