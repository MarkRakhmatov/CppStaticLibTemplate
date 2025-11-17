cmake_minimum_required(VERSION 3.15...3.23)

set(TESTED_PROJECT_NAME CppStaticLib)

project(${TESTED_PROJECT_NAME}Tests LANGUAGES CXX)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

if(TEST_INSTALLED_VERSION)
  find_package(${TESTED_PROJECT_NAME} REQUIRED)
endif()

CPMAddPackage("gh:boost-ext/ut@2.3.1")

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")

target_link_libraries(${PROJECT_NAME} Boost::ut ${TESTED_PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)

# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wpedantic -Wextra -Werror)
  elseif(MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC /W4 /WX)
  endif()
endif()

# ---- Add Tests ----

enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE)
  target_compile_options(${PROJECT_NAME} PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(${PROJECT_NAME} PUBLIC -fprofile-arcs -ftest-coverage)
endif()
