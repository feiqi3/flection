#include "fileA.hpp"
#include "metaGen/flectionIncludeAll.hpp"
#include "flection/flection.hpp"
#include <iostream>

int main() {
  flection::rflRegister::registerAll();
  students stuA{202010311222, "Unknown"};
  auto t = flection::flection::getType("students")->getField("uid");
  long long uidNew = 202010311225;
  (*t).setValue(&stuA, &uidNew);
  std::cout << stuA.uid<<"\n";

  auto fieldList = flection::flection::getType("students")->getFieldList();
  std::cout<<"Class students has "<<fieldList.size()<<" fields\n";
  for(auto&& i :fieldList){
    std::cout<<i->getFieldName()<<" -> "<<i->getTypeName()<<"\n";
  }
}