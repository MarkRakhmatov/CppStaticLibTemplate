#include <boost/ut.hpp>
#include "fuzztest/fuzztest.h"
#include "fuzztest/init_fuzztest.h"
#include "absl/debugging/failure_signal_handler.h"
#include "absl/debugging/symbolize.h"

#include <CppStaticLib/CppStaticLib.hpp>
#include <iostream>
#include <cstdlib>
#include <exception>

void factorialAlwaysGreaterThan0(int) {
  using namespace boost::ut;

  "factorial"_test = [] {
    expect(csl::factorial(0) > 0);
    // expect(csl::factorial(input) > 0);
  };
}

FUZZ_TEST(TestSuite, factorialAlwaysGreaterThan0);


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
    initFuzztest(argc, argv);
    factorialAlwaysGreaterThan0(5);
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
