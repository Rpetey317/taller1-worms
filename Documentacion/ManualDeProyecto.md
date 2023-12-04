# MANUAL DE PROYECTO

# Tabla de Contenidos

- [Integrantes y division de tareas](#integrantes-y-division-de-tareas)
- [Evolucion del proyecto](#evolucion-del-proyecto)
- [Inconvenientes del proyecto](#inconvenientes-del-proyecto)
- [Conclusion](#conclusion)


# Integrantes y division de tareas

- Ruben Bohorquez: EEncargado de toda la logica del servidor y su protocolo.

- Paolo Belforte: Encargado de la interfaz del cliente utilizando SDL. Encargado de hacer el editor de mapas, 
    y de cargar todos los archivos en YAML. Encargado de los efectos de sonido (con su propia voz). 

- Inaki Pujato: Box2d, Sistema de vida de gusanos

- Mateo Lardiez: Encargado de crear los archivos ejecutables CMake. Encargado de toda la logica del cliente y 
    su protocolo . Encargado de hacer el launcher con QT para iniciar o unirse a una partida

# Evolucion del proyecto

### Semana 1
- En la primer semana principalmente todos nos familiarizamos con nuestros nuevos entornos. Comenzamos la 
implementacion del modelo Client-Server ya que lo conociamos de los TPs individuales.
### Semana 2
### Semana 3
 Seguimos construyendo sobre la base del Client-Server y comenzamos a avanzar por diferentes frentes cada uno con lo suyo.
### Semana 4
 Semana de poco avance. Principalmente avances individuales, pero problemas en el intento de unirlo.
### Semana 5
 Similar a semana 4.
### Semana 6
 La mayoria de la semana fue utilizada en juntar todos los pedazos individualmente programados.

# Inconvenientes del proyecto
 El mayor inconveniente fue a la hora de unir todo. Utilizamos un enfoque de preparar en diferido y traer codigo ya funcional para unir al proyecto. Pero no fue una buena estrategia. Lo que tal vez funcionaba en una implementacion en paralelo nos encontrabamos con que no encajaba en el protocolo o sistema ya existente.
Si hubiese que comenzar de nuevo, creemos que lo primero a cambiar seria asegurarse desde un principio que la conexion de todo funcione.
 Por otro lado, varios inconvenientes se dieron tambien por el uso de bibliotecas nuevas con las que no estabamos familiarizados. Perdimos tiempo en adaptacion y aprendiazaje, pero entendemos tambien que es algo necesario e inevitable al usar cosas nuevas.

# Conclusion
 Nuestro principal enemigo fue el tiempo y el error en el enfoque de compartimentar los problemas desde tan temprano. Sin embargo hicimos todo con esfuerzo y pasion en busca de crear el mejor resultado posible. Creemos que fue un proyecto de mucho crecimiento y aprendizaje y valoramos la experiencia independientemente del resultado.
