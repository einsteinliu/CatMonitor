# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_SOURCE_DIR = /home/pi/CatMonitor/CPipe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/CatMonitor/CPipe/build

# Include any dependencies generated for this target.
include CMakeFiles/cpipe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cpipe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpipe.dir/flags.make

CMakeFiles/cpipe.dir/main.cpp.o: CMakeFiles/cpipe.dir/flags.make
CMakeFiles/cpipe.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/CatMonitor/CPipe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cpipe.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cpipe.dir/main.cpp.o -c /home/pi/CatMonitor/CPipe/main.cpp

CMakeFiles/cpipe.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpipe.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/CatMonitor/CPipe/main.cpp > CMakeFiles/cpipe.dir/main.cpp.i

CMakeFiles/cpipe.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpipe.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/CatMonitor/CPipe/main.cpp -o CMakeFiles/cpipe.dir/main.cpp.s

CMakeFiles/cpipe.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/cpipe.dir/main.cpp.o.requires

CMakeFiles/cpipe.dir/main.cpp.o.provides: CMakeFiles/cpipe.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/cpipe.dir/build.make CMakeFiles/cpipe.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/cpipe.dir/main.cpp.o.provides

CMakeFiles/cpipe.dir/main.cpp.o.provides.build: CMakeFiles/cpipe.dir/main.cpp.o


# Object files for target cpipe
cpipe_OBJECTS = \
"CMakeFiles/cpipe.dir/main.cpp.o"

# External object files for target cpipe
cpipe_EXTERNAL_OBJECTS =

cpipe: CMakeFiles/cpipe.dir/main.cpp.o
cpipe: CMakeFiles/cpipe.dir/build.make
cpipe: CMakeFiles/cpipe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/CatMonitor/CPipe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cpipe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cpipe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cpipe.dir/build: cpipe

.PHONY : CMakeFiles/cpipe.dir/build

CMakeFiles/cpipe.dir/requires: CMakeFiles/cpipe.dir/main.cpp.o.requires

.PHONY : CMakeFiles/cpipe.dir/requires

CMakeFiles/cpipe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cpipe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cpipe.dir/clean

CMakeFiles/cpipe.dir/depend:
	cd /home/pi/CatMonitor/CPipe/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/CatMonitor/CPipe /home/pi/CatMonitor/CPipe /home/pi/CatMonitor/CPipe/build /home/pi/CatMonitor/CPipe/build /home/pi/CatMonitor/CPipe/build/CMakeFiles/cpipe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpipe.dir/depend
