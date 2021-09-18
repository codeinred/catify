# Requirements
cmake_minimum_required(VERSION 3.14)

################################
## Section 1: Declare project ##
################################
set(project_name catify)
set(libname "lib${project_name}")
project(${project_name} CXX)

include("${CMAKE_CURRENT_SOURCE_DIR}/helper.cmake")
###################################
## Section 2: Project CMake code ##
###################################

# Add library and register compile options
add_library(${libname} INTERFACE)

target_cpp_20(${libname})

target_include_directories(
    ${libname}
    INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:include>
)

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION include
)

if(${CMAKE_PROJECT_NAME} STREQUAL ${project_name})
    find_or_fetch(fmt "https://github.com/fmtlib/fmt.git" master)

    add_source_dir(src ${libname} fmt)
endif()
