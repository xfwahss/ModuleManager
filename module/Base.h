//
// Created by xfwahss on 2024-8-8.
//
#ifndef BASE_H
#define BASE_H
#include <string>

/**
 * 必须实现 moduleName_create 函数,来初始化对象
 * extern "C" Base *module1_create() {
 *     return new Module;
 * }
 *
 * //必须实现 moduleName_destroy 函数,来回收对象
 * extern "C" void module1_destroy(Base *obj) {
 *     delete obj;
 * }
 */

class Base {
protected:
  static constexpr const char *name = "Base";

public:
  virtual std::string getType() const = 0;
  virtual ~Base() = default;
};

#endif