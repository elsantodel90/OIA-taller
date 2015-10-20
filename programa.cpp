#include <iostream>
#include <string>
#include "funcionesDeBiblioteca.h"

using namespace std;

void ejecutarAlIniciarElPrograma()
{
    // Aca se escribe el codigo que se ejecuta siempre al momento que comienza el programa
    dibujarRectangulo(10,100,300,365, ROJO);
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
}

void procesarClic(int X, int Y)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace un clic en (X,Y)
    cout << "Se hace clic en (" << X << "," << Y << ")" << endl;
}
