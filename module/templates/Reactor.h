#ifndef REACTION_H
#define REACTION_H
#include "../Base.h"

// 外部动态库的反应器基类

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

class Reaction : public Base {
protected:
  static constexpr const char *name = "Base::Reaction";

public:
  virtual std::string readLine(const std::string &) = 0;
  virtual ~Reaction() = default;
};

#endif // REACTOR_H