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
* tooling to verify consistent commits format inspired by [conventional commits](https://www.conventionalcommits.org/en/v1.0.0/)
* autocreation of [version](https://semver.org/) tags in main branch based on commits
* [Documentation](https://markrakhmatov.github.io/CppStaticLibTemplate/) powered by [doxygen](https://www.doxygen.nl), [graphviz](https://www.graphviz.org/) and [doxygen-awesome-css
](https://github.com/jothepro/doxygen-awesome-css)

  Publishing of documentation to Gitpub Pages, enabled by default(see 'Deploy Pages' job in [CI](https://github.com/%%myorg%%/%%myproject%%/blob/main/.github/workflows/ci.yml)), cofigure repository to enable Pages with "Github Actions" source.
To build documentation locally, install doxygen and graphviz, set CMake variable %%myproject%%_DOC.
If doxygen not found, set %%myproject%%_DOXYGEN_SEARCH_PATHS to directory contaning doxygen binaries.
If dot (graphviz utility) not found, set %%myproject%%_GRAPHVIZ_BIN_PATHS to directory contaning graphviz binaries.

#### Commits format

1. API breaking change (will increment major version)
For example: removal of public interface parts after introducing new version of API
Please, provide short description with reasons and migration hints if needed
```
api: remove deprecated v1 API
api(parser): hide parser API from public interface
```

2. New feature or backward compatible API change (will increment minor version and reset patch to 0)
```
feat: introduce parser v2 API
feat(parser): extend parser v2 API public interface
```

3. Fix of bug in existing logic
```
fix: bug with list parsing in v2 API
refactor(parser): reduce heap allocations in parser v2 API
```

### It requires

* cmake
* a compiler

### Platforms and compilers support matrix:

| | Windows | Ubuntu     |
|-------|-----|----------|
| MSVC |:heavy_check_mark: | |
| clang | | :heavy_check_mark: |
| gcc | | :heavy_check_mark: |

### Usage
1. Click on 'Use this template', select 'Create a new repository'
2. After initial commit, template janitor action triggered to cleanup repo (rename files, replace readme, verify that build works)
3. Clone new repository, rename 'csl' namespace, write your code
4. Publishing of documentation to Gitpub Pages, enabled by default(see 'Deploy Pages' job in [CI](https://github.com/%%myorg%%/%%myproject%%/blob/main/.github/workflows/ci.yml)), cofigure repository to enable Pages with "Github Actions" source
5. Commit your changes to main, use [conventional commits](https://www.conventionalcommits.org/en/v1.0.0/) (for example 'feat: initial commit')
6. Wait for CI to complete and create version 0.1.0 of your library

Congrats, now you can focus on your code
