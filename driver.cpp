#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <SDL2/SDL.h>
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
            case SDL_TEXTINPUT: // Se puede usar SDL_KEYDOWN para dar acceso a las flechitas, pero esto es probablemente mas simple.
                assert(strlen(evento.text.text) == 1);
                procesarPulsacionDeTecla(evento.text.text[0]);
                break;
        }
    }
}

int main()
{
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING ); 
    
    //Set up screen
    gWindow = SDL_CreateWindow( TITULO_PROGRAMA.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                                         RESOLUCION_HORIZONTAL, RESOLUCION_VERTICAL, SDL_WINDOW_SHOWN );
    screen = SDL_GetWindowSurface( gWindow );
    canvas = SDL_CreateRGBSurface(0, RESOLUCION_HORIZONTAL, RESOLUCION_VERTICAL, 32, 0,0,0,0);
    
    // Driver start
    cout << "El driver ha comenzado." << endl;
    ejecutarAlIniciarElPrograma();
    procesarClic(10,15);
    
    ejecutarElLoopPrincipal();
    
    //Quit SDL
    SDL_FreeSurface( canvas );
    SDL_DestroyWindow( gWindow );
    SDL_Quit(); 
    return 0;
}
