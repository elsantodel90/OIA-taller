#include <vector>
#include <cassert>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "funcionesDeBiblioteca.h"

Uint32 colorEnFormatoPixel(Color color, SDL_Surface *superficie)
{
    return SDL_MapRGB(superficie->format, color.rojo, color.verde, color.azul);
}

void dibujarRectanguloEnSuperficie(int x1, int y1, int x2, int y2, Color color, SDL_Surface *superficie)
{
    SDL_Rect r;
    r.x = x1;
    r.y = y1;
    r.w = x2-x1;
    r.h = y2-y1;
    SDL_FillRect(superficie, &r, colorEnFormatoPixel(color, superficie));
}

void dibujarCirculoEnSuperficie(int centroX, int centroY, int radio, Color color, SDL_Surface *superficie)
{
    Uint32 colorSDL = colorEnFormatoPixel(color, superficie);
    SDL_LockSurface(superficie);
    assert(superficie->format->BytesPerPixel == 4);
    assert(superficie->pitch % 4 == 0);
    assert(sizeof(Uint32) == 4);
    const int STEP = superficie->pitch / 4;
    Uint32 *pixels = static_cast<Uint32*>(superficie->pixels);
    pixels += STEP * (centroY - radio);
    pixels += centroX;
    for (int y = -radio; y <= radio; y++)
    {
        if (0 <= centroY + y && centroY + y < superficie->h)
        {
            for (int x = -radio; x <= radio; x++)
            if (0 <= centroX + x && centroX + x < superficie->w &&
                          x*x+y*y < radio*radio)
                pixels[x] = colorSDL;
        }
        pixels += STEP;
    }
    SDL_UnlockSurface(superficie);
}

extern const int RESOLUCION_HORIZONTAL;
extern const int RESOLUCION_VERTICAL;

const int MAX_RES = max(RESOLUCION_HORIZONTAL, RESOLUCION_VERTICAL);

void dibujarLineaEnSuperficie(int x1, int y1, int x2, int y2, Color color, int grosor, SDL_Surface *superficie)
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    for (int k = 0; k<=MAX_RES ; k++ )
    {
        int x = (deltaX * k) / MAX_RES;
        int y = (deltaY * k) / MAX_RES;
        dibujarCirculoEnSuperficie(x1 + x,y1 + y,grosor, color, superficie);
    }
}


extern TTF_Font *font;

SDL_Color colorEnFormatoSDL(Color color)
{
    SDL_Color sdlColor;
    sdlColor.r = color.rojo;
    sdlColor.g = color.verde;
    sdlColor.b = color.azul;
    return sdlColor;
}

void escribirTextoEnSuperficie(int x,int y, string texto, Color color, SDL_Surface *superficie)
{
    if (!texto.empty())
    {
        SDL_Surface *text = TTF_RenderUTF8_Blended (font, texto.c_str(), colorEnFormatoSDL(color));
        SDL_Rect dstRect;
        dstRect.x = x;
        dstRect.y = y;
        dstRect.w = text->w;
        dstRect.h = text->h;
        SDL_BlitSurface(text, NULL, superficie, &dstRect);
        SDL_FreeSurface(text);
    }
}

extern SDL_Surface* canvas;

void dibujarRectangulo(int x1, int y1, int x2, int y2, Color color)
{
    dibujarRectanguloEnSuperficie(x1,y1,x2,y2,color,canvas);
}

void dibujarLinea(int x1, int y1, int x2, int y2, Color color, int grosor)
{
    dibujarLineaEnSuperficie(x1,y1,x2,y2, color, grosor, canvas);
}

void dibujarCirculo(int centroX, int centroY, int radio, Color color)
{
    dibujarCirculoEnSuperficie(centroX,centroY, radio, color, canvas);
}


void escribirTexto(int x,int y, string texto, Color color)
{
    escribirTextoEnSuperficie(x,y,texto, color, canvas);
}
