#pragma once
#include <sys/stat.h>
#include <vector>
#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
namespace flection {

class utils{
    public: 
    static std::vector<std::string> splitStringBySpace(const std::string& str){
        std::vector<std::string> ret;
        int last = 0;int count = 0;
        for (int i = 0; i < str.size(); ++i,count++) {
            if(str[i]==' '){
                ret.push_back(str.substr(last,count));
                count = -1;
                last = i+1;
            }
        }
        ret.push_back(str.substr(last,count));
        return ret;;
    }
};
}

#endif