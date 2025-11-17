#pragma once
#include <string>

namespace csl {
  std::string GetString();

  constexpr int factorial_constexpr(int input) noexcept {
    if (input < 2) {
      return 1;
    }

    return input * factorial_constexpr(input - 1);
  }
}  // namespace csl
