#include <cassert>
#include <SDL2/SDL.h>
#include "opciones.h"
#include "funcionesDeBiblioteca.h"

extern SDL_Surface* canvas;

Uint32 colorEnFormatoPixel(Color color)
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
    SDL_FillRect(canvas, &r, colorEnFormatoPixel(color));
}

const int MAX_RES = max(RESOLUCION_HORIZONTAL, RESOLUCION_VERTICAL);

void dibujarLinea(int x1, int y1, int x2, int y2, Color color, int grosor)
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    for (int k = 0; k<=MAX_RES ; k++ )
    {
        int x = (deltaX * k) / MAX_RES;
        int y = (deltaY * k) / MAX_RES;
        dibujarCirculo(x1 + x,y1 + y,grosor, color);
    }
}

void dibujarCirculo(int centroX, int centroY, int radio, Color color)
{
    Uint32 colorSDL = colorEnFormatoPixel(color);
    SDL_LockSurface(canvas);
    assert(canvas->pitch % 4 == 0);
    assert(sizeof(Uint32) == 4);
    const int STEP = canvas->pitch / 4;
    Uint32 *pixels = static_cast<Uint32*>(canvas->pixels);
    pixels += STEP * (centroY - radio);
    pixels += centroX;
    for (int y = -radio; y <= radio; y++)
    {
        if (0 <= centroY + y && centroY + y < canvas->h)
        {
            for (int x = -radio; x <= radio; x++)
            if (0 <= centroX + x && centroX + x < canvas->w &&
                          x*x+y*y < radio*radio)
                pixels[x] = colorSDL;
        }
        pixels += STEP;
    }
    SDL_UnlockSurface(canvas);
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

#include <iostream>

void escribirTexto(int x,int y, string texto, Color color)
{
    cout << font << endl;
    SDL_Surface *text = TTF_RenderUTF8_Blended (font, texto.c_str(), colorEnFormatoSDL(color));
    cout << TTF_GetError() << endl;
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = text->w;
    dstRect.h = text->h;
    SDL_BlitSurface(text, NULL, canvas, &dstRect);
    SDL_FreeSurface(text);
}


extern SDL_Surface* screen;
extern SDL_Window* gWindow;

void actualizarPantalla()
{
    SDL_BlitSurface(canvas, NULL, screen, NULL);
    SDL_UpdateWindowSurface( gWindow );
}
