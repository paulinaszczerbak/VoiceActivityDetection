# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde

# Include any dependencies generated for this target.
include examples/am_modulation/CMakeFiles/am_modulation.dir/depend.make

# Include the progress variables for this target.
include examples/am_modulation/CMakeFiles/am_modulation.dir/progress.make

# Include the compile flags for this target's objects.
include examples/am_modulation/CMakeFiles/am_modulation.dir/flags.make

examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o: examples/am_modulation/CMakeFiles/am_modulation.dir/flags.make
examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o: examples/am_modulation/am_modulation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o"
	cd /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/examples/am_modulation && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/am_modulation.dir/am_modulation.cpp.o -c /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/examples/am_modulation/am_modulation.cpp

examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/am_modulation.dir/am_modulation.cpp.i"
	cd /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/examples/am_modulation && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/examples/am_modulation/am_modulation.cpp > CMakeFiles/am_modulation.dir/am_modulation.cpp.i

examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/am_modulation.dir/am_modulation.cpp.s"
	cd /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/examples/am_modulation && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/examples/am_modulation/am_modulation.cpp -o CMakeFiles/am_modulation.dir/am_modulation.cpp.s

examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.requires:

.PHONY : examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.requires

examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.provides: examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.requires
	$(MAKE) -f examples/am_modulation/CMakeFiles/am_modulation.dir/build.make examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.provides.build
.PHONY : examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.provides

examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.provides.build: examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o


# Object files for target am_modulation
am_modulation_OBJECTS = \
"CMakeFiles/am_modulation.dir/am_modulation.cpp.o"

# External object files for target am_modulation
am_modulation_EXTERNAL_OBJECTS =

examples/am_modulation/am_modulation: examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o
examples/am_modulation/am_modulation: examples/am_modulation/CMakeFiles/am_modulation.dir/build.make
examples/am_modulation/am_modulation: libAquila.a
examples/am_modulation/am_modulation: lib/libOoura_fft.a
examples/am_modulation/am_modulation: examples/am_modulation/CMakeFiles/am_modulation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable am_modulation"
	cd /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/examples/am_modulation && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/am_modulation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/am_modulation/CMakeFiles/am_modulation.dir/build: examples/am_modulation/am_modulation

.PHONY : examples/am_modulation/CMakeFiles/am_modulation.dir/build

examples/am_modulation/CMakeFiles/am_modulation.dir/requires: examples/am_modulation/CMakeFiles/am_modulation.dir/am_modulation.cpp.o.requires

.PHONY : examples/am_modulation/CMakeFiles/am_modulation.dir/requires

examples/am_modulation/CMakeFiles/am_modulation.dir/clean:
	cd /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/examples/am_modulation && $(CMAKE_COMMAND) -P CMakeFiles/am_modulation.dir/cmake_clean.cmake
.PHONY : examples/am_modulation/CMakeFiles/am_modulation.dir/clean

examples/am_modulation/CMakeFiles/am_modulation.dir/depend:
	cd /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/examples/am_modulation /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/examples/am_modulation /home/paulina/github/VoiceActivityDetection/zsiciarz-aquila-d5e3bde/examples/am_modulation/CMakeFiles/am_modulation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/am_modulation/CMakeFiles/am_modulation.dir/depend
