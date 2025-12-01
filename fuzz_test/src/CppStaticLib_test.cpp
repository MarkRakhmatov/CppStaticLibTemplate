#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include "absl/debugging/failure_signal_handler.h"
#include "absl/debugging/symbolize.h"

#include <CppStaticLib/CppStaticLib.hpp>
#include <cstdlib>

void factorialAlwaysGreaterThan0OrInvalid(int i) {
  auto res = csl::factorial(i);
  EXPECT_TRUE(res > 0 || res == -1 );
}

TEST(FactorialFuzzTestSuite, factorial2) {
  EXPECT_EQ(csl::factorial(2), 2);
}

FUZZ_TEST(FactorialFuzzTestSuite, factorialAlwaysGreaterThan0OrInvalid);


