# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/win/Documents/Stupid subjects/CS162/CS162-project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/win/Documents/Stupid subjects/CS162/CS162-project/build"

# Include any dependencies generated for this target.
include Function/CMakeFiles/func.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Function/CMakeFiles/func.dir/compiler_depend.make

# Include the progress variables for this target.
include Function/CMakeFiles/func.dir/progress.make

# Include the compile flags for this target's objects.
include Function/CMakeFiles/func.dir/flags.make

Function/CMakeFiles/func.dir/login.cpp.o: Function/CMakeFiles/func.dir/flags.make
Function/CMakeFiles/func.dir/login.cpp.o: /Users/win/Documents/Stupid\ subjects/CS162/CS162-project/Function/login.cpp
Function/CMakeFiles/func.dir/login.cpp.o: Function/CMakeFiles/func.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/win/Documents/Stupid subjects/CS162/CS162-project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Function/CMakeFiles/func.dir/login.cpp.o"
	cd "/Users/win/Documents/Stupid subjects/CS162/CS162-project/build/Function" && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Function/CMakeFiles/func.dir/login.cpp.o -MF CMakeFiles/func.dir/login.cpp.o.d -o CMakeFiles/func.dir/login.cpp.o -c "/Users/win/Documents/Stupid subjects/CS162/CS162-project/Function/login.cpp"

Function/CMakeFiles/func.dir/login.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/func.dir/login.cpp.i"
	cd "/Users/win/Documents/Stupid subjects/CS162/CS162-project/build/Function" && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/win/Documents/Stupid subjects/CS162/CS162-project/Function/login.cpp" > CMakeFiles/func.dir/login.cpp.i

Function/CMakeFiles/func.dir/login.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/func.dir/login.cpp.s"
	cd "/Users/win/Documents/Stupid subjects/CS162/CS162-project/build/Function" && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/win/Documents/Stupid subjects/CS162/CS162-project/Function/login.cpp" -o CMakeFiles/func.dir/login.cpp.s

# Object files for target func
func_OBJECTS = \
"CMakeFiles/func.dir/login.cpp.o"

# External object files for target func
func_EXTERNAL_OBJECTS =

Function/libfunc.a: Function/CMakeFiles/func.dir/login.cpp.o
Function/libfunc.a: Function/CMakeFiles/func.dir/build.make
Function/libfunc.a: Function/CMakeFiles/func.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/win/Documents/Stupid subjects/CS162/CS162-project/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libfunc.a"
	cd "/Users/win/Documents/Stupid subjects/CS162/CS162-project/build/Function" && $(CMAKE_COMMAND) -P CMakeFiles/func.dir/cmake_clean_target.cmake
	cd "/Users/win/Documents/Stupid subjects/CS162/CS162-project/build/Function" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/func.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Function/CMakeFiles/func.dir/build: Function/libfunc.a
.PHONY : Function/CMakeFiles/func.dir/build

Function/CMakeFiles/func.dir/clean:
	cd "/Users/win/Documents/Stupid subjects/CS162/CS162-project/build/Function" && $(CMAKE_COMMAND) -P CMakeFiles/func.dir/cmake_clean.cmake
.PHONY : Function/CMakeFiles/func.dir/clean

Function/CMakeFiles/func.dir/depend:
	cd "/Users/win/Documents/Stupid subjects/CS162/CS162-project/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/win/Documents/Stupid subjects/CS162/CS162-project" "/Users/win/Documents/Stupid subjects/CS162/CS162-project/Function" "/Users/win/Documents/Stupid subjects/CS162/CS162-project/build" "/Users/win/Documents/Stupid subjects/CS162/CS162-project/build/Function" "/Users/win/Documents/Stupid subjects/CS162/CS162-project/build/Function/CMakeFiles/func.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : Function/CMakeFiles/func.dir/depend

