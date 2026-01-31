#include <string>
#include "CppStaticLib/CppStaticLib.hpp"


namespace csl {

  /*!
   * \brief max input value that will not cause 32 bit integer overflow
   *
   * issue was found using fuzz test
   */
  constexpr int gMaxIntFactorialInput = 12;

  std::string getString() { return "cpp static lib example"; }

  int factorial(int input) noexcept {
    if (input > gMaxIntFactorialInput) {
      return -1;
    }

    if (input < 2) {
      return 1;
    }

    return input * factorial(input - 1);
  }

  int uncoveredFunction(int value) noexcept {
    if(value > 0) {
      return 1;
    }

    return -1;
  }

}  // namespace csl
