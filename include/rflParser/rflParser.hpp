#ifndef RFLPARSER_HPP_
#define RFLPARSER_HPP_

#include "rflParser/reflectionDecl.hpp"
#include "utils/fileSystemUtils.hpp"
#include <string>
#include <unordered_map>
#include <vector>
namespace flection {

	class rflParser {
	public:
		rflParser() {}
		rflParser(int args, const char** argv);
		rflParser(std::vector<std::string>& args);
		void parseFile(const std::string& filename)noexcept;
		void parseDirectory(const std::string& dirName)noexcept;
		std::vector<clsDecl> getResult()const;
		void setFilter(fileSuffixFilter& list);
	private:
		std::vector<std::string> compileFlags;
		fileSuffixFilter filterList;
		std::unordered_map<std::string, clsDecl> clsMap;
	};
}

#endif