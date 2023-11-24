project(ClientLib)

FILE(GLOB_RECURSE myFiles *.cpp *.h) #Almacena todos los archivos ejecutables .cpp y .h en myFiles

# Remove SdlManager files
list(FILTER myFiles EXCLUDE REGEX "SdlManager/.*")

# Remove Box2D files
list(FILTER myFiles EXCLUDE REGEX "Box2D/.*")

add_library(client_classes
        ${myFiles} # Los guarda en la libreria client_classes
        )
