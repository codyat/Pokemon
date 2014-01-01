#include "mymap.h"

using namespace std;

Map::Map()
:width(0), height(0), x_offset(0), y_offset(0), North(NULL), West(NULL), South(NULL), East(NULL),
name(""), number(0)
{
}

Map::Map(string s)
:North(NULL), West(NULL), South(NULL), East(NULL), name(s), number(0)
{
  s = "./maps/" + s + ".txt";
  
  fstream input;
  input.open(s.c_str());
  
  input >> width >> height >> x_offset >> y_offset;
  
  tiles = new Tile*[width];
  permissions = new int*[width];
  for(int i = 0; i < width; i++)
  {
    tiles[i] = new Tile[height];
    permissions[i] = new int[height];
  }
  
  int number;
  for(int j = height - 1; j >= 0; j--)
    for(int i = 0; i < width; i++)
    {
      input >> number;
      tiles[i][j] = create_tile(number, i, j);
    }
  
  input >> number;
  for(int j = height - 1; j >= 0; j--)
    for(int i = 0; i < width; i++)
      input >> permissions[i][j];
  
  input.close();
}

Map::~Map()
{
  for(int i = 0; i < width; i++) 
  {
    if(tiles[i]) delete[] tiles[i];
    if(permissions[i]) delete[] permissions[i];
  }
  if(tiles) delete[] tiles;
  if(permissions) delete[] permissions;
  if(North) delete North;
  if(West) delete West;
  if(South) delete South;
  if(East) delete East;
}

void Map::draw_map(const Player &p) const
{
  int x = p.get_px();
  int y = p.get_py();
  int off_x;
  int off_y;
  vector<Tile> second_layer;
  win.clear_buffer();

  for(int i = x - XVIEW; i < x + XVIEW + 1; i++)
    for(int j = y - YVIEW; j < y + YVIEW + 1; j++)
    {
      if(j >= height && North)//y too high
      {
        off_y = j - height;
        if(i + North->x_offset >= North->width && North->East)//x and y too high
        {
          off_x = i - North->width;
          Tile t(Point(i, j), North->East->tiles[off_x][off_y].get_file1(),
                              North->East->tiles[off_x][off_y].get_file2());
          win << t.get_image();
          if(t.get_over()) win << t.get_image2();
          if(North->East->permissions[off_x][off_y] == 2)
            second_layer.push_back(t);
        }
        else if(i + North->x_offset < 0 && North->West)//x too low and y too high
        {
          off_x = North->West->width + i;
          Tile t(Point(i, j), North->West->tiles[off_x][off_y].get_file1(),
                              North->West->tiles[off_x][off_y].get_file2());
          win << t.get_image();
          if(t.get_over()) win << t.get_image2();
          if(North->West->permissions[off_x][off_y] == 2)
            second_layer.push_back(t);
        }
        else if(i + North->x_offset >= 0 && i + North->x_offset < North->width)//y too high and x in bounds
        {
          Tile t(Point(i, j), North->tiles[i + North->x_offset][off_y].get_file1(),
                              North->tiles[i + North->x_offset][off_y].get_file2());
          win << t.get_image();
          if(t.get_over()) win << t.get_image2();
          if(North->permissions[i + North->x_offset][off_y] == 2)
            second_layer.push_back(t);
        }
        else if(i + North->x_offset >= North->width && !North->East 
                || i + North->x_offset < 0 && !North->West)
        {
          Tile t(Point(i,j), "0");
          win << t.get_image();
        }
      }
      if(j < 0 && South)
      {
        off_y = South->height + j;
        if(i - x_offset >= South->width && South->East)//x and y too high
        {
          off_x = i - South->width;
          Tile t(Point(i, j), South->East->tiles[off_x][off_y].get_file1(),
                              South->East->tiles[off_x][off_y].get_file2());
          win << t.get_image();
          if(t.get_over()) win << t.get_image2();
          if(South->East->permissions[off_x][off_y] == 2)
            second_layer.push_back(t);
        }
        else if(i - x_offset < 0 && South->West)//x too low and y too high
        {
          off_x = South->West->width + i;
          Tile t(Point(i, j), South->West->tiles[off_x][off_y].get_file1(),
                              South->West->tiles[off_x][off_y].get_file2());
          win << t.get_image();
          if(t.get_over()) win << t.get_image2();
          if(South->West->permissions[off_x][off_y] == 2)
            second_layer.push_back(t);
        }
        else if(i - x_offset >= 0 && i - x_offset < South->width)//y too high and x in bounds
        {
          Tile t(Point(i, j), South->tiles[i - x_offset][off_y].get_file1(),
                              South->tiles[i - x_offset][off_y].get_file2());
          win << t.get_image();
          if(t.get_over()) win << t.get_image2();
          if(South->permissions[i - x_offset][off_y] == 2)
            second_layer.push_back(t);
        }
        else if(i - x_offset >= South->width && !South->East 
                || i - x_offset < 0 && !South->West)
        {
          Tile t(Point(i,j), "0");
          win << t.get_image();
        }
      }
      if(i >= width && East)
      {
        off_x = i - width;
        if(j - y_offset >= East->height && East->North)//x and y too high
        {
          off_y = i - East->height;
          Tile t(Point(i, j), East->North->tiles[off_x][off_y].get_file1(),
                              East->North->tiles[off_x][off_y].get_file2());
          win << t.get_image();
          if(t.get_over()) win << t.get_image2();
          if(East->North->permissions[off_x][off_y] == 2)
            second_layer.push_back(t);
        }
        else if(j - y_offset < 0 && East->South)//x too low and y too high
        {
          off_y = East->South->height + i;
          Tile t(Point(i, j), East->South->tiles[off_x][off_y].get_file1(),
                              East->South->tiles[off_x][off_y].get_file2());
          win << t.get_image();
          if(t.get_over()) win << t.get_image2();
          if(East->South->permissions[off_x][off_y] == 2)
            second_layer.push_back(t);
        }
        else if(j - y_offset >= 0 && j < East->height)//y too high and x in bounds
        {
          Tile t(Point(i, j), East->tiles[off_x][j - y_offset].get_file1(),
                              East->tiles[off_x][j - y_offset].get_file2());
          win << t.get_image();
          if(t.get_over()) win << t.get_image2();
          if(East->permissions[off_x][j - y_offset] == 2)
            second_layer.push_back(t);
        }
        else if(j - y_offset >= East->height && !East->North 
                || j - y_offset < 0 && !East->South)
        {
          Tile t(Point(i,j), "0");
          win << t.get_image();
        }
      }
      if(i < 0 && West)
      {
        off_x = West->width + i;
        if(j + West->y_offset >= West->height && West->North)//x and y too high
        {
          off_y = j - West->height;
          Tile t(Point(i, j), West->North->tiles[off_x][off_y].get_file1(),
                              West->North->tiles[off_x][off_y].get_file2());
          win << t.get_image();
          if(t.get_over()) win << t.get_image2();
          if(West->North->permissions[off_x][off_y] == 2)
            second_layer.push_back(t);
        }
        else if(j + West->y_offset < 0 && West->South)//x too low and y too high
        {
          off_y = West->South->height + i;
          Tile t(Point(i, j), West->South->tiles[off_x][off_y].get_file1(),
                              West->South->tiles[off_x][off_y].get_file2());
          win << t.get_image();
          if(t.get_over()) win << t.get_image2();
          if(West->South->permissions[off_x][off_y] == 2)
            second_layer.push_back(t);
        }
        else if(j + West->y_offset >= 0 && j + West->y_offset < West->height)//y too high and x in bounds
        {
          Tile t(Point(i, j), West->tiles[off_x][j + West->y_offset].get_file1(),
                              West->tiles[off_x][j + West->y_offset].get_file2());
          win << t.get_image();
          if(t.get_over()) win << t.get_image2();
          if(West->permissions[off_x][j + West->y_offset] == 2)
            second_layer.push_back(t);
        }
        else if(j + West->y_offset >= West->height && !West->North 
                || j + West->y_offset < 0 && !West->South)
        {
          Tile t(Point(i,j), "0");
          win << t.get_image();
        }
      }
      if(i >= 0 && j >= 0 && i < width && j < height)
      {
        win << tiles[i][j].get_image();
        if(tiles[i][j].get_over()) win << tiles[i][j].get_image2();
        if(permissions[i][j] == 2)
          second_layer.push_back(tiles[i][j]);
      }
      if(i < 0 && !West || j < 0 && !South || i >= width && !East || j >= height && !North)
      {
        Tile t(Point(i,j), "0");
        win << t.get_image();
      }
    }
  p.draw_player();
  for(int i = 0; i < (int)second_layer.size(); i++) 
    win << second_layer[i].get_image2();
  win.output_buffer();
}

bool Map::allowed(int x, int y) const
{
  if(permissions[x][y] != 0) return true;
  else return false;
}

Player::Player(const Map &m)
{
  px = m.get_width() / 2;
  py = m.get_height() / 2;
  win.coord(px - XVIEW, py - YVIEW, px + XVIEW + 1, py + YVIEW + 1);
  sprite = Image(Point(px, py), 1, 1.5, "./images_1/down.png");
}

void Player::draw_player() const
{
  win << sprite;
}

void Player::move(Map* &m)
{
  if(win.is_key_down("up"))
  {
    if(py == m->get_height()-1 && m->get_north()) 
    {
      m = m->get_north();
      px = px + m->get_x_offset(); 
      py = 0;
    }
    else if(py < m->get_height() && m->allowed(px, py + 1)) py++;
    win.coord(px - XVIEW, py - YVIEW, px + XVIEW + 1, py + YVIEW + 1);
    sprite = Image(Point(px, py), 1, 1.5, "./images_1/up.png");
    m->draw_map(*this);
    wait_for(150);
  }
  else if(win.is_key_down("down"))
  {
    if(py == 0 && m->get_south()) 
    {
      px = px - m->get_x_offset();
      m = m->get_south(); 
      py = m->get_height() - 1;
    } 
    else if(py > 0 && m->allowed(px, py - 1)) py--;
    win.coord(px - XVIEW, py - YVIEW, px + XVIEW + 1, py + YVIEW + 1);
    sprite = Image(Point(px, py), 1, 1.5, "./images_1/down.png");
    m->draw_map(*this);
    wait_for(150);
  }
  else if(win.is_key_down("right"))
  {
    if(px == m->get_width() && m->get_east()) 
    {
      m = m->get_east(); 
      px = 0;
      py = py + m->get_y_offset();
    }
    else if(px < m->get_width()-1 && m->allowed(px + 1, py)) px++;
    win.coord(px - XVIEW, py - YVIEW, px + XVIEW + 1, py + YVIEW + 1);
    sprite = Image(Point(px, py), 1, 1.5, "./images_1/right.png");
    m->draw_map(*this);
    wait_for(150);
  }
  else if(win.is_key_down("left"))
  {
    if(px == 0 && m->get_west()) 
    {
      py = py - m->get_y_offset();
      m = m->get_west(); 
      px = m->get_width() - 1;
    }
    else if(px > 0 && m->allowed(px - 1, py)) px--;
    win.coord(px - XVIEW, py - YVIEW, px + XVIEW + 1, py + YVIEW + 1);
    sprite = Image(Point(px, py), 1, 1.5, "./images_1/left.png");
    m->draw_map(*this);
    wait_for(150);
  }
}

Tile Map::create_tile(int number, int x, int y)
{
  if(number == 0) return Tile(Point(x, y), "0");
    
  int iback = number / 10000;
  number = number % 10000;
  int ifolder = number / 1000;
  number = number % 1000;
  int ifront = number;

  string temp = "";
  string returnvalue = "";
  while(iback > 0)
  {
    temp += iback % 10 + 48;
    iback /= 10;
  }
  for(int i = 0; i < (int)temp.length(); i++)
    returnvalue += temp[temp.length() - i - 1];    
  string back = returnvalue;
    
  temp = "";
  returnvalue = ""; 
  while(ifolder > 0)
  {
    temp += ifolder % 10 + 48;
    ifolder /= 10;
  }
  for(int i = 0; i < (int)temp.length(); i++)
    returnvalue += temp[temp.length() - i - 1];
  string folder = returnvalue;
        
  temp = "";
  returnvalue = "";
  while(ifront > 0)
  {
    temp += ifront % 10 + 48;
    ifront /= 10;
  }
  for(int i = 0; i < (int)temp.length(); i++)
    returnvalue += temp[temp.length() - i - 1];
  string front = returnvalue;
    
  if(back == "") back = "0";
  if(folder == "") folder = "0";
  if(front == "") front = "0";
           
  front = folder + "/" + front;    
  return Tile(Point(x, y), back, front);
}
