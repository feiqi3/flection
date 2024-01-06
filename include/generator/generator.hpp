#pragma once
#include "inja/inja.hpp"
#include "rflParser/reflectionDecl.hpp"
#include <string>
#ifndef GENERATOR_HPP_
#define GENERATOR_HPP_

namespace flection {
class generator {
public:
  generator(std::vector<clsDecl>& rawData,std::string& templateDir);
  void CodeRender(const std::string &outPutPath);

private:
  void constructGenData(std::vector<clsDecl> &rawData);
  std::string TPLdir;
  inja::json data;
};
} // namespace flection

#endif