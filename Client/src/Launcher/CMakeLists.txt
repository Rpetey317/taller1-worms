cmake_minimum_required(VERSION 3.10)

project(qtLauncher)

set(CMAKE_CXX_STANDARD 17)

# Find the QtWidgets library
find_package(Qt5Widgets COMPONENTS Widgets REQUIRED)

# Esta macro toma cada uno los parámetros y ejecuta *uic* sobre ellos
# La aplicacion uic genera headers con la definición de los widgets
# a partir de un archivo .ui
# Los nombres de los headers generados se guardan en la variable pasada
# como primer parámetro.
# No, no los genera con la carpeta como prefijo.
qt5_wrap_ui(UIS_HEADERS
        Forms/super_duper_tuki.ui
        Forms/crear_partida_nueva.ui
        Forms/unirse_a_partida.ui
)

set(SOURCES
  Sources/Greeter.cpp
  Sources/main.cpp
  Sources/CreateGame.cpp
  Sources/JoinGame.cpp)

add_executable(qtLauncher
  ${SOURCES}
  ${UIS_HEADERS})

# Use the Widgets module from Qt 5.
target_link_libraries(qtLauncher Qt5::Widgets)
