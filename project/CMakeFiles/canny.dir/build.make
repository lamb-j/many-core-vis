# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /opt/apps/cmake-3.6.3/bin/cmake

# The command to remove a file.
RM = /opt/apps/cmake-3.6.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/users/jlambert/semvis/project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/users/jlambert/semvis/project

# Include any dependencies generated for this target.
include CMakeFiles/canny.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/canny.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/canny.dir/flags.make

CMakeFiles/canny.dir/canny.cxx.o: CMakeFiles/canny.dir/flags.make
CMakeFiles/canny.dir/canny.cxx.o: canny.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/users/jlambert/semvis/project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/canny.dir/canny.cxx.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/canny.dir/canny.cxx.o -c /home/users/jlambert/semvis/project/canny.cxx

CMakeFiles/canny.dir/canny.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/canny.dir/canny.cxx.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/users/jlambert/semvis/project/canny.cxx > CMakeFiles/canny.dir/canny.cxx.i

CMakeFiles/canny.dir/canny.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/canny.dir/canny.cxx.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/users/jlambert/semvis/project/canny.cxx -o CMakeFiles/canny.dir/canny.cxx.s

CMakeFiles/canny.dir/canny.cxx.o.requires:

.PHONY : CMakeFiles/canny.dir/canny.cxx.o.requires

CMakeFiles/canny.dir/canny.cxx.o.provides: CMakeFiles/canny.dir/canny.cxx.o.requires
	$(MAKE) -f CMakeFiles/canny.dir/build.make CMakeFiles/canny.dir/canny.cxx.o.provides.build
.PHONY : CMakeFiles/canny.dir/canny.cxx.o.provides

CMakeFiles/canny.dir/canny.cxx.o.provides.build: CMakeFiles/canny.dir/canny.cxx.o


CMakeFiles/canny.dir/bmp_reader.cxx.o: CMakeFiles/canny.dir/flags.make
CMakeFiles/canny.dir/bmp_reader.cxx.o: bmp_reader.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/users/jlambert/semvis/project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/canny.dir/bmp_reader.cxx.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/canny.dir/bmp_reader.cxx.o -c /home/users/jlambert/semvis/project/bmp_reader.cxx

CMakeFiles/canny.dir/bmp_reader.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/canny.dir/bmp_reader.cxx.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/users/jlambert/semvis/project/bmp_reader.cxx > CMakeFiles/canny.dir/bmp_reader.cxx.i

CMakeFiles/canny.dir/bmp_reader.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/canny.dir/bmp_reader.cxx.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/users/jlambert/semvis/project/bmp_reader.cxx -o CMakeFiles/canny.dir/bmp_reader.cxx.s

CMakeFiles/canny.dir/bmp_reader.cxx.o.requires:

.PHONY : CMakeFiles/canny.dir/bmp_reader.cxx.o.requires

CMakeFiles/canny.dir/bmp_reader.cxx.o.provides: CMakeFiles/canny.dir/bmp_reader.cxx.o.requires
	$(MAKE) -f CMakeFiles/canny.dir/build.make CMakeFiles/canny.dir/bmp_reader.cxx.o.provides.build
.PHONY : CMakeFiles/canny.dir/bmp_reader.cxx.o.provides

CMakeFiles/canny.dir/bmp_reader.cxx.o.provides.build: CMakeFiles/canny.dir/bmp_reader.cxx.o


# Object files for target canny
canny_OBJECTS = \
"CMakeFiles/canny.dir/canny.cxx.o" \
"CMakeFiles/canny.dir/bmp_reader.cxx.o"

# External object files for target canny
canny_EXTERNAL_OBJECTS =

canny: CMakeFiles/canny.dir/canny.cxx.o
canny: CMakeFiles/canny.dir/bmp_reader.cxx.o
canny: CMakeFiles/canny.dir/build.make
canny: /home/users/jlambert/my_build/lib/libvtkm_cont.so
canny: CMakeFiles/canny.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/users/jlambert/semvis/project/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable canny"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/canny.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/canny.dir/build: canny

.PHONY : CMakeFiles/canny.dir/build

CMakeFiles/canny.dir/requires: CMakeFiles/canny.dir/canny.cxx.o.requires
CMakeFiles/canny.dir/requires: CMakeFiles/canny.dir/bmp_reader.cxx.o.requires

.PHONY : CMakeFiles/canny.dir/requires

CMakeFiles/canny.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/canny.dir/cmake_clean.cmake
.PHONY : CMakeFiles/canny.dir/clean

CMakeFiles/canny.dir/depend:
	cd /home/users/jlambert/semvis/project && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/users/jlambert/semvis/project /home/users/jlambert/semvis/project /home/users/jlambert/semvis/project /home/users/jlambert/semvis/project /home/users/jlambert/semvis/project/CMakeFiles/canny.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/canny.dir/depend

