#include <string>
#include "CppStaticLib/CppStaticLib.hpp"


namespace csl {

  std::string getString() { return "cpp static lib example"; }

  int factorial(int input) noexcept {
    if (input < 2) {
      return 1;
    }

    const int max = 1000;

    if (input > max) {
      return -1;
    }


    return input * factorial(input - 1);
  }

}  // namespace csl
