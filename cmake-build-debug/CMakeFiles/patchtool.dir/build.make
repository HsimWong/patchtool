# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/xwan/Downloads/CLion-2019.2/clion-2019.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/xwan/Downloads/CLion-2019.2/clion-2019.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xwan/Desktop/patchtool

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xwan/Desktop/patchtool/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/patchtool.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/patchtool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/patchtool.dir/flags.make

CMakeFiles/patchtool.dir/Playground.cpp.o: CMakeFiles/patchtool.dir/flags.make
CMakeFiles/patchtool.dir/Playground.cpp.o: ../Playground.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xwan/Desktop/patchtool/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/patchtool.dir/Playground.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/patchtool.dir/Playground.cpp.o -c /home/xwan/Desktop/patchtool/Playground.cpp

CMakeFiles/patchtool.dir/Playground.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/patchtool.dir/Playground.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xwan/Desktop/patchtool/Playground.cpp > CMakeFiles/patchtool.dir/Playground.cpp.i

CMakeFiles/patchtool.dir/Playground.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/patchtool.dir/Playground.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xwan/Desktop/patchtool/Playground.cpp -o CMakeFiles/patchtool.dir/Playground.cpp.s

# Object files for target patchtool
patchtool_OBJECTS = \
"CMakeFiles/patchtool.dir/Playground.cpp.o"

# External object files for target patchtool
patchtool_EXTERNAL_OBJECTS =

patchtool: CMakeFiles/patchtool.dir/Playground.cpp.o
patchtool: CMakeFiles/patchtool.dir/build.make
patchtool: CMakeFiles/patchtool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xwan/Desktop/patchtool/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable patchtool"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/patchtool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/patchtool.dir/build: patchtool

.PHONY : CMakeFiles/patchtool.dir/build

CMakeFiles/patchtool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/patchtool.dir/cmake_clean.cmake
.PHONY : CMakeFiles/patchtool.dir/clean

CMakeFiles/patchtool.dir/depend:
	cd /home/xwan/Desktop/patchtool/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xwan/Desktop/patchtool /home/xwan/Desktop/patchtool /home/xwan/Desktop/patchtool/cmake-build-debug /home/xwan/Desktop/patchtool/cmake-build-debug /home/xwan/Desktop/patchtool/cmake-build-debug/CMakeFiles/patchtool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/patchtool.dir/depend

