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
    if (tecla == 'l')
    {
        int k = 0;
        for (double alpha = 0.0; alpha < 2 * M_PI; alpha += 0.1, k ^= 1)
            dibujarLinea(250 ,250,250 * (1 + cos(alpha)) ,250 * (1 + sin(alpha)), AZUL, 1 + k);
    }
    ejecutarAlIniciarElPrograma();
}

void procesarClic(int X, int Y)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace un clic en (X,Y)
    cout << "Se hace clic en (" << X << "," << Y << ")" << endl;
    dibujarCirculo(X,Y,12, CIAN);
}
