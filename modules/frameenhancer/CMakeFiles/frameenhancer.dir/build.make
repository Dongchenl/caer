# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/dongchen/Documents/caer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dongchen/Documents/caer

# Include any dependencies generated for this target.
include modules/frameenhancer/CMakeFiles/frameenhancer.dir/depend.make

# Include the progress variables for this target.
include modules/frameenhancer/CMakeFiles/frameenhancer.dir/progress.make

# Include the compile flags for this target's objects.
include modules/frameenhancer/CMakeFiles/frameenhancer.dir/flags.make

modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.o: modules/frameenhancer/CMakeFiles/frameenhancer.dir/flags.make
modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.o: modules/frameenhancer/frameenhancer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dongchen/Documents/caer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.o"
	cd /home/dongchen/Documents/caer/modules/frameenhancer && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/frameenhancer.dir/frameenhancer.c.o   -c /home/dongchen/Documents/caer/modules/frameenhancer/frameenhancer.c

modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/frameenhancer.dir/frameenhancer.c.i"
	cd /home/dongchen/Documents/caer/modules/frameenhancer && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dongchen/Documents/caer/modules/frameenhancer/frameenhancer.c > CMakeFiles/frameenhancer.dir/frameenhancer.c.i

modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/frameenhancer.dir/frameenhancer.c.s"
	cd /home/dongchen/Documents/caer/modules/frameenhancer && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dongchen/Documents/caer/modules/frameenhancer/frameenhancer.c -o CMakeFiles/frameenhancer.dir/frameenhancer.c.s

modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.o.requires:

.PHONY : modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.o.requires

modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.o.provides: modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.o.requires
	$(MAKE) -f modules/frameenhancer/CMakeFiles/frameenhancer.dir/build.make modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.o.provides.build
.PHONY : modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.o.provides

modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.o.provides.build: modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.o


# Object files for target frameenhancer
frameenhancer_OBJECTS = \
"CMakeFiles/frameenhancer.dir/frameenhancer.c.o"

# External object files for target frameenhancer
frameenhancer_EXTERNAL_OBJECTS =

modules/frameenhancer/caer_frameenhancer.so: modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.o
modules/frameenhancer/caer_frameenhancer.so: modules/frameenhancer/CMakeFiles/frameenhancer.dir/build.make
modules/frameenhancer/caer_frameenhancer.so: modules/frameenhancer/CMakeFiles/frameenhancer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dongchen/Documents/caer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library caer_frameenhancer.so"
	cd /home/dongchen/Documents/caer/modules/frameenhancer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/frameenhancer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
modules/frameenhancer/CMakeFiles/frameenhancer.dir/build: modules/frameenhancer/caer_frameenhancer.so

.PHONY : modules/frameenhancer/CMakeFiles/frameenhancer.dir/build

modules/frameenhancer/CMakeFiles/frameenhancer.dir/requires: modules/frameenhancer/CMakeFiles/frameenhancer.dir/frameenhancer.c.o.requires

.PHONY : modules/frameenhancer/CMakeFiles/frameenhancer.dir/requires

modules/frameenhancer/CMakeFiles/frameenhancer.dir/clean:
	cd /home/dongchen/Documents/caer/modules/frameenhancer && $(CMAKE_COMMAND) -P CMakeFiles/frameenhancer.dir/cmake_clean.cmake
.PHONY : modules/frameenhancer/CMakeFiles/frameenhancer.dir/clean

modules/frameenhancer/CMakeFiles/frameenhancer.dir/depend:
	cd /home/dongchen/Documents/caer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dongchen/Documents/caer /home/dongchen/Documents/caer/modules/frameenhancer /home/dongchen/Documents/caer /home/dongchen/Documents/caer/modules/frameenhancer /home/dongchen/Documents/caer/modules/frameenhancer/CMakeFiles/frameenhancer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/frameenhancer/CMakeFiles/frameenhancer.dir/depend

