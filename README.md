# Worms
Final group Project of Programming Workshop from University of Buenos Aires (UBA). It's a simplified, 2-D version of the multiplayer game 'Worms' with a client-server model

# Taller de Programación I - Cátedra Veiga - FIUBA

# Trabajo Práctico Final

| Padrón | Alumnos                  |
|--------|--------------------------|
| 109442 | Bohorquez, Ruben         | 
| 109432 | Belforte, Paolo          |
| 109131 | Pujato, Inaki            |
| 107992 | Lardiez, Mateo           |


# Tabla de Contenidos

- [Guía de Instalación](#guia-de-instalación)
    - [Requisitos](#requisitos)
    - [Instalación de Dependencias](#instalación-de-dependecias)
- [Guía de Usuario](#guía-de-usuario)
    - [Formas de ejecución](#formas-de-ejecucción)
        - [Server](#server)
        - [Cliente](#cliente)
- [Cómo jugar](#cómo-jugar)
    - [Movimientos](#movimientos)
    - [Crear Partida](#crear-partida)
    - [Unirse a Partida](#unirse-a-partida)
- [Juego](#flujo-de-juego)
    - [Sala de espera](#sala-de-espera)
    - [Jugar](#jugar)
    - [Cheats](#cheats)



# Guía de instalación

## Requisitos

Uno de los requisitos más importantes que utiliza el juego es el sistema operativo sobre el cual se ejecuta, para lo cual se debera contar con alguna distribucion que utilice GNU/Linux como sistema operativo.

Además se debe contar con tanto git, CMake y Make, para la descarga del juego así como para la compilación del juego.

## Instalación de Dependencias

Para instalar CMake y make, corre los siguientes comandos:

sudo apt update
sudo apt install cmake
sudo apt install make


En este juego se utiliza SDL, para el cual hay que instalar diversos archivos:

- Para instalar y usar la versión 0.18 de libsdl2pp:
    sudo apt-get install libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev libsdl2-dev

- Descargar los siguientes 3 zip:
    1) ( 2.6.3, https://github.com/libsdl-org/SDL_image/releases/tag/release-2.6.3)
    2) libsdl2-mixer (2.6.3, https://github.com/libsdl-org/SDL_mixer/releases/tag/release-2.6.3)
    3) libsdl2-ttf (2.20.2, https://github.com/libsdl-org/SDL_ttf/releases/tag/release-2.20.2)
  Hacer unzip de cada uno y luego ejecutar en cada respectiva carpeta:
    cd carpeta_sdl_x
    mkdir build
    cd build
    cmake ..
    make -j4
    sudo make install
  
  Luego ir a https://github.com/libSDL2pp/libSDL2pp/releases y descargarse el zip de la ultima version (libSDL2pp-0.18.1), hacer unzip y ejecutar:
    cd libSDL2pp-0.18.1
    mkdir build
    cd build
    cmake ..
    make -j4
    sudo make install

  con eso deberian estar todas las dependencias instaladas para utilizar SDL. Luego, ir a carpeta Images y hacer unzip de los 2 zip

Tambien se utiliza QT, para el cual se debe correr en la terminal el comando:
    sudo apt-install qt5-default

Se utiliza tambien box2D, para el cual no se debe instalar nada manualmente, ya que se carga todo en su respectivo CMake

## Ejecutando el juego

Debe clonar el repositorio corriendo el siguiente comando en la terminal de la carpeta que usted quiera:

- https://github.com/Rpetey317/taller1-worms.git

Luego crear la carpeta build y ejecutar el CMake:
    mkdir build
    cd build
    cmake ..
    make

Esto creara los archivos ejecutables server y client.

# Guia de Usuario

## Formas de Ejecucion

### Server

En una terminal, localizarse en el directorio build, creado anteriormente, ingresa el comando:

- ./server <port number> . Como por ejemplo ./server 8080

### Cliente

En otra terminal y parandote en el directorio build, ingrese el comando:

- ./client 127.0.0.1 <port number>. Como por ejemplo ./client 127.0.0.1 8080. Ambos deben tener el mismo port number.

Al poner el mismo numero de puerto, el cliente se conecta al server, para luego crear o unirse a una partida.

# Como Jugar

## Movimientos

## Launcher

Al conectarse el cliente con el servidor, se ejecuta el qt launcher, el cual le permite al usuario elegir unirse a una partida, 
crear una partida, o crear un nuevo mapa, como se puede ver en la siguiente imagen. NO OLVIDARSE DE INGRESAR IMAGEN

## Crear Partida

## Unirse a Partida

# Flujo de juego

## Sala de Espera

## Jugar

## Cheats
