#include <boost/ut.hpp>
#include "fuzztest/fuzztest.h"
#include "fuzztest/init_fuzztest.h"
#include "absl/debugging/failure_signal_handler.h"
#include "absl/debugging/symbolize.h"

#include <CppStaticLib/CppStaticLib.hpp>
#include <iostream>
#include <cstdlib>
#include <exception>

using namespace boost::ut;

void unitTests() {
  "ut_factorial_3"_test = [] {
    expect(csl::factorial(3) == 6_i);
  };
}

void factorialAlwaysGreaterThan0OrInvalid(int input) {
  using namespace boost::ut;
  test(" factorial_" + std::to_string(input)) = [input] {
    auto r = csl::factorial(input);
    expect(r > 0_i or r == -1_i) << "factorial output should be positive or invalid (-1)";
  };
}

FUZZ_TEST(TestSuite, factorialAlwaysGreaterThan0OrInvalid);


void initFuzztest(int argc, char** argv) {
  absl::InitializeSymbolizer(argv[0]);
  absl::FailureSignalHandlerOptions options;
  options.call_previous_handler = true;
  absl::InstallFailureSignalHandler(options);
  // We call fuzztest::ParseAbslFlags rather than absl::ParseCommandLine
  // since the latter would complain about any unknown flags that need
  // to be passed to legacy fuzzing engines (e.g. libfuzzer).
  fuzztest::ParseAbslFlags(argc, argv);
  fuzztest::InitFuzzTest(&argc, &argv);
}

void runFuzztests() {
  for (const auto& name: fuzztest::ListRegisteredTests()) {
    fuzztest::RunSpecifiedFuzzTest(name, {});
  }
}

int main(int argc, char** argv) {
  try {
    boost::ut::detail::cfg::parse_arg_with_fallback(argc, const_cast<const char**>(argv));
    unitTests();

    initFuzztest(argc, argv);
    runFuzztests();
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
