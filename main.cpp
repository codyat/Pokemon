#include "world_map.h"

using namespace std;

bool is_in(Point, Rect);

int instinct_main()
{
  win.set_title("Pokemon Peridot");
  win.set_window_size(600, 600);
  win.coord(0, 0, COORD, COORD);
  win.set_background_color(BLACK);
  //////////////////////////////////////////////////////////////////////
  //adds menu for load and new game
  //////////////////////////////////////////////////////////////////////  
  
  Image background = Image(Point(0, 2), COORD, COORD-2, "./images_1/title_screen.png");
  Rect new_game = Rect(Point(1, .5), 3, 1, CYAN);
  Message new_game_m = Message(Point(1.5, 1), "New Game", WHITE);
  Rect load = Rect(Point(6, .5), 3, 1, CYAN);
  Message load_m = Message(Point(6.5, 1), "Load", WHITE);
  win << background << new_game << new_game_m << load << load_m;
  win.output_buffer();
  
  while(true)
  {
    if(win.left_mouse_down())
    {
      Point p = win.get_mouse_loc();
      if(is_in(p, new_game)) break;
    }
  }
  win.clear_buffer();
  //////////////////////////////////////////////////////////////////////
  // menu complete
  //////////////////////////////////////////////////////////////////////
  //builds world_map
  //constructs the map of "Maps"
  World_map world;
  
  //builds the first map
  //constructs a map of tiles
  
  Map* m = world.get_start();
  
  //constructs a player
  Player p(*m);
  
  //loop for movements
  
  m->draw_map(p);
  while(true) p.move(m);
  return 0;
}

bool is_in(Point p, Rect r)
{
  return (p.get_x() > r.get_lower_left().get_x() &&
          p.get_x() < r.get_lower_left().get_x() + r.get_width() &&
          p.get_y() > r.get_lower_left().get_y() &&
          p.get_y() < r.get_lower_left().get_y() + r.get_height());
}
