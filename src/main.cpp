#include "vm/vm.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<uint8_t> program = {
        0x01, 0x01, 20,   
        0x01, 0x02, 5, 

        0x03, 0x01, 0x02, 
        0x04, 0x01, 0x02,
        0x05, 0x01, 0x02,

        0xFF
    };

    VM vm;

    vm.load(program);
    vm.run();

    vm.dumpRegisters();

    return 0;
}
