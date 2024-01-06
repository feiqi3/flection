#include "utils/fileSystemUtils.hpp"
#include "logWrapper.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <ios>
#include <istream>
#include <optional>
#include <ostream>
#include <regex>
#include <string>
#include <string_view>
namespace flection {

filePaths
fsUtils::recursivGetFile(const std::string &fileAbsolut,
                         const std::optional<fileSuffixFilter> &filter) {
  std::string regex_pattern = "^.*(";
  std::regex pattern;
  if (filter != std::nullopt) {
    fileSuffixFilter processed(filter.value());
    for (auto &&i : processed) {
      fsUtils::regexPrebuilt(i);
    }
    for (auto i = 0; i < processed.size(); ++i) {
      regex_pattern += processed[i];
      regex_pattern += i == processed.size() - 1 ? ")$" : "|";
    }
    pattern = std::regex(regex_pattern);
  }
  std::filesystem::path rootPath(fileAbsolut);
  filePaths ret;
  for (auto &&t : std::filesystem::recursive_directory_iterator(rootPath)) {
    if (t.is_directory()) {
      continue;
    }
    if (filter != std::nullopt &&
        std::regex_search(t.path().string(), pattern)) {
      ret.emplace_back(t.path().root_path().string() +
                       t.path().relative_path().string());
    } else if (filter == std::nullopt) {
      ret.emplace_back(t.path().root_path().string() +
                       t.path().relative_path().string());
    }
  }
  return ret;
}
void fsUtils::regexPrebuilt(std::string &in) {
  for (int i = 0; i < in.size(); ++i) {
    if (in[i] == '.')
      in.insert(i++, "\\", 1);
  }
}
bool fsUtils::createDir(const std::string &fileAbsolut) {
  return std::filesystem::create_directories(fileAbsolut);
}

std::fstream fsUtils::createFile(const std::string &fileAbsolut) {
  return std::fstream(fileAbsolut, std::ios_base::out | std::ios_base::trunc);
}

std::vector<std::string> fsUtils::getConfig(const std::string &in) {

  std::fstream fs(in, std::iostream::in);
  if (!fs.is_open()) {
    FLOG_ERROR("Open Config file error.");
    std::exit(0);
  }
  std::string t;
  std::vector<std::string> ret;
  while (std::getline(fs, t)) {
    ret.push_back(t);
  }
  return ret;
}

} // namespace flection