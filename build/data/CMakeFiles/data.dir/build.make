# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/build

# Include any dependencies generated for this target.
include data/CMakeFiles/data.dir/depend.make

# Include the progress variables for this target.
include data/CMakeFiles/data.dir/progress.make

# Include the compile flags for this target's objects.
include data/CMakeFiles/data.dir/flags.make

data/CMakeFiles/data.dir/data.cpp.o: data/CMakeFiles/data.dir/flags.make
data/CMakeFiles/data.dir/data.cpp.o: /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/src/data/data.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object data/CMakeFiles/data.dir/data.cpp.o"
	cd /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/build/data && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/data.dir/data.cpp.o -c /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/src/data/data.cpp

data/CMakeFiles/data.dir/data.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/data.dir/data.cpp.i"
	cd /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/build/data && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/src/data/data.cpp > CMakeFiles/data.dir/data.cpp.i

data/CMakeFiles/data.dir/data.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/data.dir/data.cpp.s"
	cd /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/build/data && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/src/data/data.cpp -o CMakeFiles/data.dir/data.cpp.s

# Object files for target data
data_OBJECTS = \
"CMakeFiles/data.dir/data.cpp.o"

# External object files for target data
data_EXTERNAL_OBJECTS =

data/libdata.a: data/CMakeFiles/data.dir/data.cpp.o
data/libdata.a: data/CMakeFiles/data.dir/build.make
data/libdata.a: data/CMakeFiles/data.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libdata.a"
	cd /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/build/data && $(CMAKE_COMMAND) -P CMakeFiles/data.dir/cmake_clean_target.cmake
	cd /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/build/data && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/data.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
data/CMakeFiles/data.dir/build: data/libdata.a

.PHONY : data/CMakeFiles/data.dir/build

data/CMakeFiles/data.dir/clean:
	cd /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/build/data && $(CMAKE_COMMAND) -P CMakeFiles/data.dir/cmake_clean.cmake
.PHONY : data/CMakeFiles/data.dir/clean

data/CMakeFiles/data.dir/depend:
	cd /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/src /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/src/data /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/build /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/build/data /home/jwimd/Study/Computer_Network/Lab/Lab2/Socket_Computer_Network/build/data/CMakeFiles/data.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : data/CMakeFiles/data.dir/depend

