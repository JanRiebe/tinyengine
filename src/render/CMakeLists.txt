cmake_minimum_required(VERSION 3.0.0)
project(exercise11
        DESCRIPTION "GDV 2021 Exercise11" 
        LANGUAGES CXX)
        
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)
# project setting
# set default build type if non was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'release' as none was specidied.")
    set(CMAKE_BUILD_TYPE
    Release 
    CACHE STRING "Choose the type of build." FORCE)
endif(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
# GENERATE COMPILE_COMMANDS.JSON
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# project warnings
function(set_project_warnings project_name)
    option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors." FALSE)
    set(CLANG_WARNINGS
    -Wall
    -Wextra
    -Wshadow # warn user if a variable is beeing shadowed
    -Wold-style-cast # warn if for old c-style casts
    -Wcast-align # warn for potentially performance reducing casts
    -Wunused # warn on anything beeing unused
    -Woverloaded-virtual # warn if you overload (not overwrite) a virtual function
    -Wpedantic # warn if non-standard C++ is used
    -Wconversion # warn on type conversion that might loose data
    -Wsign-conversion # warn on sign conversion
    -Wnull-dereference # warn if a null dereference is detected
    -Wdouble-promotion # warn if a float is implicitly promoted to double
    -Wformat=2 # warn security issues around functions that format blocks where there are none
    )
    if (WARNINGS_AS_ERRORS)
            set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
    endif()
    target_compile_options(${project_name} INTERFACE ${CLANG_WARNINGS})
endfunction()

add_executable(simple src/Simple.cpp
  src/Camera.cpp
  src/DirectionalLight.cpp
  src/eventhandling.cpp
  src/fileio.cpp
  src/gltools.cpp
  src/ImagePlaneMesh.cpp
  src/Matrix4x4.cpp
  src/Mesh.cpp
)

add_executable(phong src/Phong.cpp
  src/Camera.cpp
  src/DirectionalLight.cpp
  src/eventhandling.cpp
  src/fileio.cpp
  src/gltools.cpp
  src/ImagePlaneMesh.cpp
  src/Matrix4x4.cpp
  src/Mesh.cpp
)

add_executable(npr src/Npr.cpp
  src/Camera.cpp
  src/DirectionalLight.cpp
  src/eventhandling.cpp
  src/fileio.cpp
  src/gltools.cpp
  src/ImagePlaneMesh.cpp
  src/Matrix4x4.cpp
  src/Mesh.cpp
)

add_executable(bump src/BumpMapping.cpp
  src/Camera.cpp
  src/DirectionalLight.cpp
  src/eventhandling.cpp
  src/fileio.cpp
  src/gltools.cpp
  src/ImagePlaneMesh.cpp
  src/Matrix4x4.cpp
  src/Mesh.cpp
)

add_executable(displacement src/DisplacementMapping.cpp
  src/Camera.cpp
  src/DirectionalLight.cpp
  src/eventhandling.cpp
  src/fileio.cpp
  src/gltools.cpp
  src/ImagePlaneMesh.cpp
  src/Matrix4x4.cpp
  src/Mesh.cpp
)

add_executable(shadow src/ShadowMapping.cpp
  src/Camera.cpp
  src/DirectionalLight.cpp
  src/eventhandling.cpp
  src/fileio.cpp
  src/gltools.cpp
  src/ImagePlaneMesh.cpp
  src/Matrix4x4.cpp
  src/Mesh.cpp
)

add_executable(hdr src/Hdr.cpp
  src/Camera.cpp
  src/DirectionalLight.cpp
  src/eventhandling.cpp
  src/fileio.cpp
  src/gltools.cpp
  src/ImagePlaneMesh.cpp
  src/Matrix4x4.cpp
  src/Mesh.cpp
)

add_executable(combined src/combined.cpp
  src/Camera.cpp
  src/DirectionalLight.cpp
  src/eventhandling.cpp
  src/fileio.cpp
  src/gltools.cpp
  src/ImagePlaneMesh.cpp
  src/Matrix4x4.cpp
  src/Mesh.cpp
)

# link the submission library
target_link_libraries(combined PRIVATE SDL GL GLU X11)
set_project_warnings(combined)
target_link_libraries(simple PRIVATE SDL GL GLU X11)
set_project_warnings(simple)
target_link_libraries(phong PRIVATE SDL GL GLU X11)
set_project_warnings(phong)
target_link_libraries(npr PRIVATE SDL GL GLU X11)
set_project_warnings(npr)
target_link_libraries(bump PRIVATE SDL GL GLU X11)
set_project_warnings(bump)
target_link_libraries(displacement PRIVATE SDL GL GLU X11)
set_project_warnings(displacement)
target_link_libraries(shadow PRIVATE SDL GL GLU X11)
set_project_warnings(shadow)
target_link_libraries(hdr PRIVATE SDL GL GLU X11)
set_project_warnings(hdr)

