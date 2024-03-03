#pragma once

#ifndef REFLECTION_HPP_
#define REFLECTION_HPP_
#include "metaDefs.hpp"
#include <functional>
#include <optional>
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
  static void register2Flection(Type *type);
};

class flection {
public:
  static std::optional<Type> getType(const std::string &tname);
  friend rflRegisterHelper;

private:
  static std::unordered_map<std::string, Type *> metaMap;
};

} // namespace flection

namespace flection {
inline std::string Field::getFieldName() { return std::get<0>(*_funcTuple)(); }
inline std::string Field::getTypeName() { return std::get<1>(*_funcTuple)(); }
inline void Field::setValue(void *a, void *b) const {
  return std::get<2>(*_funcTuple)(a, b);
}
inline void *Field::getValue(void *a) const { return std::get<3>(*_funcTuple)(a); }

inline std::string Type::getTypeName() { return std::get<0>(*this->funcs)(); }

inline void rflRegisterHelper::fieldRegister(Type *type, fieldFuncTuple *func) {
  auto tmp_field = new Field;
  tmp_field->_funcTuple = func;
  type->fieldList.push_back(tmp_field);
}

inline void rflRegisterHelper::typeRegister(Type *type, typeFuncTuple *func) {
  type->funcs = func;
}

inline void rflRegisterHelper::register2Flection(Type *type) {
  flection::metaMap[type->getTypeName()] = type;
}

inline std::optional<Type> flection::getType(const std::string &tname) {
  auto t = metaMap.find(tname);
  if (t != metaMap.end()) {
    return *t->second;
  }
  return std::nullopt;
}

inline const Field *const Type::getField(const std::string &s) {
  auto ret = std::find_if(fieldList.begin(), fieldList.end(), [s](Field *a) {
    if (a->getFieldName() == s) {
      return 1;
    }
    return 0;
  });
  if (ret != fieldList.end()) {
    return *ret;
  }
  return nullptr;
}

inline std::unordered_map<std::string, Type *> flection::metaMap;

} // namespace flection

#endif
