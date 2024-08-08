#include <iostream>
#include "ModuleManager.h"

int main(){
    auto mm = ModuleManager();
    mm.loadModule("./build/lib", "basesample");
    std::cout << "Hello" << std::endl;
    std::cout << mm.getModuleList()["basesample"].base->getType();

    
}