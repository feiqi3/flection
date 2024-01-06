#include "generator/generator.hpp"
#include "inja/environment.hpp"
#include "inja/template.hpp"
#include "utils/fileSystemUtils.hpp"
#include "utils/utils.hpp"
#include <iostream>
#include <optional>
#include <string>


namespace flection {
	generator::generator(std::vector<clsDecl>& rawData,std::string& templateDir):TPLdir(templateDir) {
		constructGenData(rawData);
	}
	void generator::constructGenData(std::vector<clsDecl>& rawData) {

		for (auto&& i : rawData) {
			auto& clsItor = data["MetaDataList"][i.name];
			auto nameStr = i.name;
			clsItor["originName"] = i.name;
			utils::hasNamespaceInClsName(nameStr);
			clsItor["clsName"] = nameStr;

			data["ClsNameList"].push_back(nameStr);

			clsItor["filePath"] = i.fileIncluded;
			if (i.base != std::nullopt) {
				clsItor["base"] = i.base.value();
			}
			clsItor["fields"] = nlohmann::json::array();
			for (auto&& j : i.fields) {
				decltype(data) fieldData;
				fieldData["name"] = j.name;
				auto typeNameProcessed = j.type;
				utils::hasNamespaceInClsName(typeNameProcessed);
				fieldData["type"] = j.type;
				clsItor["fields"].push_back(fieldData);
			}
		}
	}

	void flection::generator::CodeRender(const std::string& outPutPath) {
		fsUtils::createDir(outPutPath);
		inja::Environment env;
		inja::Template includeAllTpl = env.parse_template(TPLdir + "/reflection_gen_include_all.template");
		inja::Template renderMetaTpl =
			env.parse_template(TPLdir + "/reflection_gen.template");

		auto includeAllFss = fsUtils::createFile(outPutPath + "/flectionIncludeAll.hpp");
		env.render_to(includeAllFss, includeAllTpl, data);
		includeAllFss.close();

		for (auto&& i : data["MetaDataList"].items()) {
			auto fss = fsUtils::createFile(outPutPath + "/reflection_gen_" +
				i.value()["clsName"].get<std::string>() + ".hpp");
			std::cout << i << std::endl;
			env.render_to(fss, renderMetaTpl, i.value());
			fss.close();
		}
	}} // namespace flection
