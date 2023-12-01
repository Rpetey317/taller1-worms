project(Worms)

find_package(Qt5Widgets COMPONENTS Widgets REQUIRED)

FILE(GLOB_RECURSE myFiles *.cpp *.h) #Almacena todos los archivos ejecutables .cpp y .h en myFiles

# Remove SdlManager files
list(FILTER myFiles EXCLUDE REGEX "SdlManager/.*")

# Remove Box2D files
list(FILTER myFiles EXCLUDE REGEX "Box2D/.*")

add_subdirectory(Launcher)

add_library(client_classes
        ${myFiles} # Los guarda en la libreria client_classes
        )

target_link_libraries(client_classes Qt5::Widgets
        qtLauncher)

target_include_directories(client_classes PUBLIC qtLauncher)


#### DE ACA PARA ABAJO ERA EL CMAKE Q ESTABA EN EL LAUNCHER PARA EJECUTAR QT

# # Find the QtWidgets library
# find_package(Qt5Widgets COMPONENTS Widgets REQUIRED)
        
# # Esta macro toma cada uno los parámetros y ejecuta *uic* sobre ellos
# # La aplicacion uic genera headers con la definición de los widgets
# # a partir de un archivo .ui
# # Los nombres de los headers generados se guardan en la variable pasada
# # como primer parámetro.
# # No, no los genera con la carpeta como prefijo.
# qt5_wrap_ui(UIS_HEADERS
#         Forms/super_duper_tuki.ui
#         Forms/crear_partida_nueva.ui
#         Forms/unirse_a_partida.ui
# )
        
# set(SOURCES
#         Sources/Greeter.cpp
#         Sources/main.cpp
#         Sources/CreateGame.cpp
#         Sources/JoinGame.cpp
#         DataLoggin/DataLoggin.cpp # Clase que deberia devolver el Qt Launcher
#         )
        
# add_executable(qtLauncher
#         ${SOURCES}
#         ${UIS_HEADERS})
        
# # Use the Widgets module from Qt 5.
# target_link_libraries(qtLauncher Qt5::Widgets)
        