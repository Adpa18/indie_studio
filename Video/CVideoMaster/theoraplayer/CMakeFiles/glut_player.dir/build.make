# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tavern_d/Downloads/theoraplayer-1.1.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tavern_d/Downloads/theoraplayer-1.1.0

# Include any dependencies generated for this target.
include CMakeFiles/glut_player.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/glut_player.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glut_player.dir/flags.make

CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o: CMakeFiles/glut_player.dir/flags.make
CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o: demos/basecode/glut/glutBasecode.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tavern_d/Downloads/theoraplayer-1.1.0/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o -c /home/tavern_d/Downloads/theoraplayer-1.1.0/demos/basecode/glut/glutBasecode.cpp

CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tavern_d/Downloads/theoraplayer-1.1.0/demos/basecode/glut/glutBasecode.cpp > CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.i

CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tavern_d/Downloads/theoraplayer-1.1.0/demos/basecode/glut/glutBasecode.cpp -o CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.s

CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o.requires:
.PHONY : CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o.requires

CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o.provides: CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o.requires
	$(MAKE) -f CMakeFiles/glut_player.dir/build.make CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o.provides.build
.PHONY : CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o.provides

CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o.provides.build: CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o

CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o: CMakeFiles/glut_player.dir/flags.make
CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o: demos/basecode/util/util.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tavern_d/Downloads/theoraplayer-1.1.0/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o -c /home/tavern_d/Downloads/theoraplayer-1.1.0/demos/basecode/util/util.cpp

CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tavern_d/Downloads/theoraplayer-1.1.0/demos/basecode/util/util.cpp > CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.i

CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tavern_d/Downloads/theoraplayer-1.1.0/demos/basecode/util/util.cpp -o CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.s

CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o.requires:
.PHONY : CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o.requires

CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o.provides: CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o.requires
	$(MAKE) -f CMakeFiles/glut_player.dir/build.make CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o.provides.build
.PHONY : CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o.provides

CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o.provides.build: CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o

CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o: CMakeFiles/glut_player.dir/flags.make
CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o: demos/glut_player/glut_player.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tavern_d/Downloads/theoraplayer-1.1.0/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o -c /home/tavern_d/Downloads/theoraplayer-1.1.0/demos/glut_player/glut_player.cpp

CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tavern_d/Downloads/theoraplayer-1.1.0/demos/glut_player/glut_player.cpp > CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.i

CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tavern_d/Downloads/theoraplayer-1.1.0/demos/glut_player/glut_player.cpp -o CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.s

CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o.requires:
.PHONY : CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o.requires

CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o.provides: CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o.requires
	$(MAKE) -f CMakeFiles/glut_player.dir/build.make CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o.provides.build
.PHONY : CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o.provides

CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o.provides.build: CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o

# Object files for target glut_player
glut_player_OBJECTS = \
"CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o" \
"CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o" \
"CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o"

# External object files for target glut_player
glut_player_EXTERNAL_OBJECTS =

glut_player: CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o
glut_player: CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o
glut_player: CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o
glut_player: CMakeFiles/glut_player.dir/build.make
glut_player: libtheoraplayer.a
glut_player: libtheora.a
glut_player: libvorbis.a
glut_player: libogg.a
glut_player: /usr/lib64/libGLU.so
glut_player: /usr/lib64/libGL.so
glut_player: /usr/lib64/libSM.so
glut_player: /usr/lib64/libICE.so
glut_player: /usr/lib64/libX11.so
glut_player: /usr/lib64/libXext.so
glut_player: CMakeFiles/glut_player.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable glut_player"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glut_player.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glut_player.dir/build: glut_player
.PHONY : CMakeFiles/glut_player.dir/build

CMakeFiles/glut_player.dir/requires: CMakeFiles/glut_player.dir/demos/basecode/glut/glutBasecode.cpp.o.requires
CMakeFiles/glut_player.dir/requires: CMakeFiles/glut_player.dir/demos/basecode/util/util.cpp.o.requires
CMakeFiles/glut_player.dir/requires: CMakeFiles/glut_player.dir/demos/glut_player/glut_player.cpp.o.requires
.PHONY : CMakeFiles/glut_player.dir/requires

CMakeFiles/glut_player.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/glut_player.dir/cmake_clean.cmake
.PHONY : CMakeFiles/glut_player.dir/clean

CMakeFiles/glut_player.dir/depend:
	cd /home/tavern_d/Downloads/theoraplayer-1.1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tavern_d/Downloads/theoraplayer-1.1.0 /home/tavern_d/Downloads/theoraplayer-1.1.0 /home/tavern_d/Downloads/theoraplayer-1.1.0 /home/tavern_d/Downloads/theoraplayer-1.1.0 /home/tavern_d/Downloads/theoraplayer-1.1.0/CMakeFiles/glut_player.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glut_player.dir/depend
