#include <string>
#include "funcionesDeBiblioteca.h"

using namespace std;

// Las siguientes funciones y constantes son las que el "framework" espera que existan.
// Se deben completar para crear el programa.

extern const int RESOLUCION_HORIZONTAL = 800;
extern const int RESOLUCION_VERTICAL = 500;
extern const int TAMANIO_TEXTO = 30;
extern const string TITULO_PROGRAMA = "OIA-PONG";
extern const int MILISEGUNDOS_RELOJ = 20;

const int LINEAS_CENTRO = 20;
const int GAP_LINEAS_CENTRO = 15;
const int GROSOR_LINEAS_CENTRO = 2;

const int MIN_X = 20;
const int MAX_X = RESOLUCION_HORIZONTAL/2 - 30;

const int ANCHO_PADDLE = 10;
const int ALTO_PADDLE = 60;
const Color COLOR_PADDLE = VERDE;
const int PADDLE_X_SPEED = 4;
const int PADDLE_Y_SPEED = 3;
const int IA_PADDLE_SPEED = 2;

const int BALL_RADIUS = 6;
const Color BALL_COLOR = AMARILLO;

const int BALL_SPEED = 6;

int puntajes[2] = {0,0};

struct Paddle
{
    int x,y;
};

Paddle paddle[2] = {{20, 60},{RESOLUCION_HORIZONTAL - 20 - ANCHO_PADDLE, RESOLUCION_VERTICAL - 60 - ALTO_PADDLE}};


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

void controlarPaddle(Paddle &p, char izquierda, char derecha, char abajo, char arriba, char tecla)
{
    tecla = toupper(tecla);
    if (tecla == izquierda)
        p.x -= PADDLE_X_SPEED;
    else if (tecla == derecha)
        p.x += PADDLE_X_SPEED;
    else if (tecla == abajo)
        p.y += PADDLE_Y_SPEED;
    else if (tecla == arriba)
        p.y -= PADDLE_Y_SPEED;
}

void procesarPulsacionDeTecla(char tecla)
{
    Paddle paddleOriginal = paddle[0];
    controlarPaddle(paddle[0], 'A', 'D', 'S', 'W', tecla);
    if (paddle[0].x > RESOLUCION_HORIZONTAL / 2 - 10 ||
        paddle[0].x < ANCHO_PADDLE)
        paddle[0] = paddleOriginal;
}

void procesarClic(int, int)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace un clic en (X,Y)
}

struct Pelota
{
    int x,y,vx,vy;
    
    // Devuelve True si hubo un rebote en el fondo.
    bool avanzar(int valorDelPunto)
    {
        if (y >= RESOLUCION_VERTICAL - BALL_RADIUS || y <= BALL_RADIUS)
            vy = -vy;
        bool rebote = false;
        if (x >= RESOLUCION_HORIZONTAL - BALL_RADIUS)
        {
            rebote = true;
            puntajes[0] += valorDelPunto;
            vx = -vx;
        }
        else if (x <= BALL_RADIUS)
        {
            rebote = true;
            puntajes[1] += valorDelPunto;
            vx = -vx;
        }
        x += vx;
        y += vy;
        return rebote;
    }
};

Pelota pelota = {150, 150, BALL_SPEED, BALL_SPEED};

void dibujarPaddle(Paddle p)
{
    dibujarRectangulo(p.x - ANCHO_PADDLE/2, p.y-ALTO_PADDLE/2, p.x + ANCHO_PADDLE/2, p.y + ALTO_PADDLE/2, COLOR_PADDLE);
}

bool colisiona(Paddle p)
{
    return abs(p.x - pelota.x) <= BALL_RADIUS + ANCHO_PADDLE / 2 &&
           abs(p.y - pelota.y) <= BALL_RADIUS + ALTO_PADDLE / 2;
}

int signo(int x)
{
    return (x>0) - (x<0);
}

int calcularPosicionY(int x)
{
    Pelota copiaPelota = pelota;
    int s = signo(x - copiaPelota.x);
    while (signo(x - copiaPelota.x) == s)
        copiaPelota.avanzar(0);
    return copiaPelota.y;
}

void movimientoIA(Paddle &p)
{
    int posicionEsperadaPelota = calcularPosicionY(p.x);
    if (posicionEsperadaPelota > p.y + 3)
        p.y += IA_PADDLE_SPEED;
    else if (posicionEsperadaPelota < p.y - 3)
        p.y -= IA_PADDLE_SPEED;
}

bool cruzoCancha = true;
int cancha = 0;

void tickDelReloj()
{
    movimientoIA(paddle[1]);
    dibujarRectangulo(0, 0, RESOLUCION_HORIZONTAL, RESOLUCION_VERTICAL , NEGRO);
    if (cancha != signo(pelota.x - RESOLUCION_HORIZONTAL/2))
            cruzoCancha = true;
    if (cruzoCancha && (colisiona(paddle[0]) || colisiona(paddle[1])))
    {
        pelota.vx = -pelota.vx;
        cruzoCancha = false;
        cancha = signo(pelota.x - RESOLUCION_HORIZONTAL/2);
    }
    if (pelota.avanzar(1)) cruzoCancha = true;
    dibujarDivisionCentral();
    dibujarCirculo(pelota.x, pelota.y, BALL_RADIUS , BALL_COLOR);
    for (int i=0; i < 2; i++) dibujarPaddle(paddle[i]);
    escribirTexto(0,RESOLUCION_VERTICAL - 40, to_string(puntajes[0]), ROJO);
    escribirTexto(RESOLUCION_HORIZONTAL - 50,RESOLUCION_VERTICAL - 40, to_string(puntajes[1]), ROJO);
}
