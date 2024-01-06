#pragma once

#ifndef REFLECTION_HPP_
#define REFLECTION_HPP_
#include "metaDefs.hpp"
#include <optional>
#include <functional>
#include <string>
#include <vector>
namespace flection {

typedef std::function<std::string()> getFieldNameFunc;
typedef std::function<std::string()> getTypeNameFunc;
typedef std::function<void(void *, void *)> setFunc;
typedef std::function<void *(void *)> getFunc;
typedef std::tuple<getFieldNameFunc, getTypeNameFunc, setFunc, getFunc>
    fieldFuncTuple;
typedef std::tuple<getTypeNameFunc> typeFuncTuple;


class Field {
public:
  std::string getFieldName();
  std::string getTypeName();
  void setValue(void *a, void *b) const;
  void *getValue(void *a) const;
public:
  Field() {}
  friend class rflRegisterHelper;
private:
  fieldFuncTuple *_funcTuple;
};

class Type {
public:
  std::string getTypeName();
  const std::vector<Field *> &getFieldList() { return fieldList; }
 const Field *const getField(const std::string &s);
  friend class rflRegisterHelper;

private:
  typeFuncTuple *funcs;
  std::vector<Field *> fieldList;
};

class rflRegisterHelper {
public:
  static void fieldRegister(Type *type, fieldFuncTuple *func);
  static void typeRegister(Type *type, typeFuncTuple *func);
  static void register2Flection(Type* type);
};

class flection {
public:
  static std::optional<Type> getType(const std::string &tname);
  friend rflRegisterHelper;
private:
  static std::unordered_map<std::string, Type *> metaMap;
};

} // namespace flection

#include "reflection_impl"

#endif