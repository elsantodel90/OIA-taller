#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "funcionesDeBiblioteca.h"

using namespace std;

// Medidas
const int ANCHO = 10; // En manzanas. >= 2
const int ALTO = 8;   // En manzanas. >= 2
const int LADO_MANZANA = 30;
const int MEDIA_CALLE = 5;
const int ANCHO_BLOQUE = LADO_MANZANA + 2 * MEDIA_CALLE;
const int ALTO_BARRA_INFERIOR = 50;

extern const int RESOLUCION_HORIZONTAL = 2 * (LADO_MANZANA + MEDIA_CALLE) + (ANCHO - 2) * ANCHO_BLOQUE;
extern const int RESOLUCION_VERTICAL =  2 * (LADO_MANZANA + MEDIA_CALLE) + (ALTO - 2) * ANCHO_BLOQUE + ALTO_BARRA_INFERIOR;
extern const int TAMANIO_TEXTO = 12;
extern const string TITULO_PROGRAMA = "Optimizador de reunion";

const Color COLOR_BARRA_INFERIOR = GRIS;

bool encendido[ANCHO][ALTO];

void dibujarCuadricula()
{
    dibujarRectangulo(0,0,RESOLUCION_HORIZONTAL, RESOLUCION_VERTICAL, BLANCO);
    dibujarRectangulo(0,RESOLUCION_VERTICAL - ALTO_BARRA_INFERIOR,RESOLUCION_HORIZONTAL, RESOLUCION_VERTICAL, COLOR_BARRA_INFERIOR);
    escribirTexto(100, RESOLUCION_VERTICAL - ALTO_BARRA_INFERIOR / 2, "Haga clic en las esquinas para (des)seleccionarlas", AMARILLO);
    for (int i = 0; i < ANCHO; i++)
    for (int j = 0; j < ALTO; j++)
    {
        const int x = i * ANCHO_BLOQUE;
        const int y = j * ANCHO_BLOQUE;
        dibujarRectangulo(x,y,x+LADO_MANZANA, y+LADO_MANZANA, NEGRO);
    }
}


void actualizarDibujoEsquina(int i, int j)
{
    int x = LADO_MANZANA + ANCHO_BLOQUE * i;
    int y = LADO_MANZANA + ANCHO_BLOQUE * j;
    dibujarRectangulo(x,y,x+2*MEDIA_CALLE, y+2*MEDIA_CALLE, BLANCO);
    if (encendido[i][j])
        dibujarCirculo(x+MEDIA_CALLE, y+MEDIA_CALLE, MEDIA_CALLE, ROJO);
}

void marcarEsquina(int i,int j, Color color, int separacionExtra)
{
    int x = LADO_MANZANA + MEDIA_CALLE + ANCHO_BLOQUE * i;
    int y = LADO_MANZANA + MEDIA_CALLE + ANCHO_BLOQUE * j;
    const int GROSOR = 4;
    const int DELTA = MEDIA_CALLE + GROSOR / 2 + separacionExtra;
    dibujarLinea(x - DELTA, y - DELTA, x + DELTA, y - DELTA, color, 3);
    dibujarLinea(x + DELTA, y - DELTA, x + DELTA, y + DELTA, color, 3);
    dibujarLinea(x + DELTA, y + DELTA, x - DELTA, y + DELTA, color, 3);
    dibujarLinea(x - DELTA, y + DELTA, x - DELTA, y - DELTA, color, 3);
}

void ejecutarAlIniciarElPrograma()
{
    for(int i=0; i < ANCHO; i++)
    for(int j=0; j < ALTO; j++)
        encendido[i][j] = false;
    // Aca se escribe el codigo que se ejecuta al momento que comienza la ejecucion del programa
    dibujarCuadricula();
    crearBoton(5,RESOLUCION_VERTICAL - ALTO_BARRA_INFERIOR + 5, 65, RESOLUCION_VERTICAL - 18, "Calcular");
}

void procesarCargaDeTextoEnCuadro(int, string)
{
    // Aca se escribe el codigo que se ejecuta cuando se carga texto en un cuadro de texto interactivo
}

void procesarClicEnBoton(int)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace clic en un boton
    dibujarCuadricula();
    int mejorMaximaDistancia = 1000000000;
    int mejorMaxDistI = -1;
    int mejorMaxDistJ = -1;
    int mejorSuma = 1000000000;
    int mejorSumaI = -1;
    int mejorSumaJ = -1;
    for(int i=0; i < ANCHO-1; i++)
    for(int j=0; j < ALTO-1; j++)
    {
        actualizarDibujoEsquina(i,j);
        int mayorDistancia = 0;
        int suma = 0;
        for(int x=0; x < ANCHO-1; x++)
        for(int y=0; y < ALTO-1; y++)
        if (encendido[x][y])
        {
            int distancia = abs(x-i) + abs(y-j);
            if (distancia > mayorDistancia)
                mayorDistancia = distancia;
            suma += distancia;
        }
        if (mayorDistancia < mejorMaximaDistancia)
        {
            mejorMaxDistI = i;
            mejorMaxDistJ = j;
            mejorMaximaDistancia = mayorDistancia;
        }
        if (suma < mejorSuma)
        {
            mejorSumaI = i;
            mejorSumaJ = j;
            mejorSuma = suma;
        }
    }
    marcarEsquina(mejorMaxDistI, mejorMaxDistJ, VERDE,0);
    marcarEsquina(mejorSumaI, mejorSumaJ, AZUL, 3);
    dibujarRectangulo(100, RESOLUCION_VERTICAL - ALTO_BARRA_INFERIOR, RESOLUCION_HORIZONTAL , RESOLUCION_VERTICAL, COLOR_BARRA_INFERIOR);
    ostringstream mensaje;
    mensaje << "Mejor suma de distancias(azul): " << mejorSuma;
    escribirTexto(100, RESOLUCION_VERTICAL - 3 * ALTO_BARRA_INFERIOR / 4, mensaje.str(), AMARILLO);
    mensaje.str(""); 
    mensaje << "Mejor maxima distancia(verde): " << mejorMaximaDistancia;
    escribirTexto(100, RESOLUCION_VERTICAL - ALTO_BARRA_INFERIOR / 2, mensaje.str(), AMARILLO);
}

void procesarPulsacionDeTecla(char)
{
    // Aca se escribe el codigo que se ejecuta cuando se pulsa una tecla.
}

void procesarClic(int X, int Y)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace un clic en (X,Y)
    for (int i = 0; i < ANCHO-1; i++)
    for (int j = 0; j < ALTO-1; j++)
    {
        const int x = LADO_MANZANA + MEDIA_CALLE + i * ANCHO_BLOQUE;
        const int y = LADO_MANZANA + MEDIA_CALLE + j * ANCHO_BLOQUE;
        if (abs(X-x) < MEDIA_CALLE && abs(Y-y) < MEDIA_CALLE)
        {
            encendido[i][j] = !encendido[i][j];
            actualizarDibujoEsquina(i, j);
        }
    }
}
