
.PHONY : all, static

all:
	g++ -Wall -Wshadow -Wextra -D_GLIBCXX_DEBUG -O2 -o programa programa.cpp driver.cpp funcionesDeBiblioteca.cpp `sdl2-config --libs`
