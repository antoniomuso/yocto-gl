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
include CMakeFiles/yimview.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/yimview.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/yimview.dir/flags.make

CMakeFiles/yimview.dir/apps/yimview.cpp.o: CMakeFiles/yimview.dir/flags.make
CMakeFiles/yimview.dir/apps/yimview.cpp.o: ../apps/yimview.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/antoniomusolino/Scrivania/yocto-gl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/yimview.dir/apps/yimview.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/yimview.dir/apps/yimview.cpp.o -c /home/antoniomusolino/Scrivania/yocto-gl/apps/yimview.cpp

CMakeFiles/yimview.dir/apps/yimview.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yimview.dir/apps/yimview.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/antoniomusolino/Scrivania/yocto-gl/apps/yimview.cpp > CMakeFiles/yimview.dir/apps/yimview.cpp.i

CMakeFiles/yimview.dir/apps/yimview.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yimview.dir/apps/yimview.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/antoniomusolino/Scrivania/yocto-gl/apps/yimview.cpp -o CMakeFiles/yimview.dir/apps/yimview.cpp.s

CMakeFiles/yimview.dir/apps/yimview.cpp.o.requires:

.PHONY : CMakeFiles/yimview.dir/apps/yimview.cpp.o.requires

CMakeFiles/yimview.dir/apps/yimview.cpp.o.provides: CMakeFiles/yimview.dir/apps/yimview.cpp.o.requires
	$(MAKE) -f CMakeFiles/yimview.dir/build.make CMakeFiles/yimview.dir/apps/yimview.cpp.o.provides.build
.PHONY : CMakeFiles/yimview.dir/apps/yimview.cpp.o.provides

CMakeFiles/yimview.dir/apps/yimview.cpp.o.provides.build: CMakeFiles/yimview.dir/apps/yimview.cpp.o


# Object files for target yimview
yimview_OBJECTS = \
"CMakeFiles/yimview.dir/apps/yimview.cpp.o"

# External object files for target yimview
yimview_EXTERNAL_OBJECTS =

../bin/yimview: CMakeFiles/yimview.dir/apps/yimview.cpp.o
../bin/yimview: CMakeFiles/yimview.dir/build.make
../bin/yimview: ../bin/libyocto_gl.a
../bin/yimview: /usr/lib/x86_64-linux-gnu/libGL.so
../bin/yimview: /usr/lib/x86_64-linux-gnu/libglfw.so
../bin/yimview: /usr/lib/x86_64-linux-gnu/libGLEW.so
../bin/yimview: CMakeFiles/yimview.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/antoniomusolino/Scrivania/yocto-gl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/yimview"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yimview.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/yimview.dir/build: ../bin/yimview

.PHONY : CMakeFiles/yimview.dir/build

CMakeFiles/yimview.dir/requires: CMakeFiles/yimview.dir/apps/yimview.cpp.o.requires

.PHONY : CMakeFiles/yimview.dir/requires

CMakeFiles/yimview.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/yimview.dir/cmake_clean.cmake
.PHONY : CMakeFiles/yimview.dir/clean

CMakeFiles/yimview.dir/depend:
	cd /home/antoniomusolino/Scrivania/yocto-gl/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/antoniomusolino/Scrivania/yocto-gl /home/antoniomusolino/Scrivania/yocto-gl /home/antoniomusolino/Scrivania/yocto-gl/cmake-build-debug /home/antoniomusolino/Scrivania/yocto-gl/cmake-build-debug /home/antoniomusolino/Scrivania/yocto-gl/cmake-build-debug/CMakeFiles/yimview.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/yimview.dir/depend

