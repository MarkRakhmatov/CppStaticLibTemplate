cmake_minimum_required(VERSION 3.14...3.22)

# ---- Project ----

# Only set the cxx_standard if it is not set by someone else
if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
endif()

# strongly encouraged to enable this globally to avoid conflicts between -Wpedantic being enabled
# and -std=c++23 and -std=gnu++23 for example when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

# Note: update this to your new project's name and version
project(
  CppStaticLib
  VERSION 1.0
  LANGUAGES CXX
)

option(BUILD_TESTS "Build test" ON)
option(ENABLE_CODE_ANALYSIS "Run static code analysis" OFF)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.8.0")

# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# ---- Static analisys ----

if(ENABLE_CODE_ANALYSIS)
  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Clang compiler detected. Integrating clang-tidy")
    set(CMAKE_CXX_CLANG_TIDY clang-tidy; -header-filter=.)
  else()
    message(STATUS "Integrating Cppcheck")
    find_program(CPPCHECK_EXECUTABLE NAMES cppcheck REQUIRED)
    set(CMAKE_CXX_CPPCHECK
        ${CPPCHECK_EXECUTABLE};
        --std=c++${CMAKE_CXX_STANDARD};--enable=all;--error-exitcode=10;--suppressions-list=${PROJECT_SOURCE_DIR}/cppcheck.supp;
    )
  endif()
endif()

# ---- Create static library ----

add_library(${PROJECT_NAME} STATIC ${headers} ${sources})

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# Don't even look at tests if we're not top level
if(NOT PROJECT_IS_TOP_LEVEL)
  return()
endif()

# ---- Tests ----
if(BUILD_TESTS)
  add_subdirectory(test)
endif()

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed should match the project's regular
# header paths
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  NAMESPACE ${PROJECT_NAME}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  COMPATIBILITY SameMajorVersion
)
