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
include CMakeFiles/shadow.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/shadow.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shadow.dir/flags.make

CMakeFiles/shadow.dir/src/ShadowMapping.cpp.o: CMakeFiles/shadow.dir/flags.make
CMakeFiles/shadow.dir/src/ShadowMapping.cpp.o: src/ShadowMapping.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/shadow.dir/src/ShadowMapping.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shadow.dir/src/ShadowMapping.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/ShadowMapping.cpp

CMakeFiles/shadow.dir/src/ShadowMapping.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shadow.dir/src/ShadowMapping.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/ShadowMapping.cpp > CMakeFiles/shadow.dir/src/ShadowMapping.cpp.i

CMakeFiles/shadow.dir/src/ShadowMapping.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shadow.dir/src/ShadowMapping.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/ShadowMapping.cpp -o CMakeFiles/shadow.dir/src/ShadowMapping.cpp.s

CMakeFiles/shadow.dir/src/Camera.cpp.o: CMakeFiles/shadow.dir/flags.make
CMakeFiles/shadow.dir/src/Camera.cpp.o: src/Camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/shadow.dir/src/Camera.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shadow.dir/src/Camera.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/Camera.cpp

CMakeFiles/shadow.dir/src/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shadow.dir/src/Camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/Camera.cpp > CMakeFiles/shadow.dir/src/Camera.cpp.i

CMakeFiles/shadow.dir/src/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shadow.dir/src/Camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/Camera.cpp -o CMakeFiles/shadow.dir/src/Camera.cpp.s

CMakeFiles/shadow.dir/src/DirectionalLight.cpp.o: CMakeFiles/shadow.dir/flags.make
CMakeFiles/shadow.dir/src/DirectionalLight.cpp.o: src/DirectionalLight.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/shadow.dir/src/DirectionalLight.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shadow.dir/src/DirectionalLight.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/DirectionalLight.cpp

CMakeFiles/shadow.dir/src/DirectionalLight.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shadow.dir/src/DirectionalLight.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/DirectionalLight.cpp > CMakeFiles/shadow.dir/src/DirectionalLight.cpp.i

CMakeFiles/shadow.dir/src/DirectionalLight.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shadow.dir/src/DirectionalLight.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/DirectionalLight.cpp -o CMakeFiles/shadow.dir/src/DirectionalLight.cpp.s

CMakeFiles/shadow.dir/src/eventhandling.cpp.o: CMakeFiles/shadow.dir/flags.make
CMakeFiles/shadow.dir/src/eventhandling.cpp.o: src/eventhandling.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/shadow.dir/src/eventhandling.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shadow.dir/src/eventhandling.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/eventhandling.cpp

CMakeFiles/shadow.dir/src/eventhandling.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shadow.dir/src/eventhandling.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/eventhandling.cpp > CMakeFiles/shadow.dir/src/eventhandling.cpp.i

CMakeFiles/shadow.dir/src/eventhandling.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shadow.dir/src/eventhandling.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/eventhandling.cpp -o CMakeFiles/shadow.dir/src/eventhandling.cpp.s

CMakeFiles/shadow.dir/src/fileio.cpp.o: CMakeFiles/shadow.dir/flags.make
CMakeFiles/shadow.dir/src/fileio.cpp.o: src/fileio.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/shadow.dir/src/fileio.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shadow.dir/src/fileio.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/fileio.cpp

CMakeFiles/shadow.dir/src/fileio.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shadow.dir/src/fileio.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/fileio.cpp > CMakeFiles/shadow.dir/src/fileio.cpp.i

CMakeFiles/shadow.dir/src/fileio.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shadow.dir/src/fileio.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/fileio.cpp -o CMakeFiles/shadow.dir/src/fileio.cpp.s

CMakeFiles/shadow.dir/src/gltools.cpp.o: CMakeFiles/shadow.dir/flags.make
CMakeFiles/shadow.dir/src/gltools.cpp.o: src/gltools.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/shadow.dir/src/gltools.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shadow.dir/src/gltools.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/gltools.cpp

CMakeFiles/shadow.dir/src/gltools.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shadow.dir/src/gltools.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/gltools.cpp > CMakeFiles/shadow.dir/src/gltools.cpp.i

CMakeFiles/shadow.dir/src/gltools.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shadow.dir/src/gltools.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/gltools.cpp -o CMakeFiles/shadow.dir/src/gltools.cpp.s

CMakeFiles/shadow.dir/src/ImagePlaneMesh.cpp.o: CMakeFiles/shadow.dir/flags.make
CMakeFiles/shadow.dir/src/ImagePlaneMesh.cpp.o: src/ImagePlaneMesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/shadow.dir/src/ImagePlaneMesh.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shadow.dir/src/ImagePlaneMesh.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/ImagePlaneMesh.cpp

CMakeFiles/shadow.dir/src/ImagePlaneMesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shadow.dir/src/ImagePlaneMesh.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/ImagePlaneMesh.cpp > CMakeFiles/shadow.dir/src/ImagePlaneMesh.cpp.i

CMakeFiles/shadow.dir/src/ImagePlaneMesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shadow.dir/src/ImagePlaneMesh.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/ImagePlaneMesh.cpp -o CMakeFiles/shadow.dir/src/ImagePlaneMesh.cpp.s

CMakeFiles/shadow.dir/src/Matrix4x4.cpp.o: CMakeFiles/shadow.dir/flags.make
CMakeFiles/shadow.dir/src/Matrix4x4.cpp.o: src/Matrix4x4.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/shadow.dir/src/Matrix4x4.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shadow.dir/src/Matrix4x4.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/Matrix4x4.cpp

CMakeFiles/shadow.dir/src/Matrix4x4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shadow.dir/src/Matrix4x4.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/Matrix4x4.cpp > CMakeFiles/shadow.dir/src/Matrix4x4.cpp.i

CMakeFiles/shadow.dir/src/Matrix4x4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shadow.dir/src/Matrix4x4.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/Matrix4x4.cpp -o CMakeFiles/shadow.dir/src/Matrix4x4.cpp.s

CMakeFiles/shadow.dir/src/Mesh.cpp.o: CMakeFiles/shadow.dir/flags.make
CMakeFiles/shadow.dir/src/Mesh.cpp.o: src/Mesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/shadow.dir/src/Mesh.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shadow.dir/src/Mesh.cpp.o -c /home/jan/code_projects/tinyengine/src/render_reference/src/Mesh.cpp

CMakeFiles/shadow.dir/src/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shadow.dir/src/Mesh.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jan/code_projects/tinyengine/src/render_reference/src/Mesh.cpp > CMakeFiles/shadow.dir/src/Mesh.cpp.i

CMakeFiles/shadow.dir/src/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shadow.dir/src/Mesh.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jan/code_projects/tinyengine/src/render_reference/src/Mesh.cpp -o CMakeFiles/shadow.dir/src/Mesh.cpp.s

# Object files for target shadow
shadow_OBJECTS = \
"CMakeFiles/shadow.dir/src/ShadowMapping.cpp.o" \
"CMakeFiles/shadow.dir/src/Camera.cpp.o" \
"CMakeFiles/shadow.dir/src/DirectionalLight.cpp.o" \
"CMakeFiles/shadow.dir/src/eventhandling.cpp.o" \
"CMakeFiles/shadow.dir/src/fileio.cpp.o" \
"CMakeFiles/shadow.dir/src/gltools.cpp.o" \
"CMakeFiles/shadow.dir/src/ImagePlaneMesh.cpp.o" \
"CMakeFiles/shadow.dir/src/Matrix4x4.cpp.o" \
"CMakeFiles/shadow.dir/src/Mesh.cpp.o"

# External object files for target shadow
shadow_EXTERNAL_OBJECTS =

shadow: CMakeFiles/shadow.dir/src/ShadowMapping.cpp.o
shadow: CMakeFiles/shadow.dir/src/Camera.cpp.o
shadow: CMakeFiles/shadow.dir/src/DirectionalLight.cpp.o
shadow: CMakeFiles/shadow.dir/src/eventhandling.cpp.o
shadow: CMakeFiles/shadow.dir/src/fileio.cpp.o
shadow: CMakeFiles/shadow.dir/src/gltools.cpp.o
shadow: CMakeFiles/shadow.dir/src/ImagePlaneMesh.cpp.o
shadow: CMakeFiles/shadow.dir/src/Matrix4x4.cpp.o
shadow: CMakeFiles/shadow.dir/src/Mesh.cpp.o
shadow: CMakeFiles/shadow.dir/build.make
shadow: CMakeFiles/shadow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable shadow"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shadow.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shadow.dir/build: shadow

.PHONY : CMakeFiles/shadow.dir/build

CMakeFiles/shadow.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shadow.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shadow.dir/clean

CMakeFiles/shadow.dir/depend:
	cd /home/jan/code_projects/tinyengine/src/render_reference && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jan/code_projects/tinyengine/src/render_reference /home/jan/code_projects/tinyengine/src/render_reference /home/jan/code_projects/tinyengine/src/render_reference /home/jan/code_projects/tinyengine/src/render_reference /home/jan/code_projects/tinyengine/src/render_reference/CMakeFiles/shadow.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shadow.dir/depend
