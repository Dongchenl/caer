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
include modules/misc/out/CMakeFiles/output_net_udp.dir/depend.make

# Include the progress variables for this target.
include modules/misc/out/CMakeFiles/output_net_udp.dir/progress.make

# Include the compile flags for this target's objects.
include modules/misc/out/CMakeFiles/output_net_udp.dir/flags.make

modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.o: modules/misc/out/CMakeFiles/output_net_udp.dir/flags.make
modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.o: modules/misc/out/output_common.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dongchen/Documents/caer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.o"
	cd /home/dongchen/Documents/caer/modules/misc/out && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/output_net_udp.dir/output_common.c.o   -c /home/dongchen/Documents/caer/modules/misc/out/output_common.c

modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/output_net_udp.dir/output_common.c.i"
	cd /home/dongchen/Documents/caer/modules/misc/out && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dongchen/Documents/caer/modules/misc/out/output_common.c > CMakeFiles/output_net_udp.dir/output_common.c.i

modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/output_net_udp.dir/output_common.c.s"
	cd /home/dongchen/Documents/caer/modules/misc/out && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dongchen/Documents/caer/modules/misc/out/output_common.c -o CMakeFiles/output_net_udp.dir/output_common.c.s

modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.o.requires:

.PHONY : modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.o.requires

modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.o.provides: modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.o.requires
	$(MAKE) -f modules/misc/out/CMakeFiles/output_net_udp.dir/build.make modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.o.provides.build
.PHONY : modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.o.provides

modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.o.provides.build: modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.o


modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.o: modules/misc/out/CMakeFiles/output_net_udp.dir/flags.make
modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.o: modules/misc/out/net_udp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dongchen/Documents/caer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.o"
	cd /home/dongchen/Documents/caer/modules/misc/out && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/output_net_udp.dir/net_udp.c.o   -c /home/dongchen/Documents/caer/modules/misc/out/net_udp.c

modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/output_net_udp.dir/net_udp.c.i"
	cd /home/dongchen/Documents/caer/modules/misc/out && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dongchen/Documents/caer/modules/misc/out/net_udp.c > CMakeFiles/output_net_udp.dir/net_udp.c.i

modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/output_net_udp.dir/net_udp.c.s"
	cd /home/dongchen/Documents/caer/modules/misc/out && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dongchen/Documents/caer/modules/misc/out/net_udp.c -o CMakeFiles/output_net_udp.dir/net_udp.c.s

modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.o.requires:

.PHONY : modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.o.requires

modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.o.provides: modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.o.requires
	$(MAKE) -f modules/misc/out/CMakeFiles/output_net_udp.dir/build.make modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.o.provides.build
.PHONY : modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.o.provides

modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.o.provides.build: modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.o


# Object files for target output_net_udp
output_net_udp_OBJECTS = \
"CMakeFiles/output_net_udp.dir/output_common.c.o" \
"CMakeFiles/output_net_udp.dir/net_udp.c.o"

# External object files for target output_net_udp
output_net_udp_EXTERNAL_OBJECTS =

modules/misc/out/caer_output_net_udp.so: modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.o
modules/misc/out/caer_output_net_udp.so: modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.o
modules/misc/out/caer_output_net_udp.so: modules/misc/out/CMakeFiles/output_net_udp.dir/build.make
modules/misc/out/caer_output_net_udp.so: modules/misc/out/CMakeFiles/output_net_udp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dongchen/Documents/caer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C shared library caer_output_net_udp.so"
	cd /home/dongchen/Documents/caer/modules/misc/out && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/output_net_udp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
modules/misc/out/CMakeFiles/output_net_udp.dir/build: modules/misc/out/caer_output_net_udp.so

.PHONY : modules/misc/out/CMakeFiles/output_net_udp.dir/build

modules/misc/out/CMakeFiles/output_net_udp.dir/requires: modules/misc/out/CMakeFiles/output_net_udp.dir/output_common.c.o.requires
modules/misc/out/CMakeFiles/output_net_udp.dir/requires: modules/misc/out/CMakeFiles/output_net_udp.dir/net_udp.c.o.requires

.PHONY : modules/misc/out/CMakeFiles/output_net_udp.dir/requires

modules/misc/out/CMakeFiles/output_net_udp.dir/clean:
	cd /home/dongchen/Documents/caer/modules/misc/out && $(CMAKE_COMMAND) -P CMakeFiles/output_net_udp.dir/cmake_clean.cmake
.PHONY : modules/misc/out/CMakeFiles/output_net_udp.dir/clean

modules/misc/out/CMakeFiles/output_net_udp.dir/depend:
	cd /home/dongchen/Documents/caer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dongchen/Documents/caer /home/dongchen/Documents/caer/modules/misc/out /home/dongchen/Documents/caer /home/dongchen/Documents/caer/modules/misc/out /home/dongchen/Documents/caer/modules/misc/out/CMakeFiles/output_net_udp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/misc/out/CMakeFiles/output_net_udp.dir/depend

