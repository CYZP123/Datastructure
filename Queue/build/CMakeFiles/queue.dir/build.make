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
CMAKE_SOURCE_DIR = /home/cyzp/DataStructure/Queue

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cyzp/DataStructure/Queue/build

# Include any dependencies generated for this target.
include CMakeFiles/queue.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/queue.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/queue.dir/flags.make

CMakeFiles/queue.dir/Queue_test.cc.o: CMakeFiles/queue.dir/flags.make
CMakeFiles/queue.dir/Queue_test.cc.o: ../Queue_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyzp/DataStructure/Queue/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/queue.dir/Queue_test.cc.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/queue.dir/Queue_test.cc.o -c /home/cyzp/DataStructure/Queue/Queue_test.cc

CMakeFiles/queue.dir/Queue_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/queue.dir/Queue_test.cc.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyzp/DataStructure/Queue/Queue_test.cc > CMakeFiles/queue.dir/Queue_test.cc.i

CMakeFiles/queue.dir/Queue_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/queue.dir/Queue_test.cc.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyzp/DataStructure/Queue/Queue_test.cc -o CMakeFiles/queue.dir/Queue_test.cc.s

# Object files for target queue
queue_OBJECTS = \
"CMakeFiles/queue.dir/Queue_test.cc.o"

# External object files for target queue
queue_EXTERNAL_OBJECTS =

queue: CMakeFiles/queue.dir/Queue_test.cc.o
queue: CMakeFiles/queue.dir/build.make
queue: CMakeFiles/queue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cyzp/DataStructure/Queue/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable queue"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/queue.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/queue.dir/build: queue

.PHONY : CMakeFiles/queue.dir/build

CMakeFiles/queue.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/queue.dir/cmake_clean.cmake
.PHONY : CMakeFiles/queue.dir/clean

CMakeFiles/queue.dir/depend:
	cd /home/cyzp/DataStructure/Queue/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cyzp/DataStructure/Queue /home/cyzp/DataStructure/Queue /home/cyzp/DataStructure/Queue/build /home/cyzp/DataStructure/Queue/build /home/cyzp/DataStructure/Queue/build/CMakeFiles/queue.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/queue.dir/depend

