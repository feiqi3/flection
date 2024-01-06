#include "clangWrapper/cursorWrapper.hpp"
#include "generator/generator.hpp"
#include "inja/parser.hpp"
#include "logWrapper.hpp"
#include "rflParser/cursorParser.hpp"
#include "rflParser/rflParser.hpp"
#include "utils/fileSystemUtils.hpp"
#include "utils/utils.hpp"
#include "clang-c/CXString.h"
#include "clang-c/Index.h"
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>
#include"utils/clangUtils.hpp"
int main(int argc, const char** argv) {
	if(argc == 1){
		std::cout<<"Usage: run with path of config file.";
		std::exit(0);
	}
	std::string configPath = argv[1];
	auto configVec = flection::fsUtils::getConfig(configPath);
	auto templateDir = configVec[0];
	auto parseDir = configVec[1];
	auto outPutDir = configVec[2];
	configVec.erase(configVec.begin(),configVec.begin()+3);

	flection::rflParser parser(configVec);

	FLOG_INFO("Parse begin.");

	auto beginTime = std::chrono::system_clock::now();

	parser.parseDirectory(parseDir);

	auto parseRes = parser.getResult();

	for (auto&& i : parseRes) {
		std::cout << i;
	}

	auto timeTaken = std::chrono::system_clock::now() - beginTime;

	FLOG_INFO("Parse end. Time used: {}s. ", std::chrono::duration_cast<std::chrono::milliseconds>(timeTaken).count() / 1000.);

	flection::generator gen(parseRes,templateDir);

	gen.CodeRender(outPutDir);

}
