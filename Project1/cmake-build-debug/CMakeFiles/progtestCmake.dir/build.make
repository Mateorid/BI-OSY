# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /mnt/c/CVUT/BI-OSY/progtest_solver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/CVUT/BI-OSY/progtest_solver/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/progtestCmake.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/progtestCmake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/progtestCmake.dir/flags.make

CMakeFiles/progtestCmake.dir/sample_tester.cpp.o: CMakeFiles/progtestCmake.dir/flags.make
CMakeFiles/progtestCmake.dir/sample_tester.cpp.o: ../sample_tester.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/CVUT/BI-OSY/progtest_solver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/progtestCmake.dir/sample_tester.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/progtestCmake.dir/sample_tester.cpp.o -c /mnt/c/CVUT/BI-OSY/progtest_solver/sample_tester.cpp

CMakeFiles/progtestCmake.dir/sample_tester.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/progtestCmake.dir/sample_tester.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/CVUT/BI-OSY/progtest_solver/sample_tester.cpp > CMakeFiles/progtestCmake.dir/sample_tester.cpp.i

CMakeFiles/progtestCmake.dir/sample_tester.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/progtestCmake.dir/sample_tester.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/CVUT/BI-OSY/progtest_solver/sample_tester.cpp -o CMakeFiles/progtestCmake.dir/sample_tester.cpp.s

CMakeFiles/progtestCmake.dir/sample_tester.cpp.o.requires:

.PHONY : CMakeFiles/progtestCmake.dir/sample_tester.cpp.o.requires

CMakeFiles/progtestCmake.dir/sample_tester.cpp.o.provides: CMakeFiles/progtestCmake.dir/sample_tester.cpp.o.requires
	$(MAKE) -f CMakeFiles/progtestCmake.dir/build.make CMakeFiles/progtestCmake.dir/sample_tester.cpp.o.provides.build
.PHONY : CMakeFiles/progtestCmake.dir/sample_tester.cpp.o.provides

CMakeFiles/progtestCmake.dir/sample_tester.cpp.o.provides.build: CMakeFiles/progtestCmake.dir/sample_tester.cpp.o


CMakeFiles/progtestCmake.dir/solution.cpp.o: CMakeFiles/progtestCmake.dir/flags.make
CMakeFiles/progtestCmake.dir/solution.cpp.o: ../solution.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/CVUT/BI-OSY/progtest_solver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/progtestCmake.dir/solution.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/progtestCmake.dir/solution.cpp.o -c /mnt/c/CVUT/BI-OSY/progtest_solver/solution.cpp

CMakeFiles/progtestCmake.dir/solution.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/progtestCmake.dir/solution.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/CVUT/BI-OSY/progtest_solver/solution.cpp > CMakeFiles/progtestCmake.dir/solution.cpp.i

CMakeFiles/progtestCmake.dir/solution.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/progtestCmake.dir/solution.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/CVUT/BI-OSY/progtest_solver/solution.cpp -o CMakeFiles/progtestCmake.dir/solution.cpp.s

CMakeFiles/progtestCmake.dir/solution.cpp.o.requires:

.PHONY : CMakeFiles/progtestCmake.dir/solution.cpp.o.requires

CMakeFiles/progtestCmake.dir/solution.cpp.o.provides: CMakeFiles/progtestCmake.dir/solution.cpp.o.requires
	$(MAKE) -f CMakeFiles/progtestCmake.dir/build.make CMakeFiles/progtestCmake.dir/solution.cpp.o.provides.build
.PHONY : CMakeFiles/progtestCmake.dir/solution.cpp.o.provides

CMakeFiles/progtestCmake.dir/solution.cpp.o.provides.build: CMakeFiles/progtestCmake.dir/solution.cpp.o


# Object files for target progtestCmake
progtestCmake_OBJECTS = \
"CMakeFiles/progtestCmake.dir/sample_tester.cpp.o" \
"CMakeFiles/progtestCmake.dir/solution.cpp.o"

# External object files for target progtestCmake
progtestCmake_EXTERNAL_OBJECTS =

progtestCmake: CMakeFiles/progtestCmake.dir/sample_tester.cpp.o
progtestCmake: CMakeFiles/progtestCmake.dir/solution.cpp.o
progtestCmake: CMakeFiles/progtestCmake.dir/build.make
progtestCmake: ../x86_64-linux-gnu/libprogtest_solver.a
progtestCmake: CMakeFiles/progtestCmake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/CVUT/BI-OSY/progtest_solver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable progtestCmake"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/progtestCmake.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/progtestCmake.dir/build: progtestCmake

.PHONY : CMakeFiles/progtestCmake.dir/build

CMakeFiles/progtestCmake.dir/requires: CMakeFiles/progtestCmake.dir/sample_tester.cpp.o.requires
CMakeFiles/progtestCmake.dir/requires: CMakeFiles/progtestCmake.dir/solution.cpp.o.requires

.PHONY : CMakeFiles/progtestCmake.dir/requires

CMakeFiles/progtestCmake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/progtestCmake.dir/cmake_clean.cmake
.PHONY : CMakeFiles/progtestCmake.dir/clean

CMakeFiles/progtestCmake.dir/depend:
	cd /mnt/c/CVUT/BI-OSY/progtest_solver/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/CVUT/BI-OSY/progtest_solver /mnt/c/CVUT/BI-OSY/progtest_solver /mnt/c/CVUT/BI-OSY/progtest_solver/cmake-build-debug /mnt/c/CVUT/BI-OSY/progtest_solver/cmake-build-debug /mnt/c/CVUT/BI-OSY/progtest_solver/cmake-build-debug/CMakeFiles/progtestCmake.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/progtestCmake.dir/depend

