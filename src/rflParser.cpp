#include "rflParser/rflParser.hpp"
#include "clangWrapper/fileUnit.hpp"
#include "rflParser/cursorParser.hpp"
#include "rflParser/reflectionDecl.hpp"
#include "utils/fileSystemUtils.hpp"
#include <optional>
#include <string>

namespace flection {
rflParser::rflParser(int args, const char **argv) {
  for (auto i = 0; i < args; i++) {
    this->compileFlags.emplace_back(std::string(argv[i]));
  }
  /*this->clsMap["int"] = _IntDecl;
  this->clsMap["double"] = _DoubleDecl;
  this->clsMap["float"] = _FloatDecl;
  this->clsMap["short"] = _ShortDecl;
  this->clsMap["std::string"] = _stdStringDecl;
*/
}

rflParser::rflParser(std::vector<std::string>& args) {
  this->compileFlags = args;
}

void rflParser::parseFile(const std::string &fileName) noexcept {
  fileUnit unit(fileName, this->compileFlags, index(1, 0));
  auto root = unit.getRootCursor();
  metaClassParser parser;
  auto metaInfoList = parser.parse(root);
  for (auto &&i : metaInfoList) {
    if (this->clsMap.find(i.name) == this->clsMap.end()) {
      this->clsMap[i.name] = i;
    }
  }
}

void rflParser::setFilter(fileSuffixFilter &list){
  this->filterList = list;
}

void rflParser::parseDirectory(const std::string &dirName
                              ) noexcept {
  auto files = fsUtils::recursivGetFile(dirName, (filterList.size()== 0 ? std::nullopt : std::optional<fileSuffixFilter >(filterList)));
  for (auto &&i : files) {
    this->parseFile(i);
  }
}

std::vector<clsDecl> rflParser::getResult() const {
  std::vector<clsDecl> ret;
  for (auto &&i : this->clsMap) {
    ret.emplace_back(i.second);
  }
  return ret;
}

} // namespace flection