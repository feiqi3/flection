#include "CLI11.hpp"
#include "clangWrapper/cursorWrapper.hpp"
#include "logWrapper.hpp"
#include "rflParser/cursorParser.hpp"
#include "rflParser/rflParser.hpp"
#include "utils/fileSystemUtils.hpp"
#include "utils/utils.hpp"
#include "clang-c/CXString.h"
#include "clang-c/Index.h"
#include <chrono>
#include <cstddef>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

int main(int argc, const char **argv) {

  if (argc <= 1) {
    FLOG_ERROR("Fatal error: no input files.");
    return 0;
  }
  auto argsVec = flection::utils::splitStringBySpace(argv[1]);
  std::string parseDir = argsVec[0];
  argsVec.erase(argsVec.begin());
  for (int i = 2; i < argc; ++i) {
    argsVec.push_back(std::string(argv[i]));
  }

  flection::rflParser parser(argsVec);
  parser.parseDirectory(parseDir);
  auto parseResult = parser.getResult();
  for (auto &&i : parseResult) {
    std::cout << i;
  }
}
