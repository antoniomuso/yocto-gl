# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/antoniomusolino/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/173.4127.32/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/antoniomusolino/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/173.4127.32/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/antoniomusolino/Scrivania/yocto-gl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/antoniomusolino/Scrivania/yocto-gl/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/yitrace.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/yitrace.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/yitrace.dir/flags.make

CMakeFiles/yitrace.dir/apps/yitrace.cpp.o: CMakeFiles/yitrace.dir/flags.make
CMakeFiles/yitrace.dir/apps/yitrace.cpp.o: ../apps/yitrace.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/antoniomusolino/Scrivania/yocto-gl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/yitrace.dir/apps/yitrace.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/yitrace.dir/apps/yitrace.cpp.o -c /home/antoniomusolino/Scrivania/yocto-gl/apps/yitrace.cpp

CMakeFiles/yitrace.dir/apps/yitrace.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yitrace.dir/apps/yitrace.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/antoniomusolino/Scrivania/yocto-gl/apps/yitrace.cpp > CMakeFiles/yitrace.dir/apps/yitrace.cpp.i

CMakeFiles/yitrace.dir/apps/yitrace.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yitrace.dir/apps/yitrace.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/antoniomusolino/Scrivania/yocto-gl/apps/yitrace.cpp -o CMakeFiles/yitrace.dir/apps/yitrace.cpp.s

CMakeFiles/yitrace.dir/apps/yitrace.cpp.o.requires:

.PHONY : CMakeFiles/yitrace.dir/apps/yitrace.cpp.o.requires

CMakeFiles/yitrace.dir/apps/yitrace.cpp.o.provides: CMakeFiles/yitrace.dir/apps/yitrace.cpp.o.requires
	$(MAKE) -f CMakeFiles/yitrace.dir/build.make CMakeFiles/yitrace.dir/apps/yitrace.cpp.o.provides.build
.PHONY : CMakeFiles/yitrace.dir/apps/yitrace.cpp.o.provides

CMakeFiles/yitrace.dir/apps/yitrace.cpp.o.provides.build: CMakeFiles/yitrace.dir/apps/yitrace.cpp.o


# Object files for target yitrace
yitrace_OBJECTS = \
"CMakeFiles/yitrace.dir/apps/yitrace.cpp.o"

# External object files for target yitrace
yitrace_EXTERNAL_OBJECTS =

../bin/yitrace: CMakeFiles/yitrace.dir/apps/yitrace.cpp.o
../bin/yitrace: CMakeFiles/yitrace.dir/build.make
../bin/yitrace: ../bin/libyocto_gl.a
../bin/yitrace: /usr/lib/x86_64-linux-gnu/libGL.so
../bin/yitrace: /usr/lib/x86_64-linux-gnu/libglfw.so
../bin/yitrace: /usr/lib/x86_64-linux-gnu/libGLEW.so
../bin/yitrace: CMakeFiles/yitrace.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/antoniomusolino/Scrivania/yocto-gl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/yitrace"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yitrace.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/yitrace.dir/build: ../bin/yitrace

.PHONY : CMakeFiles/yitrace.dir/build

CMakeFiles/yitrace.dir/requires: CMakeFiles/yitrace.dir/apps/yitrace.cpp.o.requires

.PHONY : CMakeFiles/yitrace.dir/requires

CMakeFiles/yitrace.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/yitrace.dir/cmake_clean.cmake
.PHONY : CMakeFiles/yitrace.dir/clean

CMakeFiles/yitrace.dir/depend:
	cd /home/antoniomusolino/Scrivania/yocto-gl/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/antoniomusolino/Scrivania/yocto-gl /home/antoniomusolino/Scrivania/yocto-gl /home/antoniomusolino/Scrivania/yocto-gl/cmake-build-debug /home/antoniomusolino/Scrivania/yocto-gl/cmake-build-debug /home/antoniomusolino/Scrivania/yocto-gl/cmake-build-debug/CMakeFiles/yitrace.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/yitrace.dir/depend

