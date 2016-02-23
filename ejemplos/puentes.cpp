#include <string>
#include <vector>
#include <algorithm>
#include "funcionesDeBiblioteca.h"

using namespace std;

// Las siguientes funciones y constantes son las que el "framework" espera que existan.
// Se deben completar para crear el programa.

extern const int RESOLUCION_HORIZONTAL = 800;
extern const int RESOLUCION_VERTICAL = 500;
extern const int TAMANIO_TEXTO = 15;
extern const string TITULO_PROGRAMA = "Puentes críticos";
extern const int MILISEGUNDOS_RELOJ = 1000;

const int RADIO_PUNTO = 7;
const Color COLOR_PUNTO = AZUL;
const Color COLOR_SELECCIONADO = VERDE;
const Color COLOR_CONEXION = NEGRO;
const Color COLOR_CONEXION_CRITICA = ROJO;
const int GROSOR_CONEXIONES = 3;

struct Punto
{
    int x,y;
};

const int INGRESANDO_PUNTOS = 0;
const int INGRESANDO_CONEXIONES = 1;
const int LISTO = 2;

int paso, puntoSeleccionado;

vector<Punto> puntos;
vector<vector<int>> conexiones;

void dibujarFondo()
{
    dibujarRectangulo(0,0,RESOLUCION_HORIZONTAL, RESOLUCION_VERTICAL, GRIS_CLARO);
}

void dibujarPunto(int indice, Color color)
{
    dibujarCirculo(puntos[indice].x, puntos[indice].y, RADIO_PUNTO, color);
}

void dibujarConexion(int a, int b, Color color)
{
    dibujarLinea(puntos[a].x, puntos[a].y, puntos[b].x, puntos[b].y, color, GROSOR_CONEXIONES);
}

void dibujarTodosLosPuntos()
{
    for (int i=0;i < (int)puntos.size(); i++)
        dibujarPunto(i, COLOR_PUNTO);
}

void ejecutarAlIniciarElPrograma()
{
    // Aca se escribe el codigo que se ejecuta al momento que comienza la ejecucion del programa
    dibujarFondo();
    escribirTexto(0,0, "Ingresando puntos...", NEGRO);
    crearBoton(0, RESOLUCION_VERTICAL-30,50, RESOLUCION_VERTICAL, "Listo");
    paso = INGRESANDO_PUNTOS;
    puntos.clear();
    conexiones.clear();
}

void procesarCargaDeTextoEnCuadro(int , string )
{
    // Aca se escribe el codigo que se ejecuta cuando se carga texto en un cuadro de texto interactivo
    
}

namespace NotebookPuentes
{
    const int MAXN = 10000;
    // g es la lista de adyacencia de un grafo en forma vector<int>, N es cantidad de vertices,
    // MAXN es una cota superior tanto para cantidad de vertices como cantidad de aristas
    #define g conexiones
    int D[MAXN], L[MAXN], J[MAXN], I[MAXN]; char E[MAXN];
    int P[2 * MAXN], R, S[2 * MAXN], K, A[MAXN], T;
    void dfs (int r) {
        E[r] = K = T = R = 0; A[S[K++] = r] = -1;
        while (K) { int u = S[--K], v;
            switch (E[u]) {
            case 0: L[u] = D[u] = T++; J[u] = I[u] = 0; P[R++] = u;
            case 1: c1: if (I[u] == (int)g[u].size()) break;
                if (D[v = g[u][I[u]]] == -1) {
                    E[A[v] = S[K++] = u] = 2, E[S[K++] = v] = 0;
                } else { if (v != A[u] && D[v] < L[u]) L[u] = D[v];
                    I[u]++; E[S[K++] = u] = 1;
                } break;
            case 2: v = g[u][I[u]], P[R++] = u;
                if (L[v] < L[u]) L[u] = L[v];
                if (L[v] >= D[v]) {
                    dibujarConexion(u, v, COLOR_CONEXION_CRITICA);
                    dibujarPunto(u, COLOR_PUNTO);
                    dibujarPunto(v, COLOR_PUNTO);
                }
                I[u]++; goto c1;
            }
        }
    }
    void BC()
    {
        int N = g.size();
        for(int i=0;i<N;i++) D[i] = -1;
        for(int i=0;i<N;i++) if(D[i] == -1) dfs(i);
    }
    #undef g
};

void procesarClicEnBoton(int )
{
    // Aca se escribe el codigo que se ejecuta cuando se hace clic en un boton
    if (paso == INGRESANDO_PUNTOS)
    {
        dibujarFondo();
        escribirTexto(0,0, "Ingresando conexiones...", NEGRO);
        dibujarTodosLosPuntos();
        puntoSeleccionado = -1;
        paso = INGRESANDO_CONEXIONES;
    }
    else if (paso == INGRESANDO_CONEXIONES)
    {
        NotebookPuentes::BC();
        escribirTexto(200,0, "¡¡LISTO!! Conexiones criticas calculadas.", ROJO);
        paso = LISTO;
    }
    else if (paso == LISTO)
        ejecutarAlIniciarElPrograma();
}

void procesarPulsacionDeTecla(char )
{
    // Aca se escribe el codigo que se ejecuta cuando se pulsa una tecla.
}

int puntoCliqueado(int x, int y)
{
    for (int i=0; i<(int)puntos.size(); i++)
    if (abs(puntos[i].x - x) <= RADIO_PUNTO && abs(puntos[i].y - y) <= RADIO_PUNTO)
        return i;
    return -1;
}

void procesarClic(int x, int y)
{
    // Aca se escribe el codigo que se ejecuta cuando se hace un clic en (X,Y)
    if (paso == INGRESANDO_PUNTOS)
    {
        puntos.push_back({x,y});
        conexiones.push_back({});
        dibujarPunto(puntos.size()-1, COLOR_PUNTO);
    }
    else if (paso == INGRESANDO_CONEXIONES)
    {
        int indice = puntoCliqueado(x,y);
        if (indice >= 0)
        {
            if (puntoSeleccionado < 0)
            {
                puntoSeleccionado = indice;
                dibujarPunto(indice, COLOR_SELECCIONADO);
            }
            else
            {
                if (puntoSeleccionado != indice &&
                    find(conexiones[puntoSeleccionado].begin(), conexiones[puntoSeleccionado].end(), indice) == conexiones[puntoSeleccionado].end())
                {
                    conexiones[puntoSeleccionado].push_back(indice);
                    conexiones[indice].push_back(puntoSeleccionado);
                    dibujarConexion(indice, puntoSeleccionado, COLOR_CONEXION);
                    dibujarPunto(indice, COLOR_PUNTO);
                }
                dibujarPunto(puntoSeleccionado, COLOR_PUNTO);
                puntoSeleccionado = -1;
            }
        }
    }
}

void tickDelReloj()
{
    // Aca se escribe el codigo que se ejecuta periodicamente cada MILISEGUNDOS_RELOJ milisegundos.
}
