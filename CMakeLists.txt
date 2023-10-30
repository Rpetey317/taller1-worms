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
include_directories(${PROJECT_SOURCE_DIR}/Server)
include_directories(${PROJECT_SOURCE_DIR}/Server/AccepterThread)
include_directories(${PROJECT_SOURCE_DIR}/Server/ClientUpdate)
include_directories(${PROJECT_SOURCE_DIR}/Server/Game)
include_directories(${PROJECT_SOURCE_DIR}/Server/GameLoopThread)
include_directories(${PROJECT_SOURCE_DIR}/Server/GameUpdate)
include_directories(${PROJECT_SOURCE_DIR}/Server/PlayerHandler)
include_directories(${PROJECT_SOURCE_DIR}/Server/PlayerListMonitor)
include_directories(${PROJECT_SOURCE_DIR}/Server/ReceiverThread)
include_directories(${PROJECT_SOURCE_DIR}/Server/SenderThread)
include_directories(${PROJECT_SOURCE_DIR}/Server/ServerProtocol)

add_subdirectory("Server")

# CLIENT
include_directories(${PROJECT_SOURCE_DIR}/Client)
include_directories(${PROJECT_SOURCE_DIR}/Client/ServerUpdate)

add_subdirectory("Client")


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
