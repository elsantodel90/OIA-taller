#ifndef FUNCIONES_DE_BIBLIOTECA_H
#define FUNCIONES_DE_BIBLIOTECA_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

struct Color
{
    int rojo, verde, azul;
};

const Color ROJO      = {255, 0  , 0  };
const Color VERDE     = {0  , 255, 0  };
const Color AZUL      = {0  , 0  , 255};
const Color CIAN      = {0  , 255, 255};
const Color AMARILLO  = {255, 255, 0  };
const Color MAGENTA   = {255, 0  , 255};
const Color BLANCO    = {255, 255, 255};
const Color NEGRO     = {0  , 0  , 0  };

void dibujarRectangulo(int x1, int y1, int x2, int y2, Color color);
void dibujarLinea(int x1, int y1, int x2, int y2, Color color, int grosor = 1);
void dibujarCirculo(int centroX, int centroY, int radio, Color color);
void escribirTexto(int x,int y, string texto, Color color);

void actualizarPantalla();

#endif // FUNCIONES_DE_BIBLIOTECA_H
