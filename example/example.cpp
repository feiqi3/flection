#include "fileA.hpp"
#include "metaGen/flectionIncludeAll.hpp"
#include "rfl/reflection.hpp"
#include <iostream>

int main() {
  flection::rflRegister::registerAll();
  students stuA{202010311222, "Unknown"};
  auto t = flection::flection::getType("students")->getField("uid");
  long long uidNew = 202010311225;
  (*t).setValue(&stuA, &uidNew);
  std::cout << stuA.uid;
}