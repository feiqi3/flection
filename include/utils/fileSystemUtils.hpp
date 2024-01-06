#pragma once
#include <optional>
#include <ostream>
#ifndef FILESYSTEMUTILS_HPP_
#define FILESYSTEMUTILS_HPP_

#include <filesystem>
#include <functional>
#include <string>
#include <vector>


namespace flection {
typedef std::vector<std::string> fileSuffixFilter;
typedef std::vector<std::string> filePaths;
class fsUtils {
    public:
  // like {".hpp",".cpp"} macth files with extension .hpp,.cpp or {"hello","hi"}
  // => match all files with suffix hello hi
  // get a list of files' absolute path to root
  static filePaths recursivGetFile(const std::string &rootAbsolute,
                                   const std::optional<fileSuffixFilter> &filter = std::nullopt);
  static bool createDir(const std::string &fileAbsolut);
  static std::fstream createFile(const std::string &fileAbsolut);
  static std::vector<std::string> getConfig(const std::string& in);
    private:
    static void regexPrebuilt(std::string&);
};
} // namespace flection

#endif