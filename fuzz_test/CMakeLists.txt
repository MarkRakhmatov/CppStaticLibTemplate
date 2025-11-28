cmake_minimum_required(VERSION 3.15...3.23)

set(TESTED_PROJECT_NAME CppStaticLib)

# Only set the cxx_standard if it is not set by someone else
if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 23)
endif()

project(${TESTED_PROJECT_NAME}FuzzTests LANGUAGES CXX)

# ---- Options ----

option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

if(TEST_INSTALLED_VERSION)
  find_package(${TESTED_PROJECT_NAME} CONFIG REQUIRED) # for intro, project_options, ...

  if(NOT TARGET ${TESTED_PROJECT_NAME}_options)
    message(FATAL_ERROR "Required config package not found!")
    return() # be strictly paranoid for Template Janitor github action! CK
  endif()
endif()

CPMAddPackage("gh:boost-ext/ut@2.3.1")
CPMAddPackage("gh:google/fuzztest@2025-08-05")

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::ut fuzztest::fuzztest ${TESTED_PROJECT_NAME})

target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})

# enable compiler warnings
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wpedantic -Wextra -Werror)

# ---- Add Tests ----

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
