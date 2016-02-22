#include <string>
#include "funcionesDeBiblioteca.h"

using namespace std;

// Las siguientes funciones y constantes son las que el "framework" espera que existan.
// Se deben completar para crear el programa.

extern const int RESOLUCION_HORIZONTAL = 800;
extern const int RESOLUCION_VERTICAL = 500;
extern const int TAMANIO_TEXTO = 15;
extern const string TITULO_PROGRAMA = "OIA-PONG";
extern const int MILISEGUNDOS_RELOJ = 20;

const int LINEAS_CENTRO = 20;
const int GAP_LINEAS_CENTRO = 15;
const int GROSOR_LINEAS_CENTRO = 2;

const int MIN_X = 20;
const int MAX_X = RESOLUCION_HORIZONTAL/2 - 30;

const int ANCHO_PADDLE = 10;
const int ALTO_PADDLE = 60;

const int BALL_RADIUS = 6;
const Color BALL_COLOR = AMARILLO;

const int BALL_SPEED = 4;

int playerX[2] = {MIN_X, MIN_X};
int playerY[2] = {RESOLUCION_VERTICAL/2,RESOLUCION_VERTICAL/2};

void dibujarDivisionCentral()
{
    for(int numeroDeLinea=0; numeroDeLinea < LINEAS_CENTRO; numeroDeLinea++)
    {
        int trozo = ((RESOLUCION_VERTICAL - GAP_LINEAS_CENTRO) / LINEAS_CENTRO);
        int y = GAP_LINEAS_CENTRO + numeroDeLinea * trozo;
        dibujarLinea(RESOLUCION_HORIZONTAL/2,y,RESOLUCION_HORIZONTAL/2,y+trozo-GAP_LINEAS_CENTRO,BLANCO, GROSOR_LINEAS_CENTRO);
    }
}

void ejecutarAlIniciarElPrograma()
{
    dibujarDivisionCentral();
}

void procesarCargaDeTextoEnCuadro(int, string)
{
    // Aca se escribe el codigo que se ejecuta cuando se carga texto en un cuadro de texto interactivo
}

void procesarClicEnBoton(int)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace clic en un boton
}

void procesarPulsacionDeTecla(char tecla)
{
    // Aca se escribe el codigo que se ejecuta cuando se pulsa una tecla.
}

void procesarClic(int, int)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace un clic en (X,Y)
}

int ballX = 150;
int ballY = 150;
int ballVX = BALL_SPEED;
int ballVY = BALL_SPEED;

void tickDelReloj()
{
    dibujarCirculo(ballX, ballY, BALL_RADIUS , NEGRO);
    if (ballY >= RESOLUCION_VERTICAL - BALL_RADIUS || ballY <= BALL_RADIUS)
        ballVY = -ballVY;
    if (ballX >= RESOLUCION_HORIZONTAL - BALL_RADIUS || ballX <= BALL_RADIUS)
        ballVX = -ballVX;
    ballX += ballVX;
    ballY += ballVY;
    dibujarDivisionCentral();
    dibujarCirculo(ballX, ballY, BALL_RADIUS , BALL_COLOR);
}
