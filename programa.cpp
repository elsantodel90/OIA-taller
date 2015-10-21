#include <string>
#include "funcionesDeBiblioteca.h"

using namespace std;

// Las siguientes funciones y constantes son las que el "framework" espera que existan.
// Se deben completar para crear el programa.

extern const int RESOLUCION_HORIZONTAL = 500;
extern const int RESOLUCION_VERTICAL = 500;
extern const int TAMANIO_TEXTO = 12;
extern const string TITULO_PROGRAMA = "Programa OIA";

void ejecutarAlIniciarElPrograma()
{
    // Aca se escribe el codigo que se ejecuta al momento que comienza la ejecucion del programa
    const int H = 25;
    for(int y=0; y < 20; y++)
        dibujarLinea(10+H*y,10+H*y,100+(H*y)/2,10+H*y,ROJO, 2);
}

void procesarCargaDeTextoEnCuadro(int numeroDeCuadroDeTexto, string texto)
{
    // Aca se escribe el codigo que se ejecuta cuando se carga texto en un cuadro de texto interactivo
}

void procesarClicEnBoton(int numeroDeBoton)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace clic en un boton
}

void procesarPulsacionDeTecla(char tecla)
{
    // Aca se escribe el codigo que se ejecuta cuando se pulsa una tecla.
}

void procesarClic(int X, int Y)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace un clic en (X,Y)
}
