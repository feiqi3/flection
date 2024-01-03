#pragma once
#ifndef CURSORPARSER_HPP_
#define CURSORPARSER_HPP_
#include <optional>
#include "clang-c/Index.h"
#include "metaDefs.hpp"
#include "reflectionDecl.hpp"
#include "clangWrapper/cursorWrapper.hpp"
#include "rflParser/reflectionDecl.hpp"
#include <string>
#include <vector>
#include <unordered_map>
namespace flection {

    class metaClassParser{
        public:
        metaClassParser();
        ~metaClassParser(){};
        std::vector<clsDecl> parse(const flection::cursor& root);
        private:
        CursorList findClassCursorWithMetaInfo() const noexcept;
        CursorList findChildrenCursorWithMetaInfo() const noexcept;
        std::optional<clsDecl> clsMetaCursorParse(const cursor&)const;
        funcDecl funcCursorParse(const cursor&)const;
        fieldDecl fieldCursorParse(const cursor&)const;
    };
}

#endif