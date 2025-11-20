#include <boost/ut.hpp>

#include <CppStaticLib/CppStaticLib.hpp>
#include <string>


int main() {
  using namespace boost::ut;

  "get string"_test = [] {
    expect(!csl::getString().empty());
    expect(csl::getString() == std::string("cpp static lib example"));
  };

  "factorial"_test = [] {
    expect(csl::factorial(0) == 1);
    expect(csl::factorial(1) == 1);
    expect(csl::factorial(2) == 2);
  };

  "factorial_constexpr"_test = [] {
    static_assert(csl::factorialConstexpr(0) == 1);
    static_assert(csl::factorialConstexpr(1) == 1);
    static_assert(csl::factorialConstexpr(2) == 2);
  };
}
