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
CMAKE_BINARY_DIR = "/Users/win/Documents/Stupid subjects/CS162/CS162-project/out/build"

# Include any dependencies generated for this target.
include CMakeFiles/ProjectUI.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ProjectUI.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ProjectUI.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProjectUI.dir/flags.make

CMakeFiles/ProjectUI.dir/main.cpp.o: CMakeFiles/ProjectUI.dir/flags.make
CMakeFiles/ProjectUI.dir/main.cpp.o: /Users/win/Documents/Stupid\ subjects/CS162/CS162-project/main.cpp
CMakeFiles/ProjectUI.dir/main.cpp.o: CMakeFiles/ProjectUI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/win/Documents/Stupid subjects/CS162/CS162-project/out/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ProjectUI.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ProjectUI.dir/main.cpp.o -MF CMakeFiles/ProjectUI.dir/main.cpp.o.d -o CMakeFiles/ProjectUI.dir/main.cpp.o -c "/Users/win/Documents/Stupid subjects/CS162/CS162-project/main.cpp"

CMakeFiles/ProjectUI.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ProjectUI.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/win/Documents/Stupid subjects/CS162/CS162-project/main.cpp" > CMakeFiles/ProjectUI.dir/main.cpp.i

CMakeFiles/ProjectUI.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ProjectUI.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/win/Documents/Stupid subjects/CS162/CS162-project/main.cpp" -o CMakeFiles/ProjectUI.dir/main.cpp.s

# Object files for target ProjectUI
ProjectUI_OBJECTS = \
"CMakeFiles/ProjectUI.dir/main.cpp.o"

# External object files for target ProjectUI
ProjectUI_EXTERNAL_OBJECTS =

ProjectUI: CMakeFiles/ProjectUI.dir/main.cpp.o
ProjectUI: CMakeFiles/ProjectUI.dir/build.make
ProjectUI: external/raylib/raylib/libraylib.a
ProjectUI: Function/libfunc.a
ProjectUI: UI/libui.a
ProjectUI: external/raylib/raylib/external/glfw/src/libglfw3.a
ProjectUI: CMakeFiles/ProjectUI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/win/Documents/Stupid subjects/CS162/CS162-project/out/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ProjectUI"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProjectUI.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProjectUI.dir/build: ProjectUI
.PHONY : CMakeFiles/ProjectUI.dir/build

CMakeFiles/ProjectUI.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ProjectUI.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ProjectUI.dir/clean

CMakeFiles/ProjectUI.dir/depend:
	cd "/Users/win/Documents/Stupid subjects/CS162/CS162-project/out/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/win/Documents/Stupid subjects/CS162/CS162-project" "/Users/win/Documents/Stupid subjects/CS162/CS162-project" "/Users/win/Documents/Stupid subjects/CS162/CS162-project/out/build" "/Users/win/Documents/Stupid subjects/CS162/CS162-project/out/build" "/Users/win/Documents/Stupid subjects/CS162/CS162-project/out/build/CMakeFiles/ProjectUI.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/ProjectUI.dir/depend

