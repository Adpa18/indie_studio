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
include CMakeFiles/ogg.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ogg.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ogg.dir/flags.make

CMakeFiles/ogg.dir/ogg/src/framing.c.o: CMakeFiles/ogg.dir/flags.make
CMakeFiles/ogg.dir/ogg/src/framing.c.o: ogg/src/framing.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tavern_d/Downloads/theoraplayer-1.1.0/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/ogg.dir/ogg/src/framing.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ogg.dir/ogg/src/framing.c.o   -c /home/tavern_d/Downloads/theoraplayer-1.1.0/ogg/src/framing.c

CMakeFiles/ogg.dir/ogg/src/framing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ogg.dir/ogg/src/framing.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/tavern_d/Downloads/theoraplayer-1.1.0/ogg/src/framing.c > CMakeFiles/ogg.dir/ogg/src/framing.c.i

CMakeFiles/ogg.dir/ogg/src/framing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ogg.dir/ogg/src/framing.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/tavern_d/Downloads/theoraplayer-1.1.0/ogg/src/framing.c -o CMakeFiles/ogg.dir/ogg/src/framing.c.s

CMakeFiles/ogg.dir/ogg/src/framing.c.o.requires:
.PHONY : CMakeFiles/ogg.dir/ogg/src/framing.c.o.requires

CMakeFiles/ogg.dir/ogg/src/framing.c.o.provides: CMakeFiles/ogg.dir/ogg/src/framing.c.o.requires
	$(MAKE) -f CMakeFiles/ogg.dir/build.make CMakeFiles/ogg.dir/ogg/src/framing.c.o.provides.build
.PHONY : CMakeFiles/ogg.dir/ogg/src/framing.c.o.provides

CMakeFiles/ogg.dir/ogg/src/framing.c.o.provides.build: CMakeFiles/ogg.dir/ogg/src/framing.c.o

CMakeFiles/ogg.dir/ogg/src/bitwise.c.o: CMakeFiles/ogg.dir/flags.make
CMakeFiles/ogg.dir/ogg/src/bitwise.c.o: ogg/src/bitwise.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tavern_d/Downloads/theoraplayer-1.1.0/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/ogg.dir/ogg/src/bitwise.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ogg.dir/ogg/src/bitwise.c.o   -c /home/tavern_d/Downloads/theoraplayer-1.1.0/ogg/src/bitwise.c

CMakeFiles/ogg.dir/ogg/src/bitwise.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ogg.dir/ogg/src/bitwise.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/tavern_d/Downloads/theoraplayer-1.1.0/ogg/src/bitwise.c > CMakeFiles/ogg.dir/ogg/src/bitwise.c.i

CMakeFiles/ogg.dir/ogg/src/bitwise.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ogg.dir/ogg/src/bitwise.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/tavern_d/Downloads/theoraplayer-1.1.0/ogg/src/bitwise.c -o CMakeFiles/ogg.dir/ogg/src/bitwise.c.s

CMakeFiles/ogg.dir/ogg/src/bitwise.c.o.requires:
.PHONY : CMakeFiles/ogg.dir/ogg/src/bitwise.c.o.requires

CMakeFiles/ogg.dir/ogg/src/bitwise.c.o.provides: CMakeFiles/ogg.dir/ogg/src/bitwise.c.o.requires
	$(MAKE) -f CMakeFiles/ogg.dir/build.make CMakeFiles/ogg.dir/ogg/src/bitwise.c.o.provides.build
.PHONY : CMakeFiles/ogg.dir/ogg/src/bitwise.c.o.provides

CMakeFiles/ogg.dir/ogg/src/bitwise.c.o.provides.build: CMakeFiles/ogg.dir/ogg/src/bitwise.c.o

# Object files for target ogg
ogg_OBJECTS = \
"CMakeFiles/ogg.dir/ogg/src/framing.c.o" \
"CMakeFiles/ogg.dir/ogg/src/bitwise.c.o"

# External object files for target ogg
ogg_EXTERNAL_OBJECTS =

libogg.a: CMakeFiles/ogg.dir/ogg/src/framing.c.o
libogg.a: CMakeFiles/ogg.dir/ogg/src/bitwise.c.o
libogg.a: CMakeFiles/ogg.dir/build.make
libogg.a: CMakeFiles/ogg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library libogg.a"
	$(CMAKE_COMMAND) -P CMakeFiles/ogg.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ogg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ogg.dir/build: libogg.a
.PHONY : CMakeFiles/ogg.dir/build

CMakeFiles/ogg.dir/requires: CMakeFiles/ogg.dir/ogg/src/framing.c.o.requires
CMakeFiles/ogg.dir/requires: CMakeFiles/ogg.dir/ogg/src/bitwise.c.o.requires
.PHONY : CMakeFiles/ogg.dir/requires

CMakeFiles/ogg.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ogg.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ogg.dir/clean

CMakeFiles/ogg.dir/depend:
	cd /home/tavern_d/Downloads/theoraplayer-1.1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tavern_d/Downloads/theoraplayer-1.1.0 /home/tavern_d/Downloads/theoraplayer-1.1.0 /home/tavern_d/Downloads/theoraplayer-1.1.0 /home/tavern_d/Downloads/theoraplayer-1.1.0 /home/tavern_d/Downloads/theoraplayer-1.1.0/CMakeFiles/ogg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ogg.dir/depend
