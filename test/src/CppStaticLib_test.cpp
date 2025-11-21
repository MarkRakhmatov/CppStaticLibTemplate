#include <boost/ut.hpp>

#include <CppStaticLib/CppStaticLib.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include <exception>

void tests() {
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

int main() {
  try {
    tests();
  } catch (const std::exception& ex) {
    std::cout << "exception: "<< ex.what();
    return EXIT_FAILURE;
  }
  catch (...) {
    std::cout <<"unknown exception";
    return EXIT_FAILURE;
  }
}
