#Compiler
CXX=g++

#Compiler Flags
CXXFLAGS=-g -W -Wall -Werror -ansi -pedantic

#Include
INCLUDE=-I/usr/local/include -I/usr/csshare/include -I/usr/Desktop/tdgame/instinct/include -I/usr/csshare/freetype2

#Library locations
LIBDIRS=-L/usr/lib -L/usr/local/lib -L/usr/csshare/lib -L/usr/csshare/pkgs/instinct_graphics/lib

#Libraries
LIBS=-lSDL -lSDL_image -lGL -lfreetype -lz -linstinct -lSDL_mixer

#Main program
EXERCISES=main.cpp mymap.cpp world_map.cpp tile.cpp
#world_map.cpp

#Object files
OBJECTS=main.cpp 

all: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LIBDIRS) $(LIBS) $(EXERCISES) -o a.out  

clean:
	rm -rf *.o a.out *~ *#
