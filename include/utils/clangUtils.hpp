#pragma once
#include "clang-c/CXString.h"
#include <string>
#ifndef CLANGUTILS_HPP_
#define CLANGUTILS_HPP_

namespace flection {
    class clangUtils{
        public:
        static std::string getString(const CXString& cxs);
    };
}

#endif