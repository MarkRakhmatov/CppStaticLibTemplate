# %%myproject%%

[![ci](https://github.com/%%myorg%%/%%myproject%%/actions/workflows/ci.yml/badge.svg)](https://github.com/%%myorg%%/%%myproject%%/actions/workflows/ci.yml)

## About %%myproject%%
%%description%%

### By default:
* Warnings as errors
* clang-tidy and cppcheck static analysis
* CPM for dependencies

### It includes

* unit testing using [UT/μt](https://github.com/boost-ext/ut)
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
