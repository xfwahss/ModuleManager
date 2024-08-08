#ifndef MODULE_MANAGER_H
#define MODULE_MANAGER_H
// load the header from the operating system
#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

// load the header used
#include "../module/Base.h"
#include <iostream>
#include <map>
#include <string>

// 声明创建对象的函数
typedef Base *(*create)();
// 声明回收对象的函数
typedef void (*destroy)(Base *);

struct Module {
#ifdef _WIN32
  HINSTANCE handle;
#else
  void *handle;
#endif
  Base *base;
};

/*
 * load the module base template
 */
class ModuleManager {
private:
  std::map<std::string, Module> moduleDict;

public:
#ifdef _WIN32
  HINSTANCE loadLib(Base **base, const char *path, const char *funName) {
    auto handle = LoadLibrary(path);
    if (!handle) {
      return nullptr;
    }
    // 读取的是一个创建对象的函数。。。。
    auto cr = (create)GetProcAddress(handle, funName);
    if (cr) {
      *base = cr();
    }
    return handle;
  }

  // 调用系统函数,卸载动态库
  void freeLib(HINSTANCE handle, Base *obj, const char *funName) {
    auto free = (destroy)GetProcAddress(handle, funName);
    if (free) {
      free(obj);
    }
    FreeLibrary(handle);
  }
#else
  void *loadLib(Base **base, const char *path, const char *funName) {
    auto handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
      return nullptr;
    }
    auto cr = (create)dlsym(handle, funName);
    if (cr) {
      *base = cr();
    }
    return handle;
  };

  // 调用系统函数,卸载动态库
  void freeLib(void *handle, Base *obj, const char *funName) {
    auto free = (destroy)dlsym(handle, funName);
    if (free) {
      free(obj);
    }
    dlclose(handle);
  }
#endif

  bool loadModule(const std::string &moduleDir, const std::string &moduleName) {
    std::string libPath;
#ifdef _WIN32
    libPath = std::string(moduleDir + "/lib" + moduleName + ".dll");
#else
    libPath = std::string(moduleDir + "/lib" + moduleName + ".so");
#endif
    Base *module = nullptr;
    auto handle = loadLib(&module, libPath.c_str(),
                          std::string(moduleName + "_create").c_str());
    if (!module) {
      std::cout << "load lib" << moduleName << " fail" << std::endl;
      return false;
    }
    if (moduleDict.find(moduleName) != moduleDict.end()) {
      unloadModule(moduleName);
    }
    moduleDict[moduleName] = Module{handle, module};
    return true;
  };

  void unloadModule(const std::string &moduleName) {
    auto module = moduleDict.find(moduleName);
    if (module == moduleDict.end()) {
      return;
    }
    freeLib(module->second.handle, module->second.base,
            std::string(moduleName + "_destroy").c_str());
  };
  std::map<std::string, Module> getModuleList() { return moduleDict; }
};

#endif