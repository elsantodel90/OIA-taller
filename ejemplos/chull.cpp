#include <iostream>
#include <vector>
#include <algorithm>
#include "funcionesDeBiblioteca.h"

using namespace std;

extern const int RESOLUCION_HORIZONTAL = 600;
extern const int RESOLUCION_VERTICAL =  600;
extern const int TAMANIO_TEXTO = 12;
extern const string TITULO_PROGRAMA = "Cerco óptimo";
extern const int MILISEGUNDOS_RELOJ = 1000;

const int RADIO_PUNTOS = 4;
const Color COLOR_PUNTOS = ROJO;
const Color COLOR_CHULL = MAGENTA;

namespace ChullNotebook
{
    typedef long long tipo;
    tipo pcruz(tipo x1,tipo y1,tipo x2,tipo y2){return x1*y2-x2*y1;}
    struct pto {
      tipo x,y;
      tipo n2(pto &p2)const{
          #define sqr(x) ((x)*(x))
        return sqr(x-p2.x)+sqr(y-p2.y);
      }
    } r;
    tipo area3(pto a, pto b, pto c){
      return pcruz(b.x-a.x,b.y-a.y,c.x-a.x,c.y-a.y);
    }
    bool men2(const pto &p1, const pto &p2){
      return (p1.y==p2.y)?(p1.x<p2.x):(p1.y<p2.y);
    }
    bool operator<(const pto &p1,const pto &p2){
      tipo ar = area3(r,p1,p2);
      return(ar==0)?(p1.n2(r)<p2.n2(r)):ar>0;
      //< clockwise, >counterclockwise
    }
    typedef vector<pto> VP;
    VP chull(VP & l){
      VP res = l;  if(l.size()<3) return res;
      r = *(min_element(res.begin(),res.end(),men2));
      sort(res.begin(),res.end());
      int i=0;VP ch;ch.push_back(res[i++]);ch.push_back(res[i++]);
      while(i<(int)res.size())  // area3 > clockwise, < counterclockwise
        if(ch.size()>1 && area3(ch[ch.size()-2],ch[ch.size()-1],res[i])<=0)
          ch.pop_back();
        else
          ch.push_back(res[i++]);
      return ch;
    }
};

typedef ChullNotebook::pto Punto;

vector<Punto> puntos;

const int ALTO_BOTONES = 25;

int botonLimpiar, botonCalcular;

void limpiarPantalla()
{
    dibujarRectangulo(0,0,RESOLUCION_HORIZONTAL, RESOLUCION_VERTICAL, BLANCO);
}

void dibujarPunto(Punto p)
{
    dibujarCirculo(p.x,p.y, RADIO_PUNTOS, COLOR_PUNTOS);
}

void ejecutarAlIniciarElPrograma()
{
    botonCalcular = crearBoton(0,RESOLUCION_VERTICAL - ALTO_BOTONES + 5, 60, RESOLUCION_VERTICAL, "Calcular");
    botonLimpiar = crearBoton(65,RESOLUCION_VERTICAL - ALTO_BOTONES + 5, 125, RESOLUCION_VERTICAL, "Limpiar");
    limpiarPantalla();
}

void procesarCargaDeTextoEnCuadro(int, string)
{
    // Aca se escribe el codigo que se ejecuta cuando se carga texto en un cuadro de texto interactivo
}

void procesarClicEnBoton(int boton)
{
    if (boton == botonLimpiar)
    {
        limpiarPantalla();
        puntos.clear();
    }
    if (boton == botonCalcular)
    {
        ChullNotebook::VP chull = ChullNotebook::chull(puntos);
        limpiarPantalla();
        for (Punto p : puntos)
            dibujarPunto(p);
        if (!chull.empty())
        {
            chull.push_back(chull.front());
            for (int i = 0; i < (int)chull.size() - 1; i++)
                dibujarLinea(chull[i].x, chull[i].y, chull[i+1].x, chull[i+1].y, COLOR_CHULL);
        }
    }
}

void procesarPulsacionDeTecla(char)
{
    // Aca se escribe el codigo que se ejecuta cuando se pulsa una tecla.
}

void procesarClic(int X, int Y)
{
    Punto p = {X,Y};
    puntos.push_back(p);
    dibujarPunto(p);
}

void tickDelReloj()
{
    // Aca se escribe el codigo que se ejecuta periodicamente cada MILISEGUNDOS_RELOJ milisegundos.
}
