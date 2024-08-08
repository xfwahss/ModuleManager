#include<string>
#include <algorithm>
#include "../templates/Reactor.h"
class Module1 : public Reaction {
  std::string readLine(const std::string &str) override {
      std::string str2(str);
      std::transform(str.begin(), str.end(), str2.begin(), ::toupper);
      return str2;
  }
  std::string getType() const override{
    return std::string(Reaction::name) + std::string("Moduel");

  };
};

//必须实现 moduleName_create 函数,来初始化对象
extern "C" Base *basesample_create() {
    return new Module1;
}

//必须实现 moduleName_destroy 函数,来回收对象
extern "C" void basesample_destroy(Base *obj) {
    delete obj;
}