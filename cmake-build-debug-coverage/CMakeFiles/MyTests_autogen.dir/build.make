# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/liuming/CLionProjects/Word_Chain1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/liuming/CLionProjects/Word_Chain1/cmake-build-debug-coverage

# Utility rule file for MyTests_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/MyTests_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyTests_autogen.dir/progress.make

CMakeFiles/MyTests_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/liuming/CLionProjects/Word_Chain1/cmake-build-debug-coverage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target MyTests"
	/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E cmake_autogen /Users/liuming/CLionProjects/Word_Chain1/cmake-build-debug-coverage/CMakeFiles/MyTests_autogen.dir/AutogenInfo.json Debug

MyTests_autogen: CMakeFiles/MyTests_autogen
MyTests_autogen: CMakeFiles/MyTests_autogen.dir/build.make
.PHONY : MyTests_autogen

# Rule to build all files generated by this target.
CMakeFiles/MyTests_autogen.dir/build: MyTests_autogen
.PHONY : CMakeFiles/MyTests_autogen.dir/build

CMakeFiles/MyTests_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyTests_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyTests_autogen.dir/clean

CMakeFiles/MyTests_autogen.dir/depend:
	cd /Users/liuming/CLionProjects/Word_Chain1/cmake-build-debug-coverage && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/liuming/CLionProjects/Word_Chain1 /Users/liuming/CLionProjects/Word_Chain1 /Users/liuming/CLionProjects/Word_Chain1/cmake-build-debug-coverage /Users/liuming/CLionProjects/Word_Chain1/cmake-build-debug-coverage /Users/liuming/CLionProjects/Word_Chain1/cmake-build-debug-coverage/CMakeFiles/MyTests_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyTests_autogen.dir/depend

