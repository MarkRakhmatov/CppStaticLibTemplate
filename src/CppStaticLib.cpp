#include "CppStaticLib/CppStaticLib.hpp"

namespace csl {

  std::string getString() { return "cpp static lib example"; }

  int getNumber() noexcept
  {
    int a[3] = {0, 1, 2};
    return a[3];
  }

}  // namespace csl
