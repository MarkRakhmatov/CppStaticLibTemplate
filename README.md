# CppStaticLib

[![CMake on multiple platforms](https://github.com/MarkRakhmatov/CppStaticLibTemplate/actions/workflows/cmake-multi-platform.yml/badge.svg?branch=main)](https://github.com/MarkRakhmatov/CppStaticLibTemplate/actions/workflows/cmake-multi-platform.yml)

## About
C++ 20 static library template

### By default:
* Warnings as errors
* clang-tidy and cppcheck static analysis
* CPM for dependencies

### It includes

* examples for unit testing using [UT/μt](https://github.com/boost-ext/ut)
* single GitHub action workflow

### It requires

* cmake
* a compiler

### Platforms and compilers support matrix:

| | Windows | Ubuntu     |
|-------|-----|----------|
| MSVC |:heavy_check_mark: | |
| clang | | :heavy_check_mark: |
| gcc | | :heavy_check_mark: |
