#include <boost/ut.hpp>

#include <CppStaticLib/CppStaticLib.hpp>
#include <string>


int main() {
  using namespace boost::ut;

  "get string"_test = [] {
    expect(!csl::GetString().empty());
    expect(csl::GetString() == std::string("cpp static lib example"));
  };

  "factorial_constexpr"_test = [] {
    static_assert(csl::factorial_constexpr(0) == 1);
    static_assert(csl::factorial_constexpr(1) == 1);
    static_assert(csl::factorial_constexpr(2) == 2);
  };
}
