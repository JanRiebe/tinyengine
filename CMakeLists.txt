cmake_minimum_required(VERSION 3.0.0)
project(tinyengine
        DESCRIPTION "A tiny game engine" 
        LANGUAGES CXX)
        
set(OpenGL_GL_PREFERENCE LEGACY)
find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
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

add_executable(tinyengine 	src/gamenode.cpp
			   	src/glutInput.h
			   	src/modules.h
			   	src/transform.cpp
			   	src/Utils.h
			   	src/gamenode.h
			   	src/input.h
			   	src/renderer.cpp
			   	src/transform.h
			   	src/glutInput.cpp
			   	src/main.cpp
			   	src/renderer.h
			   	src/Utils.cpp

                          )
# link the submission library
target_link_libraries(tinyengine PRIVATE SDL GL GLU X11)
target_link_libraries(tinyengine PRIVATE)
set_project_warnings(tinyengine)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
  target_compile_definitions(tinyengine PRIVATE OPENMP)
  target_link_libraries(tinyengine PRIVATE OpenMP::OpenMP_CXX)
endif()


                               

                       
