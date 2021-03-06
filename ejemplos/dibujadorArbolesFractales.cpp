#include <string>
#include <cmath>
#include "funcionesDeBiblioteca.h"

using namespace std;

// Las siguientes funciones y constantes son las que el "framework" espera que existan.
// Se deben completar para crear el programa.

extern const int RESOLUCION_HORIZONTAL = 990;
extern const int RESOLUCION_VERTICAL = 800;
extern const int TAMANIO_TEXTO = 22;
extern const string TITULO_PROGRAMA = "Arbol Fractal";
extern const int MILISEGUNDOS_RELOJ = 1000;

const double LONGITUD_INICIAL = 110;
const Color COLOR_ARBOL = AZUL;

int inputAngulo, inputReduccion, inputRamificacion, inputTotalPasos;

double gradosARadianes(double alpha)
{
    return alpha / 180.0 * M_PI;
}

const string anguloInicial = "35", reduccionInicial = "0.87", ramificacionInicial = "2", totalPasosInicial = "10";
double angulo = gradosARadianes(stod(anguloInicial)), reduccion = stod(reduccionInicial);
int ramificacion = stoi(ramificacionInicial), totalPasos = stoi(totalPasosInicial);

void limpiarPantalla()
{
    dibujarRectangulo(0,0,RESOLUCION_HORIZONTAL,RESOLUCION_VERTICAL, GRIS_MUY_OSCURO);
}

const int ANCHO_BOTON = 80;
const int ALTO_BOTON = 35;
const int GAP = 5;
const int ANCHO_CUADRO = 50;
const int CUADRO1_X = 175;
const int CUADRO2_X = 435;
const int CUADRO3_X = 720;
const int CUADRO4_X = 930;

void escribirEtiquetas()
{
    escribirTexto(ANCHO_BOTON + 3*GAP,RESOLUCION_VERTICAL-ALTO_BOTON, "Ángulo", BLANCO);
    escribirTexto(CUADRO1_X + ANCHO_CUADRO + GAP, RESOLUCION_VERTICAL-ALTO_BOTON , "Factor de reducción", BLANCO);
    escribirTexto(CUADRO2_X + ANCHO_CUADRO + GAP, RESOLUCION_VERTICAL-ALTO_BOTON , "Factor de ramificación", BLANCO);
    escribirTexto(CUADRO3_X + ANCHO_CUADRO + GAP, RESOLUCION_VERTICAL-ALTO_BOTON , "Total de pasos", BLANCO);
}

void ejecutarAlIniciarElPrograma()
{
    limpiarPantalla();
    crearBoton(0,RESOLUCION_VERTICAL - ALTO_BOTON, ANCHO_BOTON, RESOLUCION_VERTICAL-GAP, "Dibujar");
    inputAngulo = crearCuadroDeTexto(CUADRO1_X, RESOLUCION_VERTICAL-ALTO_BOTON,CUADRO1_X+ANCHO_CUADRO,RESOLUCION_VERTICAL-GAP, anguloInicial);
    inputReduccion = crearCuadroDeTexto(CUADRO2_X, RESOLUCION_VERTICAL-ALTO_BOTON,CUADRO2_X+ANCHO_CUADRO,RESOLUCION_VERTICAL-GAP, reduccionInicial);
    inputRamificacion = crearCuadroDeTexto(CUADRO3_X, RESOLUCION_VERTICAL-ALTO_BOTON,CUADRO3_X+ANCHO_CUADRO,RESOLUCION_VERTICAL-GAP, ramificacionInicial);
    inputTotalPasos = crearCuadroDeTexto(CUADRO4_X, RESOLUCION_VERTICAL-ALTO_BOTON,CUADRO4_X+ANCHO_CUADRO,RESOLUCION_VERTICAL-GAP, totalPasosInicial);
    escribirEtiquetas();
}

void procesarCargaDeTextoEnCuadro(int numeroDeCuadroDeTexto, string texto)
{
    if (numeroDeCuadroDeTexto == inputAngulo)
        angulo = gradosARadianes(stod(texto));
    else if (numeroDeCuadroDeTexto == inputReduccion)
        reduccion = stod(texto);
    else if (numeroDeCuadroDeTexto == inputRamificacion)
        ramificacion = stoi(texto);
    else if (numeroDeCuadroDeTexto == inputTotalPasos)
        totalPasos = stoi(texto);
}

void dibujarArbol(double x, double y,double longitud, double orientacion, int pasosRestantes)
{
    if (pasosRestantes > 0)
    {
        double nx = x + cos(orientacion) * longitud;
        double ny = y + sin(orientacion) * longitud;
        dibujarLinea(x,y,nx,ny, COLOR_ARBOL);
        double angleStep = angulo / (ramificacion-1); 
        double anguloBase = orientacion - angulo/2.0;
        for (int i=0;i<ramificacion;i++)
            dibujarArbol(nx, ny, longitud * reduccion, anguloBase + i * angleStep, pasosRestantes-1);
    }
}

void procesarClicEnBoton(int )
{
    limpiarPantalla();
    dibujarArbol(RESOLUCION_HORIZONTAL/2, RESOLUCION_VERTICAL-ALTO_BOTON-2*GAP,LONGITUD_INICIAL, -M_PI/2.0, totalPasos);
    escribirEtiquetas();
}

void procesarPulsacionDeTecla(char)
{
    // Aca se escribe el codigo que se ejecuta cuando se pulsa una tecla.
}

void procesarClic(int, int)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace un clic en (X,Y)
}

void tickDelReloj()
{
    // Aca se escribe el codigo que se ejecuta periodicamente cada MILISEGUNDOS_RELOJ milisegundos.
}
