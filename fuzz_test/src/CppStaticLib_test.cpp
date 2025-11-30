#include <boost/ut.hpp>
#include "fuzztest/fuzztest.h"
#include "fuzztest/init_fuzztest.h"
#include "absl/debugging/failure_signal_handler.h"
#include "absl/debugging/symbolize.h"

#include <CppStaticLib/CppStaticLib.hpp>
#include <iostream>
#include <cstdlib>
#include <exception>
#include <filesystem>

using namespace boost::ut;

void unitTests() {
  "ut_factorial_3"_test = [] {
    expect(csl::factorial(3) == 6_i);
  };
}

void factorialAlwaysGreaterThan0OrInvalid(int) {
}

FUZZ_TEST(TestSuite, factorialAlwaysGreaterThan0OrInvalid);


void initFuzztest(int argc, char** argv, std::string_view binary_id) {
  absl::InitializeSymbolizer(argv[0]);
  absl::FailureSignalHandlerOptions options;
  options.call_previous_handler = true;
  absl::InstallFailureSignalHandler(options);
  // We call fuzztest::ParseAbslFlags rather than absl::ParseCommandLine
  // since the latter would complain about any unknown flags that need
  // to be passed to legacy fuzzing engines (e.g. libfuzzer).
  fuzztest::ParseAbslFlags(argc, argv);
  fuzztest::InitFuzzTest(&argc, &argv, binary_id);
}

void runFuzztests(std::string_view binary_id) {
  for (const auto& name: fuzztest::ListRegisteredTests()) {
    fuzztest::RunSpecifiedFuzzTest(name, binary_id);
  }
}

int main(int argc, char** argv) {
  try {
    const char* exePath = argv[0];
    std::filesystem::path fullPath{exePath};
    auto binary_id = fullPath.filename().string();
    boost::ut::detail::cfg::parse_arg_with_fallback(argc, const_cast<const char**>(argv));
    unitTests();

    initFuzztest(argc, argv, binary_id);
    runFuzztests(binary_id);
  } catch (const std::exception& ex) {
    std::cout << "exception: "<< ex.what();
    return EXIT_FAILURE;
  }
  catch (...) {
    std::cout <<"unknown exception";
    return EXIT_FAILURE;
  }

  std::cout <<"Success";
  return EXIT_SUCCESS;
}
