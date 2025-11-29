#include <boost/ut.hpp>
#include "fuzztest/fuzztest.h"

#include <CppStaticLib/CppStaticLib.hpp>
#include <iostream>
#include <cstdlib>
#include <exception>

void factorialAlwaysGreaterThan0(int input) {
  using namespace boost::ut;

  "factorial"_test = [input] {
    expect(csl::factorial(input) > 0);
  };
}

FUZZ_TEST(TestSuite, factorialAlwaysGreaterThan0);

int main() {
  try {
    factorialAlwaysGreaterThan0(5);
  } catch (const std::exception& ex) {
    std::cout << "exception: "<< ex.what();
    return EXIT_FAILURE;
  }
  catch (...) {
    std::cout <<"unknown exception";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
