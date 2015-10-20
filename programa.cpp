#include <iostream>
#include <string>
#include "opciones.h"
#include "funcionesDeBiblioteca.h"

using namespace std;

int xRectangulo = 0, yRectangulo = 0;

Color c = ROJO;

void ejecutarAlIniciarElPrograma()
{
    // Aca se escribe el codigo que se ejecuta siempre al momento que comienza el programa
    dibujarRectangulo(10 + xRectangulo,100 + yRectangulo,300+xRectangulo,365 + yRectangulo, c);
    c.verde = (c.verde + 5) % 256;
    c.azul = (c.azul + 7) % 256;
}

void procesarCargaDeTextoEnCuadro(int numeroDeCuadroDeTexto, string texto)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace clic en un boton
    cout << "Se carga el texto \"" << texto << "\" en el cuadro de texto numero " << numeroDeCuadroDeTexto << endl;
}

void procesarClicEnBoton(int numeroDeBoton)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace clic en un boton
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
    ejecutarAlIniciarElPrograma();
}

void procesarClic(int X, int Y)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace un clic en (X,Y)
    cout << "Se hace clic en (" << X << "," << Y << ")" << endl;
    dibujarCirculo(X,Y,12, CIAN);
}
