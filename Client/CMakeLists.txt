project(ClientLib)

FILE(GLOB_RECURSE myFiles *.cpp *.h) #Almacena todos los archivos ejecutables .cpp y .h en myFiles

add_library(client_classes
        ${myFiles} # Los guarda en la libreria client_classes
        )
