
.PHONY : all

all:
	g++ -Wall -Wshadow -Wextra -D_GLIBCXX_DEBUG -O2 -o programa programa.cpp driver.cpp funcionesDeBiblioteca.cpp -lSDL2
