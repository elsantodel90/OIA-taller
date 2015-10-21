#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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

int mouseX = 0, mouseY = 0;
int mouseDownX = 0, mouseDownY = 0;

void dibujarRectanguloEnSuperficie(int x1, int y1, int x2, int y2, Color color, SDL_Surface *superficie);
void escribirTextoEnSuperficie(int x,int y, string texto, Color color, SDL_Surface *superficie);

const int REBORDE_BOTON = 2;

struct Control
{
    int x1,y1,x2,y2;
    int numero;
    string texto;
    bool mouseEncima()
    {
        return x1 <= mouseX && mouseX < x2 && 
               y1 <= mouseY && mouseY < y2;
    }
    bool mousePulso()
    {
        return x1 <= mouseDownX && mouseDownX < x2 && 
               y1 <= mouseDownY && mouseDownY < y2;
    }
    bool presionado()
    {
        return mouseEncima() && mousePulso();
    }
};

struct Boton : public Control
{
    void dibujar()
    {
        if (presionado())
        {
            dibujarRectanguloEnSuperficie(x1,y1,x2,y2, GRIS_MUY_OSCURO, screen);
            dibujarRectanguloEnSuperficie(x1+REBORDE_BOTON,y1,x2,y2-REBORDE_BOTON, GRIS_OSCURO, screen);
            escribirTextoEnSuperficie(x1 + 2*REBORDE_BOTON, y1 + REBORDE_BOTON, texto, NEGRO, screen);
        }
        else
        {
            dibujarRectanguloEnSuperficie(x1,y1-REBORDE_BOTON,x2 + REBORDE_BOTON,y2, BLANCO, screen);
            dibujarRectanguloEnSuperficie(x1,y1,x2,y2, GRIS_CLARO, screen);
            escribirTextoEnSuperficie(x1 + REBORDE_BOTON, y1 + REBORDE_BOTON, texto, NEGRO, screen);
        }
        
    }
};

const int REBORDE_CUADRO = 2;
int cuadroEnElQueSeCargaTexto = -1;

struct CuadroDeTexto : public Control
{
    void dibujar()
    {
        if (cuadroEnElQueSeCargaTexto == numero)
        {
            dibujarRectanguloEnSuperficie(x1-REBORDE_CUADRO,y1-REBORDE_CUADRO,x2+REBORDE_CUADRO,y2+REBORDE_CUADRO, VERDE, screen);
            dibujarRectanguloEnSuperficie(x1,y1,x2,y2, GRIS_MUY_OSCURO, screen);
            escribirTextoEnSuperficie(x1 + REBORDE_CUADRO, y1 + REBORDE_CUADRO, texto, ROJO, screen);
        }
        else if (mouseEncima())
        {
            dibujarRectanguloEnSuperficie(x1-REBORDE_CUADRO,y1-REBORDE_CUADRO,x2+REBORDE_CUADRO,y2+REBORDE_CUADRO, BLANCO, screen);
            dibujarRectanguloEnSuperficie(x1,y1,x2,y2, NEGRO, screen);
            escribirTextoEnSuperficie(x1 + REBORDE_CUADRO, y1 + REBORDE_CUADRO, texto, AMARILLO, screen);
        }
        else
        {
            dibujarRectanguloEnSuperficie(x1-REBORDE_CUADRO,y1-REBORDE_CUADRO,x2+REBORDE_CUADRO,y2+REBORDE_CUADRO, ROJO, screen);
            dibujarRectanguloEnSuperficie(x1,y1,x2,y2, BLANCO, screen);
            escribirTextoEnSuperficie(x1 + REBORDE_CUADRO, y1 + REBORDE_CUADRO, texto, NEGRO, screen);
        }
    }
};

vector<Boton> botones;
vector<CuadroDeTexto> cuadrosDeTexto;

int proximoNumeroDeControl = 0;

extern const int RESOLUCION_HORIZONTAL;
extern const int RESOLUCION_VERTICAL;

template <typename T>
void eliminarControlPorNumero(vector<T> &v, int numeroDeControl, string mensajeDeError)
{
    for (int i = 0; i < (int)v.size(); i++)
    if (v[i].numero == numeroDeControl)
    {
        v.erase(v.begin() + i);
        return;
    }
    dibujarRectanguloEnSuperficie(0,0,RESOLUCION_HORIZONTAL, RESOLUCION_VERTICAL, AZUL, screen);
    escribirTextoEnSuperficie(100,100, mensajeDeError, BLANCO, screen);
    SDL_UpdateWindowSurface( gWindow );
    SDL_Delay(3000);
}

template <typename T>
int crearControl(int x1,int y1, int x2, int y2, string texto, vector<T> &v)
{
    T b;
    b.numero = proximoNumeroDeControl++;
    b.x1 = x1;
    b.y1 = y1;
    b.x2 = x2;
    b.y2 = y2;
    b.texto = texto;
    v.push_back(b);
    return b.numero;
}


int crearBoton(int x1,int y1, int x2, int y2, string texto)
{
    return crearControl(x1, y1, x2, y2, texto, botones);
}


void eliminarBoton(int numeroDeBoton)
{
    eliminarControlPorNumero(botones, numeroDeBoton, "El boton solicitado no existe! No puede ser eliminado.");
}

int crearCuadroDeTexto(int x1,int y1, int x2, int y2, string textoInicial)
{
    return crearControl(x1, y1, x2, y2, textoInicial, cuadrosDeTexto);
}

void eliminarCuadroDeTexto(int numeroDeCuadroDeTexto)
{
    eliminarControlPorNumero(cuadrosDeTexto, numeroDeCuadroDeTexto, "El cuadro de texto solicitado no existe! No puede ser eliminado.");
}

template <typename T>
void dibujarTodos(vector<T> &v)
{
    for (int i = 0; i < (int)v.size(); i++)
        v[i].dibujar();
}

void actualizarPantalla()
{
    SDL_BlitSurface(canvas, NULL, screen, NULL);
    dibujarTodos(botones);
    dibujarTodos(cuadrosDeTexto);
    SDL_UpdateWindowSurface( gWindow );
}

void finDeCargaDeTexto()
{
    if (cuadroEnElQueSeCargaTexto >= 0)
    {
        for (int i = 0; i < (int)cuadrosDeTexto.size(); i++)
        if (cuadrosDeTexto[i].numero == cuadroEnElQueSeCargaTexto)
        {
            procesarCargaDeTextoEnCuadro(cuadrosDeTexto[i].numero, cuadrosDeTexto[i].texto);
            break;
        }
        cuadroEnElQueSeCargaTexto = -1;
    }
}

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
            case SDL_KEYDOWN:
                if (evento.key.keysym.sym == SDLK_KP_ENTER ||
                    evento.key.keysym.sym == SDLK_RETURN)
                    finDeCargaDeTexto();
                if (evento.key.keysym.sym == SDLK_KP_BACKSPACE ||
                    evento.key.keysym.sym == SDLK_BACKSPACE) 
                {
                    for (int i = 0; i < (int)cuadrosDeTexto.size(); i++)
                    if (cuadrosDeTexto[i].numero == cuadroEnElQueSeCargaTexto)
                    {
                        if (!cuadrosDeTexto[i].texto.empty())
                            cuadrosDeTexto[i].texto.erase(cuadrosDeTexto[i].texto.size() - 1);
                        break;
                    }
                }
                break;
            case SDL_TEXTINPUT: // Se puede usar SDL_KEYDOWN para dar acceso a las flechitas y no distinguir mayusculas, etc, pero esto es probablemente mas simple para el cliente.
                assert(strlen(evento.text.text) == 1);
                if (cuadroEnElQueSeCargaTexto >= 0)
                {
                    for (int i = 0; i < (int)cuadrosDeTexto.size(); i++)
                    if (cuadrosDeTexto[i].numero == cuadroEnElQueSeCargaTexto)
                    {
                        cuadrosDeTexto[i].texto += evento.text.text;
                        break;
                    }
                }
                else
                    procesarPulsacionDeTecla(evento.text.text[0]);
                break;
            case SDL_MOUSEMOTION:
                mouseX = evento.motion.x;
                mouseY = evento.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                finDeCargaDeTexto();
                mouseX = mouseDownX = evento.button.x;
                mouseY = mouseDownY = evento.button.y;
                break;
            case SDL_MOUSEBUTTONUP:
                mouseX = evento.button.x;
                mouseY = evento.button.y;
                bool botonCliqueado = false;
                for (int i = 0; i < (int)botones.size(); i++)
                if (botones[i].presionado())
                {
                    procesarClicEnBoton(botones[i].numero);
                    botonCliqueado = true;
                    break;
                }
                if (!botonCliqueado && evento.button.clicks == 1)
                {
                    bool cuadroCliqueado = false;
                    for (int i = 0; i < (int)cuadrosDeTexto.size(); i++)
                    if (cuadrosDeTexto[i].presionado())
                    {
                        cuadroEnElQueSeCargaTexto = cuadrosDeTexto[i].numero;
                        cuadrosDeTexto[i].texto = "";
                        cuadroCliqueado = true;
                        break;
                    }
                    if (!cuadroCliqueado)
                        procesarClic(mouseX, mouseY);
                }
                mouseDownX = mouseDownY = -1000000;
                break;
        }
    }
}

extern const int TAMANIO_TEXTO;
extern const string TITULO_PROGRAMA;


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
    
    font = TTF_OpenFont("open-sans.ttf", TAMANIO_TEXTO);
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
