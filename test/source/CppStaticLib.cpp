#include <doctest/doctest.h>

#include <CppStaticLib/CppStaticLib.hpp>
#include <string>

TEST_CASE("get string") {
  CHECK(csl::GetString() != "");
  CHECK(csl::GetString() == std::string("cpp static lib example"));
  static_assert(csl::factorial_constexpr(0) == 1);
  static_assert(csl::factorial_constexpr(1) == 1);
  static_assert(csl::factorial_constexpr(2) == 2);
}
