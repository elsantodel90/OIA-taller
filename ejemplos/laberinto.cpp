#include <string>
#include <cstdlib>
#include <ctime>
#include <queue>
#include "funcionesDeBiblioteca.h"

using namespace std;

// Las siguientes funciones y constantes son las que el "framework" espera que existan.
// Se deben completar para crear el programa.

const int ANCHO_TILE = 60;
const int ALTO_TILE = 80;
const int ANCHO_LABERINTO = 25;
const int ALTO_LABERINTO = 12;
extern const int RESOLUCION_HORIZONTAL = ANCHO_LABERINTO * ANCHO_TILE;
extern const int RESOLUCION_VERTICAL = ALTO_LABERINTO * ALTO_TILE;
extern const int TAMANIO_TEXTO = 150;
extern const string TITULO_PROGRAMA = "Laberinto";
extern const int MILISEGUNDOS_RELOJ = 1000;

bool TODO_VISIBLE = false;

const int VACIO = 0;
const int PARED = 1;
const int TARGET = 2;

int laberinto[ANCHO_LABERINTO][ALTO_LABERINTO];

const int GROSOR = 2;

bool dentroDelTablero(int i,int j)
{
    return 0 <= i && i < ANCHO_LABERINTO && 0 <= j && j < ALTO_LABERINTO;
}

void dibujarCaja(int x1,int y1, int x2, int y2)
{
    dibujarRectangulo(x1,y1,x2,y2, GRIS_CLARO);
    dibujarRectangulo(x1-GROSOR,y1-GROSOR, x1+GROSOR, y2+GROSOR, NEGRO);
    dibujarRectangulo(x1-GROSOR,y1-GROSOR, x2+GROSOR, y1+GROSOR, NEGRO);
    dibujarRectangulo(x1-GROSOR,y2-GROSOR, x2+GROSOR, y2+GROSOR, NEGRO);
    dibujarRectangulo(x2-GROSOR,y1-GROSOR, x2+GROSOR, y2+GROSOR, NEGRO);
}

void dibujarPared(int x, int y)
{
    dibujarRectangulo(ANCHO_TILE*x, ALTO_TILE*y,ANCHO_TILE*(x+1),ALTO_TILE*(y+1), NEGRO);
}

void dibujarVacio(int x, int y)
{
    dibujarRectangulo(ANCHO_TILE*x, ALTO_TILE*y,ANCHO_TILE*(x+1),ALTO_TILE*(y+1), BLANCO);
}

void dibujarTarget(int x, int y)
{
    dibujarRectangulo(ANCHO_TILE*x, ALTO_TILE*y,ANCHO_TILE*(x+1),ALTO_TILE*(y+1), ROJO);
}

void dibujarRobot(int x,int y)
{
    x = x * ANCHO_TILE + 30;
    y = y * ALTO_TILE + 30;
    const int ANCHO1 = 22;
    const int ALTO1 = 10;
    const int ANTENA = 13;
    const int CUELLO = 6;
    const int ANCHO2 = 16;
    const int ALTO2 = 11;
    const int ANCHO3 = 12;
    const int ALTO3 = 5;
    dibujarCaja(x-ANCHO1,y-ALTO1, x+ANCHO1, y+ALTO1);
    dibujarLinea(x,y-ALTO1,x, y-ALTO1-ANTENA, NEGRO, GROSOR);
    dibujarCirculo(x,y-ALTO1-ANTENA, 2*GROSOR, NEGRO);
    dibujarCirculo(x - ANCHO1 / 3,y, GROSOR, NEGRO);
    dibujarCirculo(x + ANCHO1 / 3,y, GROSOR, NEGRO);
    dibujarCaja(x-ANCHO2,y+ALTO1+CUELLO, x+ANCHO2, y+ALTO1+CUELLO+2*ALTO2);
    dibujarCaja(x-ANCHO2-ANCHO3,y+ALTO1+CUELLO+ALTO2-ALTO3, x-ANCHO2, y+ALTO1+CUELLO+ALTO2+ALTO3);
    dibujarCaja(x+ANCHO2,y+ALTO1+CUELLO+ALTO2-ALTO3, x+ANCHO2+ANCHO3, y+ALTO1+CUELLO+ALTO2+ALTO3);
    dibujarCaja(x-ANCHO2/3 - ANCHO3,y+ALTO1+CUELLO+ALTO2*2, x-ANCHO2/3, y+ALTO1+CUELLO+ALTO2*2+2*ALTO3);
    dibujarCaja(x+ANCHO2/3,y+ALTO1+CUELLO+ALTO2*2, x+ANCHO2/3 + ANCHO3, y+ALTO1+CUELLO+ALTO2*2+2*ALTO3);
    dibujarLinea(x,y+ALTO1+GROSOR,x,y+ALTO1+CUELLO-GROSOR, NEGRO, 1.5*GROSOR);
}

int xRobot = 0, yRobot = 0;

void dibujarCasilla(int i,int j)
{
    if (laberinto[i][j] == VACIO)
        dibujarVacio(i,j);
    else if (laberinto[i][j] == PARED)
        dibujarPared(i,j);
    else if (laberinto[i][j] == TARGET)
        dibujarTarget(i,j);
}

void dibujarRobotYAlrededores()
{
    if (TODO_VISIBLE)
    {
        for (int i=0;i < ANCHO_LABERINTO; i++)
        for (int j=0;j < ALTO_LABERINTO; j++)
        if (dentroDelTablero(i,j))
            dibujarCasilla(i,j);
    }
    else
    {
        for (int i = xRobot - 1; i <= xRobot +1; i++)
        for (int j = yRobot - 1; j <= yRobot +1; j++)
        if (dentroDelTablero(i,j))
            dibujarCasilla(i,j);
    }
    dibujarRobot(xRobot,yRobot);
}

void redibujarTodo()
{
    dibujarRectangulo(0,0,RESOLUCION_HORIZONTAL,RESOLUCION_VERTICAL, GRIS_OSCURO);
    dibujarRobotYAlrededores();
    if (laberinto[xRobot][yRobot] == TARGET)
    {
        const Color colores[5] = {VERDE, AZUL, AMARILLO, MAGENTA, CIAN};
        for (int k = 0; k < 10; k+=2)
        {
            escribirTexto(150+k, RESOLUCION_VERTICAL/2+k, "¡Victoria!", colores[k%5]);
            escribirTexto(750+k, RESOLUCION_VERTICAL/3-k, "¡Victoria!", colores[(k+1)%5]);
            escribirTexto(150+k, RESOLUCION_VERTICAL/4+k, "¡Victoria!", colores[(k+2)%5]);
            escribirTexto(750+k, RESOLUCION_VERTICAL/7-k, "¡Victoria!", colores[(k+3)%5]);
            escribirTexto(450+k, 0.75*RESOLUCION_VERTICAL+k, "¡Victoria!", colores[(k+4)%5]);
        }
    }
}


void maze(int x1, int y1, int x2, int y2, int leftKey, int downKey, int rightKey, int upKey)
{
    if (x2 - x1 >= 3 && y2 - y1 >= 3)
    {
        int xLine = x1 + 1 + rand() % (x2 - x1 - 2);
        int yLine = y1 + 1 + rand() % (y2 - y1 - 2);
        for (int y=y1; y < y2; y++)
            laberinto[xLine][y] = PARED;
        for (int x=x1; x < x2; x++)
            laberinto[x][yLine] = PARED;
        int v[4] = {VACIO, VACIO, VACIO, VACIO};
        v[rand()%4] = PARED;
        int upHole = y1 + rand() % (yLine - y1);
        if (upKey == xLine) {upHole = y1; v[0] = VACIO;}
        int downHole = yLine+1 + rand() % (y2 - yLine-1);
        if (downKey == xLine) {downHole = y2-1; v[1] = VACIO;}
        int leftHole = x1 + rand() % (xLine - x1);
        if (leftKey == yLine) {leftHole = x1; v[2] = VACIO;}
        int rightHole = xLine+1 + rand() % (x2 - xLine-1);
        if (rightKey == yLine) {rightHole = x2-1; v[3] = VACIO;}
        laberinto[xLine][upHole] = v[0];
        laberinto[xLine][downHole] = v[1];
        laberinto[leftHole][yLine] = v[2];
        laberinto[rightHole][yLine] = v[3];
        maze(x1,y1,xLine, yLine, leftKey, leftHole , upHole , upKey);
        maze(xLine+1,y1,x2, yLine, upHole, rightHole, rightKey, upKey);
        maze(x1,yLine+1,xLine, y2, leftKey, downKey, downHole, leftHole);
        maze(xLine+1,yLine+1,x2, y2, downHole, downKey, rightKey, rightHole);
    }
}

void inicializarLaberinto()
{
    for (int i = 0; i < ANCHO_LABERINTO; i++)
    for (int j = 0; j < ALTO_LABERINTO; j++)
        laberinto[i][j] = VACIO;
    srand(time(NULL));
    maze(0, 0, ANCHO_LABERINTO, ALTO_LABERINTO, -1,-1,-1,-1);
}

void ubicarTarget()
{
    int d[ANCHO_LABERINTO][ALTO_LABERINTO];
    for(int i=0;i < ANCHO_LABERINTO;i++)
    for(int j=0;j < ALTO_LABERINTO;j++)
        d[i][j] = -1;
    d[0][0] = 0;
    queue<int> q;
    q.push(0);
    q.push(0);
    const int dx[4] = {-1,1,0,0};
    const int dy[4] = {0,0,1,-1};
    int lastx = 0, lasty = 0;
    while (!q.empty())
    {
        int x = q.front(); q.pop();
        int y = q.front(); q.pop();
        lastx = x;
        lasty = y;
        for(int dir=0;dir<4;dir++)
        {
            int nx = x+dx[dir];
            int ny = y+dy[dir];
            if (dentroDelTablero(nx,ny) && laberinto[nx][ny] == VACIO && d[nx][ny] < 0)
            {
                d[nx][ny] = d[x][y] + 1;
                q.push(nx);
                q.push(ny);
            }
        }
    }
    laberinto[lastx][lasty] = TARGET;
}

void ejecutarAlIniciarElPrograma()
{
    inicializarLaberinto();
    ubicarTarget();
    redibujarTodo();
}

void procesarCargaDeTextoEnCuadro(int , string)
{
    // Aca se escribe el codigo que se ejecuta cuando se carga texto en un cuadro de texto interactivo
}

void procesarClicEnBoton(int)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace clic en un boton
}

void procesarPulsacionDeTecla(char tecla)
{
    tecla = toupper(tecla);
    int newX = xRobot;
    int newY = yRobot;
    if (tecla == 'A')
        newX--;
    if (tecla == 'D')
        newX++;
    if (tecla == 'S')
        newY++;
    if (tecla == 'W')
        newY--;
    if (dentroDelTablero(newX, newY) && laberinto[newX][newY] != PARED)
    {
        xRobot = newX;
        yRobot = newY;
        redibujarTodo();
    }
}

void procesarClic(int, int)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace un clic en (X,Y)
}

void tickDelReloj()
{
    // Aca se escribe el codigo que se ejecuta periodicamente cada MILISEGUNDOS_RELOJ milisegundos.
}
