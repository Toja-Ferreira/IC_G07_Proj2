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
CMAKE_SOURCE_DIR = /home/luis/Desktop/IC_G07_Proj2/Part_III

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luis/Desktop/IC_G07_Proj2/Part_III

# Include any dependencies generated for this target.
include CMakeFiles/testEncoding.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testEncoding.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testEncoding.dir/flags.make

CMakeFiles/testEncoding.dir/test_programs/testEncoding.cpp.o: CMakeFiles/testEncoding.dir/flags.make
CMakeFiles/testEncoding.dir/test_programs/testEncoding.cpp.o: test_programs/testEncoding.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luis/Desktop/IC_G07_Proj2/Part_III/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testEncoding.dir/test_programs/testEncoding.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testEncoding.dir/test_programs/testEncoding.cpp.o -c /home/luis/Desktop/IC_G07_Proj2/Part_III/test_programs/testEncoding.cpp

CMakeFiles/testEncoding.dir/test_programs/testEncoding.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testEncoding.dir/test_programs/testEncoding.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luis/Desktop/IC_G07_Proj2/Part_III/test_programs/testEncoding.cpp > CMakeFiles/testEncoding.dir/test_programs/testEncoding.cpp.i

CMakeFiles/testEncoding.dir/test_programs/testEncoding.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testEncoding.dir/test_programs/testEncoding.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luis/Desktop/IC_G07_Proj2/Part_III/test_programs/testEncoding.cpp -o CMakeFiles/testEncoding.dir/test_programs/testEncoding.cpp.s

# Object files for target testEncoding
testEncoding_OBJECTS = \
"CMakeFiles/testEncoding.dir/test_programs/testEncoding.cpp.o"

# External object files for target testEncoding
testEncoding_EXTERNAL_OBJECTS =

test_programs/testEncoding: CMakeFiles/testEncoding.dir/test_programs/testEncoding.cpp.o
test_programs/testEncoding: CMakeFiles/testEncoding.dir/build.make
test_programs/testEncoding: CMakeFiles/testEncoding.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luis/Desktop/IC_G07_Proj2/Part_III/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_programs/testEncoding"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testEncoding.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testEncoding.dir/build: test_programs/testEncoding

.PHONY : CMakeFiles/testEncoding.dir/build

CMakeFiles/testEncoding.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testEncoding.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testEncoding.dir/clean

CMakeFiles/testEncoding.dir/depend:
	cd /home/luis/Desktop/IC_G07_Proj2/Part_III && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luis/Desktop/IC_G07_Proj2/Part_III /home/luis/Desktop/IC_G07_Proj2/Part_III /home/luis/Desktop/IC_G07_Proj2/Part_III /home/luis/Desktop/IC_G07_Proj2/Part_III /home/luis/Desktop/IC_G07_Proj2/Part_III/CMakeFiles/testEncoding.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testEncoding.dir/depend

