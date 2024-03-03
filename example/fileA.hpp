#pragma once

#include "metaDefs.hpp"
#include <string>

class RFL_CLASS() students{
    public:
    students(long long _uid,std::string name){
        uid = _uid;
        this->name = name;
        PrivateInfo = "Private";
    }
    RFL_ALL(students);
    public:
    RFL_PROPERTY()
    long long uid;
    RFL_PROPERTY()
    std::string name;
    private:
    RFL_PROPERTY()
    std::string PrivateInfo;
    RFL_PROPERTY()
    students* stu;
};




