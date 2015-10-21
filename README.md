# OIA-taller
## Ejecución de ejemplos

La carpeta "ejemplos" contiene algunos ejemplos de programas que se pueden realizar con este framework sencillo. Como solamente se debe modificar el archivo "programa.cpp" para generar un programa, cada ejemplo corresponde a un archivo de código fuente "programa.cpp" distinto.

Para compilar uno de ellos, basta con reemplazar el "programa.cpp" del directorio principal (que inicialmente contiene únicamente un esqueleto con las funciones que el framework espera que el usuario implemente) con el .cpp del ejemplo correspondiente.

## Instalación en ubuntu

* Clonar el repo
* Instalar el compilador de c++
    - apt-get install g++
* Instalar SDL2 y SDL_TTF, incluyendo los paquetes dev:
    - apt-get install libsdl2-2.0-0 libsdl2-dev
    - apt-get install libsdl2-ttf-2.0-0 libsdl2-ttf-dev
* Correr el makefile con "make" en el directorio del repo
* Correr el programa con ./programa
* Profit
