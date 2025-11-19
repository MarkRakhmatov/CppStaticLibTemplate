#include <boost/ut.hpp>

#include <CppStaticLib/CppStaticLib.hpp>
#include <string>


int main() {
  using namespace boost::ut;

  "get string"_test = [] {
    expect(!csl::getString().empty());
    expect(csl::getString() == std::string("cpp static lib example"));
  };

  "get number"_test = [] {
    expect(csl::getNumber() == 2);
  };

  "factorial_constexpr"_test = [] {
    static_assert(csl::factorialConstexpr(0) == 1);
    static_assert(csl::factorialConstexpr(1) == 1);
    static_assert(csl::factorialConstexpr(2) == 2);
  };
}
