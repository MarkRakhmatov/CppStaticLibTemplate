#pragma once
#include <string>

/*! \mainpage CppStaticLib
 *
 * \section intro_sec Introduction
 *
 * This project simplify creation of C++ static libraries and provides basic tooling.
 *
 */

/*! \brief Example namespace that contains static library functions
 *
 *    *  Detailed description of namesace
 */
namespace csl {
  /*! \brief Example function that returns string.
   *
   *    *  Detailed description of function
   *
   *  \return hardcoded string
   */
  std::string getString();

  /*! \brief Example compile time factorial function
   *
   *    *  Detailed description of function
   *
   *  \param input: integer
   *  \return factorial of input
   */
  constexpr int factorialConstexpr(int input) noexcept {
    if (input < 2) {
      return 1;
    }

    return input * factorialConstexpr(input - 1);
  }

  /*! \brief Example runtime time factorial function
   *
   *    *  Detailed description of function
   *
   *  \param input: integer
   *  \return factorial of input
   */
  int factorial(int input) noexcept;

  /*! \brief Example of function not covered with test
   *
   *    * Testing is important for quality of software.
   *    * This function left uncovered just to simplify usage of this project as template.
   *    * CI configured to require 60% code coverage and not allows decrease of coverage.
   *    * If your project has no tests you can temporarily change CI,
   *    see .github/workflows/ci.yml 'Coverage - Check' fail_min and fail_diff_decrease options
   *
   *  \param value: integer value
   *  \return some integer value
   */
  int uncoveredFunction(int value) noexcept;
}  // namespace csl
