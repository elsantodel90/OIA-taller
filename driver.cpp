#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "opciones.h"
#include "funcionesDeBiblioteca.h"

using namespace std;

void ejecutarAlIniciarElPrograma();
void procesarCargaDeTextoEnCuadro(int numeroDeCuadroDeTexto, string texto);
void procesarClicEnBoton(int numeroDeBoton);
void procesarPulsacionDeTecla(char tecla);
void procesarClic(int X, int Y);

SDL_Surface* screen = NULL;
SDL_Surface* canvas = NULL;
SDL_Window* gWindow = NULL;
TTF_Font *font = NULL;

void ejecutarElLoopPrincipal()
{
    SDL_Event evento;
    while (true)
    {
        actualizarPantalla();
        SDL_WaitEvent(&evento);
        switch(evento.type)
        {
            case SDL_QUIT:
                return;
                break;
            case SDL_TEXTINPUT: // Se puede usar SDL_KEYDOWN para dar acceso a las flechitas y no distinguir mayusculas, etc, pero esto es probablemente mas simple.
                assert(strlen(evento.text.text) == 1);
                procesarPulsacionDeTecla(evento.text.text[0]);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (evento.button.clicks == 1)
                    procesarClic(evento.button.x, evento.button.y);
                break;
        }
    }
}

int main()
{
    //Iniciar SDL
    SDL_Init( SDL_INIT_EVERYTHING ); 
    TTF_Init();
    
    
    //Preparar la ventana
    gWindow = SDL_CreateWindow( TITULO_PROGRAMA.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                                         RESOLUCION_HORIZONTAL, RESOLUCION_VERTICAL, SDL_WINDOW_SHOWN );
    screen = SDL_GetWindowSurface( gWindow );
    canvas = SDL_CreateRGBSurface(0, RESOLUCION_HORIZONTAL, RESOLUCION_VERTICAL, 32, 0,0,0,0);
    
    // Cargar la fuente
    
    font = TTF_OpenFont("open-sans.ttf", 24);
    cout << TTF_GetError() << endl;
    // Comienza nuestro driver!
    cout << "El driver ha comenzado." << endl;
    ejecutarAlIniciarElPrograma();
    ejecutarElLoopPrincipal();
    
    //Terminar SDL
    SDL_FreeSurface( canvas );
    SDL_DestroyWindow( gWindow );
    TTF_Quit();
    SDL_Quit(); 
    return 0;
}
