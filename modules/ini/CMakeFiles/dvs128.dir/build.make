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
include modules/ini/CMakeFiles/dvs128.dir/depend.make

# Include the progress variables for this target.
include modules/ini/CMakeFiles/dvs128.dir/progress.make

# Include the compile flags for this target's objects.
include modules/ini/CMakeFiles/dvs128.dir/flags.make

modules/ini/CMakeFiles/dvs128.dir/dvs128.c.o: modules/ini/CMakeFiles/dvs128.dir/flags.make
modules/ini/CMakeFiles/dvs128.dir/dvs128.c.o: modules/ini/dvs128.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dongchen/Documents/caer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object modules/ini/CMakeFiles/dvs128.dir/dvs128.c.o"
	cd /home/dongchen/Documents/caer/modules/ini && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dvs128.dir/dvs128.c.o   -c /home/dongchen/Documents/caer/modules/ini/dvs128.c

modules/ini/CMakeFiles/dvs128.dir/dvs128.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dvs128.dir/dvs128.c.i"
	cd /home/dongchen/Documents/caer/modules/ini && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dongchen/Documents/caer/modules/ini/dvs128.c > CMakeFiles/dvs128.dir/dvs128.c.i

modules/ini/CMakeFiles/dvs128.dir/dvs128.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dvs128.dir/dvs128.c.s"
	cd /home/dongchen/Documents/caer/modules/ini && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dongchen/Documents/caer/modules/ini/dvs128.c -o CMakeFiles/dvs128.dir/dvs128.c.s

modules/ini/CMakeFiles/dvs128.dir/dvs128.c.o.requires:

.PHONY : modules/ini/CMakeFiles/dvs128.dir/dvs128.c.o.requires

modules/ini/CMakeFiles/dvs128.dir/dvs128.c.o.provides: modules/ini/CMakeFiles/dvs128.dir/dvs128.c.o.requires
	$(MAKE) -f modules/ini/CMakeFiles/dvs128.dir/build.make modules/ini/CMakeFiles/dvs128.dir/dvs128.c.o.provides.build
.PHONY : modules/ini/CMakeFiles/dvs128.dir/dvs128.c.o.provides

modules/ini/CMakeFiles/dvs128.dir/dvs128.c.o.provides.build: modules/ini/CMakeFiles/dvs128.dir/dvs128.c.o


# Object files for target dvs128
dvs128_OBJECTS = \
"CMakeFiles/dvs128.dir/dvs128.c.o"

# External object files for target dvs128
dvs128_EXTERNAL_OBJECTS =

modules/ini/caer_dvs128.so: modules/ini/CMakeFiles/dvs128.dir/dvs128.c.o
modules/ini/caer_dvs128.so: modules/ini/CMakeFiles/dvs128.dir/build.make
modules/ini/caer_dvs128.so: modules/ini/CMakeFiles/dvs128.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dongchen/Documents/caer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library caer_dvs128.so"
	cd /home/dongchen/Documents/caer/modules/ini && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dvs128.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
modules/ini/CMakeFiles/dvs128.dir/build: modules/ini/caer_dvs128.so

.PHONY : modules/ini/CMakeFiles/dvs128.dir/build

modules/ini/CMakeFiles/dvs128.dir/requires: modules/ini/CMakeFiles/dvs128.dir/dvs128.c.o.requires

.PHONY : modules/ini/CMakeFiles/dvs128.dir/requires

modules/ini/CMakeFiles/dvs128.dir/clean:
	cd /home/dongchen/Documents/caer/modules/ini && $(CMAKE_COMMAND) -P CMakeFiles/dvs128.dir/cmake_clean.cmake
.PHONY : modules/ini/CMakeFiles/dvs128.dir/clean

modules/ini/CMakeFiles/dvs128.dir/depend:
	cd /home/dongchen/Documents/caer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dongchen/Documents/caer /home/dongchen/Documents/caer/modules/ini /home/dongchen/Documents/caer /home/dongchen/Documents/caer/modules/ini /home/dongchen/Documents/caer/modules/ini/CMakeFiles/dvs128.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/ini/CMakeFiles/dvs128.dir/depend

