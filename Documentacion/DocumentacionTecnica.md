# DOCUMENTACION TECNICA

# Tabla de Contenidos

- [Introduccion](#introduccion)
- [Requerimientos del sistema](#requerimientos-del-sistema)
- [Modulo comun](#descripcion-general)
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


# Descripcion general

El trabajo cuenta con dos programas ejecutables, un cliente y un servidor, estos tendrán interacción
por medio de un protocolo de comunicación basado en sockets TCP/IP.
En el contexto de una aplicación o juego, el cliente cumple un papel fundamental al gestionar la
comunicación con el usuario en la parte visible y accesible de la interfaz (front-end). Esto implica que
el cliente no solo recibe y procesa los eventos que ocurren, sino también las acciones que el usuario
realiza. Por otro lado, el servidor asume la responsabilidad de manejar toda la lógica del juego o la
aplicación (back-end), respondiendo de manera adecuada a las acciones que el usuario lleva a cabo.

# Modulo cliente

El módulo del cliente se encarga de establecer la conexión con el Servidor, gestionar las acciones
al Servidor y procesar los eventos recibidos por el Servidor. 

El cliente tiene su interfaz gráfica, la cual consta del Launcher y del SdlManager.

El launcher, el cual esta construido mediante la libreria Qt5, es una parte importante del módulo del cliente en 
este proyecto. Es una interfaz gráfica construida utilizando la biblioteca Qt5 que permite al usuario realizar 
diferentes acciones, como crear nuevas partidas o unirse a partidas existentes.

El Launcher actúa como el punto de entrada para que el usuario interactúe con el juego. Proporciona una forma 
intuitiva y fácil de acceder a las funcionalidades del juego.

Por otro lado se encuentra el SdlManager el cual es parte del módulo del cliente y se encarga de gestionar la interfaz 
gráfica del juego utilizando la biblioteca SDL (Simple DirectMedia Layer).

El SdlManager se encarga de realizar tareas como la inicialización de la ventana del juego, la carga de recursos 
gráficos (como imágenes y fuentes), la gestión de eventos de entrada del usuario (como teclado y mouse), y la 
renderización de los elementos visuales en la pantalla.

En resumen, el SdlManager es responsable de proporcionar una interfaz gráfica interactiva y visualmente atractiva 
para que el usuario pueda interactuar con el juego. 

El cliente tiene dos queues bloqueantes, una para enviar Acciones al servidor, y otra para recibir eventos de parte
del servidor. Para el manejo de la coneccion entre cliente-servidor, se utiliza el clientProtocol, el cual es el 
encargado de recibir los mensajes y crear los eventos correspondientes, como tambien enviar las acciones como corresponda.

El cliente esta compuesto por tres threads:
- el thread main: ejecuta el launcher, luego una vez que se hayan ingresado los datos ejecuta el cliente (gameProcessing), 
 y despues de eso ejecuta el sdlManager

- el thread Receiver:  Su función principal es recibir eventos del servidor y pushearlos a la queue de eventos.
 En el contexto del juego, el servidor envía eventos al cliente para informar sobre cambios en el estado del juego, como 
 movimientos de otros jugadores, disparos, actualizacion de posiciones, etc. El ClientReceiverThread se encarga de 
 recibir estos eventos pushearlos a la queue de eventos. Estos eventos luego son poppeados y procesados por el SdlManager
 El hilo ClientReceiverThread utiliza una cola bloqueante para recibir los eventos del servidor. Una cola bloqueante es 
 una estructura de datos que permite a un hilo esperar hasta que haya elementos disponibles

- el thread Sender: es el responsable de enviar acciones desde el cliente al servidor . Su función principal es tomar las 
acciones generadas por el jugador en el cliente y enviarlas al servidor para que se procesen y se reflejen en el estado del juego.
En el contexto del juego, las acciones pueden incluir movimientos del jugador, disparos, etc. Estas acciones son capturadas 
por el cliente y se encolan en una cola bloqueante específica para el envío de acciones al servidor.

El thread Sender se encarga de tomar las acciones de esta cola bloqueante y enviarlas al servidor a través del protocolo de 
comunicación establecido. Utiliza el clientProtocol, que es el encargado de recibir los mensajes y crear los eventos 
correspondientes para el servidor.

En la siguiente imagen se puede ver el flujo general de los threads del cliente:
![Alt text](threadsClient.png)

# Modulo servidor