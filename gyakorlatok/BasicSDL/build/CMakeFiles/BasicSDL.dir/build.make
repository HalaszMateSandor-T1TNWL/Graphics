# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 4.0

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
CMAKE_SOURCE_DIR = D:\Programming\OpenGL\Graphics\BasicSDL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Programming\OpenGL\Graphics\BasicSDL\build

# Include any dependencies generated for this target.
include CMakeFiles/BasicSDL.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/BasicSDL.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/BasicSDL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BasicSDL.dir/flags.make

CMakeFiles/BasicSDL.dir/codegen:
.PHONY : CMakeFiles/BasicSDL.dir/codegen

CMakeFiles/BasicSDL.dir/src/main.c.obj: CMakeFiles/BasicSDL.dir/flags.make
CMakeFiles/BasicSDL.dir/src/main.c.obj: D:/Programming/OpenGL/Graphics/BasicSDL/src/main.c
CMakeFiles/BasicSDL.dir/src/main.c.obj: CMakeFiles/BasicSDL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Programming\OpenGL\Graphics\BasicSDL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/BasicSDL.dir/src/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/BasicSDL.dir/src/main.c.obj -MF CMakeFiles\BasicSDL.dir\src\main.c.obj.d -o CMakeFiles\BasicSDL.dir\src\main.c.obj -c D:\Programming\OpenGL\Graphics\BasicSDL\src\main.c

CMakeFiles/BasicSDL.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/BasicSDL.dir/src/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Programming\OpenGL\Graphics\BasicSDL\src\main.c > CMakeFiles\BasicSDL.dir\src\main.c.i

CMakeFiles/BasicSDL.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/BasicSDL.dir/src/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Programming\OpenGL\Graphics\BasicSDL\src\main.c -o CMakeFiles\BasicSDL.dir\src\main.c.s

# Object files for target BasicSDL
BasicSDL_OBJECTS = \
"CMakeFiles/BasicSDL.dir/src/main.c.obj"

# External object files for target BasicSDL
BasicSDL_EXTERNAL_OBJECTS =

BasicSDL.exe: CMakeFiles/BasicSDL.dir/src/main.c.obj
BasicSDL.exe: CMakeFiles/BasicSDL.dir/build.make
BasicSDL.exe: CMakeFiles/BasicSDL.dir/linkLibs.rsp
BasicSDL.exe: CMakeFiles/BasicSDL.dir/objects1.rsp
BasicSDL.exe: CMakeFiles/BasicSDL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Programming\OpenGL\Graphics\BasicSDL\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable BasicSDL.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\BasicSDL.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BasicSDL.dir/build: BasicSDL.exe
.PHONY : CMakeFiles/BasicSDL.dir/build

CMakeFiles/BasicSDL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\BasicSDL.dir\cmake_clean.cmake
.PHONY : CMakeFiles/BasicSDL.dir/clean

CMakeFiles/BasicSDL.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Programming\OpenGL\Graphics\BasicSDL D:\Programming\OpenGL\Graphics\BasicSDL D:\Programming\OpenGL\Graphics\BasicSDL\build D:\Programming\OpenGL\Graphics\BasicSDL\build D:\Programming\OpenGL\Graphics\BasicSDL\build\CMakeFiles\BasicSDL.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/BasicSDL.dir/depend

