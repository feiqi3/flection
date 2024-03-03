#include "fileA.hpp"
#include "flection/flection.hpp"
#include "metaGen/flectionIncludeAll.hpp"
#include <iostream>

int main() {
  flection::rflRegister::registerAll();
  students stu{123,"Hello"};
  auto type = flection::flection::getType("students");
  auto fields = type->getFieldList();
  for (auto& i : fields) {
    std::cout<<i->getFieldName()<<" "<<i->getTypeName()<<"\n";
  }
}