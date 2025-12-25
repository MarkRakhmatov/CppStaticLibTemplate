# CppStaticLib

[![ci](https://github.com/MarkRakhmatov/CppStaticLibTemplate/actions/workflows/ci.yml/badge.svg)](https://github.com/MarkRakhmatov/CppStaticLibTemplate/actions/workflows/ci.yml)

## About
C++ 23 static library template

### By default:
* Warnings as errors
* clang-tidy and cppcheck static analysis
* [CPM](https://github.com/cpm-cmake/CPM.cmake) for dependencies

### It includes

* unit testing using [UT/μt](https://github.com/boost-ext/ut)
* fuzz testing using [fuzztest](https://github.com/google/fuzztest)
* autocreation of tags in main branch (commit title should contain version number, for example `0.1.0`)

### It requires

* cmake
* a compiler

### Platforms and compilers support matrix:

| | Windows | Ubuntu     |
|-------|-----|----------|
| MSVC |:heavy_check_mark: | |
| clang | | :heavy_check_mark: |
| gcc | | :heavy_check_mark: |
