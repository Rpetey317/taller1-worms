cmake_minimum_required(VERSION 3.10)

project(Worms)

set(CMAKE_CXX_STANDARD 17)

# Flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors")
# debugging flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline ")
# threads
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


# COMMON
include_directories(${PROJECT_SOURCE_DIR}/Common) #Agrega el directiorio Common al conjunto de directorios
include_directories(${PROJECT_SOURCE_DIR}/Common/Socket)

add_subdirectory("Common") #Para buscar el archivo CMakeLists.txt en el directorio "Common"

# SERVER
include_directories(${PROJECT_SOURCE_DIR}/Server/src)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/AccepterThread)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/ClientUpdate)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/Game)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/GameLoopThread)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/GameUpdate)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/PlayerHandler)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/PlayerListMonitor)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/ReceiverThread)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/SenderThread)
include_directories(${PROJECT_SOURCE_DIR}/Server/src/ServerProtocol)

add_subdirectory("Server/src")

# CLIENT
include_directories(${PROJECT_SOURCE_DIR}/Client/src)
include_directories(${PROJECT_SOURCE_DIR}/Client/src/ServerUpdate)

add_subdirectory("Client/src")


# EJECUTABLES
add_executable(server "Server/main.cpp") #Define objeto ejecutable llamado server que se compila a partir de "Server/server_main.cpp"
target_link_libraries(server server_classes common_classes) #Establece las bibliotecas necesarias para el ejecutable server

add_executable(client "Client/main.cpp")
target_link_libraries(client client_classes common_classes)


# # Add server executable
# file(GLOB SERVER_SOURCES "server/**/*.cpp" "common/**/*.cpp")
# add_executable(server ${SERVER_SOURCES})

# # Add client executable
# file(GLOB CLIENT_SOURCES "client/**/*.cpp" "common/**/*.cpp")
# add_executable(client ${CLIENT_SOURCES})
