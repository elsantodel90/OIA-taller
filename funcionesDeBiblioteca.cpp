#include <SDL2/SDL.h>
#include "funcionesDeBiblioteca.h"

extern SDL_Surface* canvas;

Uint32 colorEnFormatoSDL(Color color)
{
    return SDL_MapRGB(canvas->format, color.rojo, color.verde, color.azul);
    
}

void dibujarRectangulo(int x1, int y1, int x2, int y2, Color color)
{
    SDL_Rect r;
    r.x = x1;
    r.y = y1;
    r.w = x2-x1;
    r.h = y2-y1;
    SDL_FillRect(canvas, &r, colorEnFormatoSDL(color));
}

extern SDL_Surface* screen;
extern SDL_Window* gWindow;

void actualizarPantalla()
{
    SDL_BlitSurface(canvas, NULL, screen, NULL);
    SDL_UpdateWindowSurface( gWindow );
}
