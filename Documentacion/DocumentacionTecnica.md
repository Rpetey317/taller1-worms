# DOCUMENTACION TECNICA

# Tabla de Contenidos

- [Introduccion](#introduccion)
- [Requerimientos del sistema](#requerimientos-del-sistema)
- [Modulo comun](#modulo-comun)
- [Modulo cliente](#modulo-cliente)
- [Modulo servidor](#modulo-servidor)

# Introduccion

Este TP busca implementar una copia del videojuego Worms, juego multijugador con sistema de turnos en el que pueden jugar
2 o mas jugadores. 

# Requerimientos del sistema

El proyecto se ejecuta en un sistema operativo GNU/Linux y se utilizan distintas librerias, necesarias para poder
compilar y ejecutar el juego. Estas son las siguientes:

- SDL2pp
 Esta librerı́a es el motor gráfico del juego, se encarga de todo lo relacionado con la renderización,
 musicalización e interacción con el usuario (Cliente), determinando cada acción del usuario para luego 
 mostrarla en pantalla. Se utiliza tambien para el editor de mapas

- Box2d
 Box2D es una biblioteca libre que implementa un motor físico en dos dimensiones. Se utiliza para implementar
 toda la fisica del juego

- QT
 Qt5, es una librerı́a que, utiliza el lenguaje de programacion C++, para trabajar con interfaz gráfica. En este
 proyecto se utiliza el module de Widgets para la creacion de la interfaz mediante el uso de buttons, labels,
 lineEdits, etc. Se utiliza en el Launcher, para que el usuario pueda crear nuevas partidas o unirse a alguna

- YAML-cpp
 Se utiliza para parsear archivos YAML, mas especificamente los mapas en los cuales se puede jugar. Cuando el editor
 crea un nuevo mapa, se genera un nuevo archivo YAML que se guarda en la carpeta del proyecto


# Modulo comun



# Modulo cliente

# Modulo servidor