# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/jan/code_projects/tinyengine/src/render_reference

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jan/code_projects/tinyengine/src/render_reference

# Include any dependencies generated for this target.
include CMakeFiles/phong.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/phong.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/phong.dir/flags.make

CMakeFiles/phong.dir/src/Phong.cpp.o: CMakeFiles/phong.dir/flags.make
CMakeFiles/phong.dir/src/Phong.cpp.o: src/Phong.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/phong.dir/src/Phong.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/phong.dir/src/Phong.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/Phong.cpp

CMakeFiles/phong.dir/src/Phong.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phong.dir/src/Phong.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/Phong.cpp > CMakeFiles/phong.dir/src/Phong.cpp.i

CMakeFiles/phong.dir/src/Phong.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phong.dir/src/Phong.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/Phong.cpp -o CMakeFiles/phong.dir/src/Phong.cpp.s

CMakeFiles/phong.dir/src/Camera.cpp.o: CMakeFiles/phong.dir/flags.make
CMakeFiles/phong.dir/src/Camera.cpp.o: src/Camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/phong.dir/src/Camera.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/phong.dir/src/Camera.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/Camera.cpp

CMakeFiles/phong.dir/src/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phong.dir/src/Camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/Camera.cpp > CMakeFiles/phong.dir/src/Camera.cpp.i

CMakeFiles/phong.dir/src/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phong.dir/src/Camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/Camera.cpp -o CMakeFiles/phong.dir/src/Camera.cpp.s

CMakeFiles/phong.dir/src/DirectionalLight.cpp.o: CMakeFiles/phong.dir/flags.make
CMakeFiles/phong.dir/src/DirectionalLight.cpp.o: src/DirectionalLight.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/phong.dir/src/DirectionalLight.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/phong.dir/src/DirectionalLight.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/DirectionalLight.cpp

CMakeFiles/phong.dir/src/DirectionalLight.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phong.dir/src/DirectionalLight.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/DirectionalLight.cpp > CMakeFiles/phong.dir/src/DirectionalLight.cpp.i

CMakeFiles/phong.dir/src/DirectionalLight.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phong.dir/src/DirectionalLight.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/DirectionalLight.cpp -o CMakeFiles/phong.dir/src/DirectionalLight.cpp.s

CMakeFiles/phong.dir/src/eventhandling.cpp.o: CMakeFiles/phong.dir/flags.make
CMakeFiles/phong.dir/src/eventhandling.cpp.o: src/eventhandling.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/phong.dir/src/eventhandling.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/phong.dir/src/eventhandling.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/eventhandling.cpp

CMakeFiles/phong.dir/src/eventhandling.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phong.dir/src/eventhandling.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/eventhandling.cpp > CMakeFiles/phong.dir/src/eventhandling.cpp.i

CMakeFiles/phong.dir/src/eventhandling.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phong.dir/src/eventhandling.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/eventhandling.cpp -o CMakeFiles/phong.dir/src/eventhandling.cpp.s

CMakeFiles/phong.dir/src/fileio.cpp.o: CMakeFiles/phong.dir/flags.make
CMakeFiles/phong.dir/src/fileio.cpp.o: src/fileio.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/phong.dir/src/fileio.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/phong.dir/src/fileio.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/fileio.cpp

CMakeFiles/phong.dir/src/fileio.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phong.dir/src/fileio.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/fileio.cpp > CMakeFiles/phong.dir/src/fileio.cpp.i

CMakeFiles/phong.dir/src/fileio.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phong.dir/src/fileio.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/fileio.cpp -o CMakeFiles/phong.dir/src/fileio.cpp.s

CMakeFiles/phong.dir/src/gltools.cpp.o: CMakeFiles/phong.dir/flags.make
CMakeFiles/phong.dir/src/gltools.cpp.o: src/gltools.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/phong.dir/src/gltools.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/phong.dir/src/gltools.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/gltools.cpp

CMakeFiles/phong.dir/src/gltools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phong.dir/src/gltools.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/gltools.cpp > CMakeFiles/phong.dir/src/gltools.cpp.i

CMakeFiles/phong.dir/src/gltools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phong.dir/src/gltools.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/gltools.cpp -o CMakeFiles/phong.dir/src/gltools.cpp.s

CMakeFiles/phong.dir/src/ImagePlaneMesh.cpp.o: CMakeFiles/phong.dir/flags.make
CMakeFiles/phong.dir/src/ImagePlaneMesh.cpp.o: src/ImagePlaneMesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/phong.dir/src/ImagePlaneMesh.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/phong.dir/src/ImagePlaneMesh.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/ImagePlaneMesh.cpp

CMakeFiles/phong.dir/src/ImagePlaneMesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phong.dir/src/ImagePlaneMesh.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/ImagePlaneMesh.cpp > CMakeFiles/phong.dir/src/ImagePlaneMesh.cpp.i

CMakeFiles/phong.dir/src/ImagePlaneMesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phong.dir/src/ImagePlaneMesh.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/ImagePlaneMesh.cpp -o CMakeFiles/phong.dir/src/ImagePlaneMesh.cpp.s

CMakeFiles/phong.dir/src/Matrix4x4.cpp.o: CMakeFiles/phong.dir/flags.make
CMakeFiles/phong.dir/src/Matrix4x4.cpp.o: src/Matrix4x4.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/phong.dir/src/Matrix4x4.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/phong.dir/src/Matrix4x4.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/Matrix4x4.cpp

CMakeFiles/phong.dir/src/Matrix4x4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phong.dir/src/Matrix4x4.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/Matrix4x4.cpp > CMakeFiles/phong.dir/src/Matrix4x4.cpp.i

CMakeFiles/phong.dir/src/Matrix4x4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phong.dir/src/Matrix4x4.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/Matrix4x4.cpp -o CMakeFiles/phong.dir/src/Matrix4x4.cpp.s

CMakeFiles/phong.dir/src/Mesh.cpp.o: CMakeFiles/phong.dir/flags.make
CMakeFiles/phong.dir/src/Mesh.cpp.o: src/Mesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/phong.dir/src/Mesh.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/phong.dir/src/Mesh.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/Mesh.cpp

CMakeFiles/phong.dir/src/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phong.dir/src/Mesh.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/Mesh.cpp > CMakeFiles/phong.dir/src/Mesh.cpp.i

CMakeFiles/phong.dir/src/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phong.dir/src/Mesh.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/Mesh.cpp -o CMakeFiles/phong.dir/src/Mesh.cpp.s

# Object files for target phong
phong_OBJECTS = \
"CMakeFiles/phong.dir/src/Phong.cpp.o" \
"CMakeFiles/phong.dir/src/Camera.cpp.o" \
"CMakeFiles/phong.dir/src/DirectionalLight.cpp.o" \
"CMakeFiles/phong.dir/src/eventhandling.cpp.o" \
"CMakeFiles/phong.dir/src/fileio.cpp.o" \
"CMakeFiles/phong.dir/src/gltools.cpp.o" \
"CMakeFiles/phong.dir/src/ImagePlaneMesh.cpp.o" \
"CMakeFiles/phong.dir/src/Matrix4x4.cpp.o" \
"CMakeFiles/phong.dir/src/Mesh.cpp.o"

# External object files for target phong
phong_EXTERNAL_OBJECTS =

phong: CMakeFiles/phong.dir/src/Phong.cpp.o
phong: CMakeFiles/phong.dir/src/Camera.cpp.o
phong: CMakeFiles/phong.dir/src/DirectionalLight.cpp.o
phong: CMakeFiles/phong.dir/src/eventhandling.cpp.o
phong: CMakeFiles/phong.dir/src/fileio.cpp.o
phong: CMakeFiles/phong.dir/src/gltools.cpp.o
phong: CMakeFiles/phong.dir/src/ImagePlaneMesh.cpp.o
phong: CMakeFiles/phong.dir/src/Matrix4x4.cpp.o
phong: CMakeFiles/phong.dir/src/Mesh.cpp.o
phong: CMakeFiles/phong.dir/build.make
phong: CMakeFiles/phong.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable phong"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/phong.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/phong.dir/build: phong

.PHONY : CMakeFiles/phong.dir/build

CMakeFiles/phong.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/phong.dir/cmake_clean.cmake
.PHONY : CMakeFiles/phong.dir/clean

CMakeFiles/phong.dir/depend:
	cd /home/jan/code_projects/tinyengine/src/render_reference && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jan/code_projects/tinyengine/src/render_reference /home/jan/code_projects/tinyengine/src/render_reference /home/jan/code_projects/tinyengine/src/render_reference /home/jan/code_projects/tinyengine/src/render_reference /home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles/phong.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/phong.dir/depend
