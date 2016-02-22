.PHONY : all

all:
	g++ -std=c++11 -Wall -Wshadow -Wextra -D_GLIBCXX_DEBUG -O2 -o programa programa.cpp driver.cpp funcionesDeBiblioteca.cpp `sdl2-config --libs` -lSDL2_ttf

