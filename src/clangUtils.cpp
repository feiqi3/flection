#include "utils/clangUtils.hpp"
#include "clang-c/CXString.h"
#include <string>

namespace flection {
std::string clangUtils::getString(const CXString &cxs) {
    std::string ret(clang_getCString(cxs));
    clang_disposeString(cxs);
    return ret;
}

} // namespace flection