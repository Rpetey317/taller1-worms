project(ServerLib)

FILE(GLOB_RECURSE myFiles *.cpp *.h) #Almacena todos los archivos ejecutables .cpp y .h en myFiles

add_library(server_classes
        ${myFiles} # Los guarda en la libreria server_classes
        )
