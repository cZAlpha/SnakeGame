# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/x64/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nbklaus21/CLionProjects/SnakeGame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nbklaus21/CLionProjects/SnakeGame/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Snake.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Snake.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Snake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Snake.dir/flags.make

CMakeFiles/Snake.dir/main.cpp.o: CMakeFiles/Snake.dir/flags.make
CMakeFiles/Snake.dir/main.cpp.o: /Users/nbklaus21/CLionProjects/SnakeGame/main.cpp
CMakeFiles/Snake.dir/main.cpp.o: CMakeFiles/Snake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nbklaus21/CLionProjects/SnakeGame/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Snake.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Snake.dir/main.cpp.o -MF CMakeFiles/Snake.dir/main.cpp.o.d -o CMakeFiles/Snake.dir/main.cpp.o -c /Users/nbklaus21/CLionProjects/SnakeGame/main.cpp

CMakeFiles/Snake.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Snake.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nbklaus21/CLionProjects/SnakeGame/main.cpp > CMakeFiles/Snake.dir/main.cpp.i

CMakeFiles/Snake.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Snake.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nbklaus21/CLionProjects/SnakeGame/main.cpp -o CMakeFiles/Snake.dir/main.cpp.s

# Object files for target Snake
Snake_OBJECTS = \
"CMakeFiles/Snake.dir/main.cpp.o"

# External object files for target Snake
Snake_EXTERNAL_OBJECTS =

Snake: CMakeFiles/Snake.dir/main.cpp.o
Snake: CMakeFiles/Snake.dir/build.make
Snake: CMakeFiles/Snake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/nbklaus21/CLionProjects/SnakeGame/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Snake"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Snake.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Snake.dir/build: Snake
.PHONY : CMakeFiles/Snake.dir/build

CMakeFiles/Snake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Snake.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Snake.dir/clean

CMakeFiles/Snake.dir/depend:
	cd /Users/nbklaus21/CLionProjects/SnakeGame/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nbklaus21/CLionProjects/SnakeGame /Users/nbklaus21/CLionProjects/SnakeGame /Users/nbklaus21/CLionProjects/SnakeGame/cmake-build-debug /Users/nbklaus21/CLionProjects/SnakeGame/cmake-build-debug /Users/nbklaus21/CLionProjects/SnakeGame/cmake-build-debug/CMakeFiles/Snake.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Snake.dir/depend
