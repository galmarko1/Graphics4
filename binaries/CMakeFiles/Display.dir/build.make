# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.25

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\gal\Desktop\graphics4\BasicEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\gal\Desktop\graphics4\BasicEngine\binaries

# Include any dependencies generated for this target.
include CMakeFiles/Display.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Display.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Display.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Display.dir/flags.make

CMakeFiles/Display.dir/DisplayGLFW/display.cpp.obj: CMakeFiles/Display.dir/flags.make
CMakeFiles/Display.dir/DisplayGLFW/display.cpp.obj: CMakeFiles/Display.dir/includes_CXX.rsp
CMakeFiles/Display.dir/DisplayGLFW/display.cpp.obj: C:/Users/gal/Desktop/graphics4/BasicEngine/DisplayGLFW/display.cpp
CMakeFiles/Display.dir/DisplayGLFW/display.cpp.obj: CMakeFiles/Display.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\gal\Desktop\graphics4\BasicEngine\binaries\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Display.dir/DisplayGLFW/display.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Display.dir/DisplayGLFW/display.cpp.obj -MF CMakeFiles\Display.dir\DisplayGLFW\display.cpp.obj.d -o CMakeFiles\Display.dir\DisplayGLFW\display.cpp.obj -c C:\Users\gal\Desktop\graphics4\BasicEngine\DisplayGLFW\display.cpp

CMakeFiles/Display.dir/DisplayGLFW/display.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Display.dir/DisplayGLFW/display.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\gal\Desktop\graphics4\BasicEngine\DisplayGLFW\display.cpp > CMakeFiles\Display.dir\DisplayGLFW\display.cpp.i

CMakeFiles/Display.dir/DisplayGLFW/display.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Display.dir/DisplayGLFW/display.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\gal\Desktop\graphics4\BasicEngine\DisplayGLFW\display.cpp -o CMakeFiles\Display.dir\DisplayGLFW\display.cpp.s

# Object files for target Display
Display_OBJECTS = \
"CMakeFiles/Display.dir/DisplayGLFW/display.cpp.obj"

# External object files for target Display
Display_EXTERNAL_OBJECTS =

libDisplay.a: CMakeFiles/Display.dir/DisplayGLFW/display.cpp.obj
libDisplay.a: CMakeFiles/Display.dir/build.make
libDisplay.a: CMakeFiles/Display.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\gal\Desktop\graphics4\BasicEngine\binaries\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libDisplay.a"
	$(CMAKE_COMMAND) -P CMakeFiles\Display.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Display.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Display.dir/build: libDisplay.a
.PHONY : CMakeFiles/Display.dir/build

CMakeFiles/Display.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Display.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Display.dir/clean

CMakeFiles/Display.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\gal\Desktop\graphics4\BasicEngine C:\Users\gal\Desktop\graphics4\BasicEngine C:\Users\gal\Desktop\graphics4\BasicEngine\binaries C:\Users\gal\Desktop\graphics4\BasicEngine\binaries C:\Users\gal\Desktop\graphics4\BasicEngine\binaries\CMakeFiles\Display.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Display.dir/depend
