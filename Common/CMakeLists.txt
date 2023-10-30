project(CommonLib)

FILE(GLOB_RECURSE myFiles *.cpp *.h) #Almacena todos los archivos ejecutables .cpp y .h en myFiles

add_library(common_classes
        ${myFiles} # Los guarda en la libreria common_classes
        )
