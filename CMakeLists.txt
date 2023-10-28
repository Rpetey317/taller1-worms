cmake_minimum_required(VERSION 3.10)

project(Worms)

set(CMAKE_CXX_STANDARD 11)

# Add server executable
file(GLOB SERVER_SOURCES "server/**/*.cpp" "common/**/*.cpp")
add_executable(server ${SERVER_SOURCES})

# Add client executable
file(GLOB CLIENT_SOURCES "client/**/*.cpp" "common/**/*.cpp")
add_executable(client ${CLIENT_SOURCES})
