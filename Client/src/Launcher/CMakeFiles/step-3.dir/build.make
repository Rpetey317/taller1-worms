# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher

# Include any dependencies generated for this target.
include CMakeFiles/step-3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/step-3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/step-3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/step-3.dir/flags.make

ui_super_duper_tuki.h: ui/super_duper_tuki.ui
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating ui_super_duper_tuki.h"
	/usr/lib/qt5/bin/uic -o /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/ui_super_duper_tuki.h /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/ui/super_duper_tuki.ui

ui_crear_partida_nueva.h: ui/crear_partida_nueva.ui
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating ui_crear_partida_nueva.h"
	/usr/lib/qt5/bin/uic -o /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/ui_crear_partida_nueva.h /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/ui/crear_partida_nueva.ui

ui_unirse_a_partida.h: ui/unirse_a_partida.ui
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating ui_unirse_a_partida.h"
	/usr/lib/qt5/bin/uic -o /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/ui_unirse_a_partida.h /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/ui/unirse_a_partida.ui

CMakeFiles/step-3.dir/Greeter.o: CMakeFiles/step-3.dir/flags.make
CMakeFiles/step-3.dir/Greeter.o: Greeter.cpp
CMakeFiles/step-3.dir/Greeter.o: CMakeFiles/step-3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/step-3.dir/Greeter.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/step-3.dir/Greeter.o -MF CMakeFiles/step-3.dir/Greeter.o.d -o CMakeFiles/step-3.dir/Greeter.o -c /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/Greeter.cpp

CMakeFiles/step-3.dir/Greeter.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/step-3.dir/Greeter.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/Greeter.cpp > CMakeFiles/step-3.dir/Greeter.i

CMakeFiles/step-3.dir/Greeter.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/step-3.dir/Greeter.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/Greeter.cpp -o CMakeFiles/step-3.dir/Greeter.s

CMakeFiles/step-3.dir/main.o: CMakeFiles/step-3.dir/flags.make
CMakeFiles/step-3.dir/main.o: main.cpp
CMakeFiles/step-3.dir/main.o: CMakeFiles/step-3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/step-3.dir/main.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/step-3.dir/main.o -MF CMakeFiles/step-3.dir/main.o.d -o CMakeFiles/step-3.dir/main.o -c /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/main.cpp

CMakeFiles/step-3.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/step-3.dir/main.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/main.cpp > CMakeFiles/step-3.dir/main.i

CMakeFiles/step-3.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/step-3.dir/main.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/main.cpp -o CMakeFiles/step-3.dir/main.s

CMakeFiles/step-3.dir/CreateGame.o: CMakeFiles/step-3.dir/flags.make
CMakeFiles/step-3.dir/CreateGame.o: CreateGame.cpp
CMakeFiles/step-3.dir/CreateGame.o: CMakeFiles/step-3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/step-3.dir/CreateGame.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/step-3.dir/CreateGame.o -MF CMakeFiles/step-3.dir/CreateGame.o.d -o CMakeFiles/step-3.dir/CreateGame.o -c /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/CreateGame.cpp

CMakeFiles/step-3.dir/CreateGame.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/step-3.dir/CreateGame.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/CreateGame.cpp > CMakeFiles/step-3.dir/CreateGame.i

CMakeFiles/step-3.dir/CreateGame.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/step-3.dir/CreateGame.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/CreateGame.cpp -o CMakeFiles/step-3.dir/CreateGame.s

CMakeFiles/step-3.dir/JoinGame.o: CMakeFiles/step-3.dir/flags.make
CMakeFiles/step-3.dir/JoinGame.o: JoinGame.cpp
CMakeFiles/step-3.dir/JoinGame.o: CMakeFiles/step-3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/step-3.dir/JoinGame.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/step-3.dir/JoinGame.o -MF CMakeFiles/step-3.dir/JoinGame.o.d -o CMakeFiles/step-3.dir/JoinGame.o -c /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/JoinGame.cpp

CMakeFiles/step-3.dir/JoinGame.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/step-3.dir/JoinGame.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/JoinGame.cpp > CMakeFiles/step-3.dir/JoinGame.i

CMakeFiles/step-3.dir/JoinGame.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/step-3.dir/JoinGame.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/JoinGame.cpp -o CMakeFiles/step-3.dir/JoinGame.s

# Object files for target step-3
step__3_OBJECTS = \
"CMakeFiles/step-3.dir/Greeter.o" \
"CMakeFiles/step-3.dir/main.o" \
"CMakeFiles/step-3.dir/CreateGame.o" \
"CMakeFiles/step-3.dir/JoinGame.o"

# External object files for target step-3
step__3_EXTERNAL_OBJECTS =

step-3: CMakeFiles/step-3.dir/Greeter.o
step-3: CMakeFiles/step-3.dir/main.o
step-3: CMakeFiles/step-3.dir/CreateGame.o
step-3: CMakeFiles/step-3.dir/JoinGame.o
step-3: CMakeFiles/step-3.dir/build.make
step-3: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
step-3: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
step-3: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
step-3: CMakeFiles/step-3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable step-3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/step-3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/step-3.dir/build: step-3
.PHONY : CMakeFiles/step-3.dir/build

CMakeFiles/step-3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/step-3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/step-3.dir/clean

CMakeFiles/step-3.dir/depend: ui_crear_partida_nueva.h
CMakeFiles/step-3.dir/depend: ui_super_duper_tuki.h
CMakeFiles/step-3.dir/depend: ui_unirse_a_partida.h
	cd /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher /home/mateolardiez/Facultad/Taller1/tpWorms/taller1-worms/Client/src/Launcher/CMakeFiles/step-3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/step-3.dir/depend

