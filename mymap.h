#ifndef MYMAP_H_
#define MYMAP_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "tile.h"

const int COORD = 11;
const int SIZE = 9;
const int XVIEW = 4;
const int YVIEW = 4;

class Player;

class Map
{
  private:
    Tile** tiles;
    int** permissions;
    ////////////////////////////////////////////////////////////////////
    //permissions range
    //
    //0: cannot walk on
    //1: can walk
    //2: overlap
    //3: water
    ////////////////////////////////////////////////////////////////////
    int width;
    int height;
    int x_offset;
    int y_offset;
    //int north_offset;
    //int south_offset;
    //int east_offset;
    //int west_offset;
    Map* North;
    Map* West;
    Map* South;
    Map* East;
    string name;
    int number;
    
    Tile create_tile(int, int, int);
        
  public:
    Map();
    Map(string);
    ~Map();
    
    Map* get_north() const {return North;};
    Map* get_west() const {return West;};
    Map* get_south() const {return South;};
    Map* get_east() const {return East;};
    int get_offset() const;
    string get_name() const {return name;};
    int get_number() const {return number;};
    int get_width() const {return width;};
    int get_height() const {return height;};
    int get_x_offset() const {return x_offset;};
    int get_y_offset() const {return y_offset;};
    
    void set_north(Map* m) {North = m;};
    void set_west(Map* m) {West = m;};
    void set_south(Map* m) {South = m;};
    void set_east(Map* m) {East = m;};
    void set_offset(int i);
    
    void draw_map(const Player &p) const;
    bool allowed(int, int) const;
    Tile at(int i, int j) const{ return tiles[i][j];};
};

class Player
{
	private:
	  int px;
	  int py;
	  Image sprite;
	public:
	  Player();
	  Player(const Map&);
	  void draw_player() const;
	  void move(Map*&);
	  
	  void set_loc(int x, int y){px = x; py = y;};
	  
	  int get_px() const {return px;};
	  int get_py() const {return py;};
};

#endif
