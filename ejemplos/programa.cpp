#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <cmath>
#include "funcionesDeBiblioteca.h"

using namespace std;

int xRectangulo = 0, yRectangulo = 0;
Color c = ROJO;

void dibujar()
{    
    dibujarRectangulo(10 + xRectangulo,100 + yRectangulo,300+xRectangulo,365 + yRectangulo, c);
    c.verde = (c.verde + 5) % 256;
    c.azul = (c.azul + 7) % 256;
}

// Las siguientes funciones son las que espera el "framework"

extern const int RESOLUCION_HORIZONTAL = 500;
extern const int RESOLUCION_VERTICAL = 500;
extern const int TAMANIO_TEXTO = 12;
extern const string TITULO_PROGRAMA = "Programa OIA";

int numeroDelBotonUno = -1, numeroDelBotonDos = -1;
int numeroDelCuadroUno = -1, numeroDelCuadroDos = -1;

void ejecutarAlIniciarElPrograma()
{
    // Aca se escribe el codigo que se ejecuta siempre al momento que comienza el programa
    numeroDelBotonUno = crearBoton(50,30,120,70, "Boton1");
    numeroDelBotonDos = crearBoton(130,30,200,70, "Boton2");
    numeroDelCuadroUno = crearCuadroDeTexto(350,30,420,70, "10");
    numeroDelCuadroDos = crearCuadroDeTexto(430,30,495,70, "5");
    dibujar();
    escribirTexto(10,2, "Finalmente podemos escribir", AMARILLO);
}

string toString(int x)
{
    ostringstream s; s << x;
    return s.str();
}

int fromString(string x)
{
    int ret; istringstream s(x); s >> ret;
    return ret;
}

int numero1 = 10, numero2 = 5;

void procesarCargaDeTextoEnCuadro(int numeroDeCuadroDeTexto, string texto)
{
    // Aca se escribe el codigo que se ejecuta cuando se carga texto en un cuadro de texto interactivo
    cout << "Se carga el texto \"" << texto << "\" en el cuadro de texto numero " << numeroDeCuadroDeTexto << endl;
    if (numeroDeCuadroDeTexto == numeroDelCuadroUno)
        numero1 = fromString(texto);
    else if (numeroDeCuadroDeTexto == numeroDelCuadroDos)
        numero2 = fromString(texto);
    else
        assert(false);
    dibujarRectangulo(0,400,500,500, NEGRO);
    escribirTexto(200, 415, string("La suma de los numeros cargados es ") + toString(numero1 + numero2), AMARILLO);
}

void procesarClicEnBoton(int numeroDeBoton)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace clic en un boton
    dibujarRectangulo(0,400,500,500, NEGRO);
    if (numeroDeBoton == numeroDelBotonUno)
        escribirTexto(200, 415, "Se apreto el boton 1 UNO 1!", AMARILLO);
    else if (numeroDeBoton == numeroDelBotonDos)
        escribirTexto(200, 415, "Se apreto el boton 2 DOS 2!", AMARILLO);
    else
        assert(false);
    cout << "Se hace clic en el boton numero " << numeroDeBoton << endl;
}

void procesarPulsacionDeTecla(char tecla)
{
    // Aca se escribe el codigo que se ejecuta cuando se pulsa una tecla.
    cout << "Se pulsa la tecla " << tecla  << endl;
    const int SPEED = 3;
    if (tecla == 'a') xRectangulo -= SPEED;
    if (tecla == 'd') xRectangulo += SPEED;
    if (tecla == 'w') yRectangulo -= SPEED;
    if (tecla == 's') yRectangulo += SPEED;
    if (tecla == 'c') dibujarRectangulo(0 ,0,RESOLUCION_HORIZONTAL,RESOLUCION_VERTICAL, NEGRO);
    if (tecla == 'z') eliminarBoton(numeroDelBotonDos);
    if (tecla == 'x') eliminarCuadroDeTexto(numeroDelCuadroDos);
    if (tecla == 'l')
    {
        int k = 0;
        for (double alpha = 0.0; alpha < 2 * M_PI; alpha += 0.1, k ^= 1)
            dibujarLinea(250 ,250,250 * (1 + cos(alpha)) ,250 * (1 + sin(alpha)), AZUL, 1 + k);
    }
    dibujar();
}

void procesarClic(int X, int Y)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace un clic en (X,Y)
    cout << "Se hace clic en (" << X << "," << Y << ")" << endl;
    dibujarCirculo(X,Y,12, CIAN);
}
