#include "vm.hpp"

#include <stdexcept>
#include <iostream>

enum Opcode : uint8_t {
    OP_MOV = 0x01,
    OP_ADD = 0x02,
    OP_HLT = 0xFF,
};

void VM::reset() {
    ip = 0;
    running = false;

    for (size_t i = 0; i < 8; i++) {
        registers[i] = 0;
    }
}

void VM::validateRegister(uint8_t reg) const {
    if (reg >= 8) {
        throw std::runtime_error("Invalid register index");
    }
}

void VM::load(const std::vector<uint8_t>& program) {
    memory = program;
    reset();
}

uint8_t VM::readByte() {
    if (ip >= memory.size()) {
        throw std::runtime_error("Unexpected end of program");
    }

    return memory[ip++];
}

uint8_t VM::getRegister(size_t index) const {
    if (index >= 8) {
        throw std::runtime_error("Invalid register index");
    }

    return registers[index];
}

void VM::dumpRegisters() const {
    for (size_t i = 0; i < 8; i++) {
        std::cout << "r" << i
                  << " = "
                  << (int)registers[i]
                  << "\n";
    }
}

void VM::run() {
    running = true;

    while (running && ip < memory.size()) {
        uint8_t opcode = readByte();

        switch (opcode) {

        case OP_MOV: {
            uint8_t reg = readByte();
            uint8_t value = readByte();

            validateRegister(reg);

            registers[reg] = value;
            break;
        }

        case OP_ADD: {
            uint8_t dest = readByte();
            uint8_t src = readByte();

            validateRegister(dest);
            validateRegister(src);

            registers[dest] += registers[src];
            break;
        }

        case OP_HLT:
            running = false;
            break;

        default:
            throw std::runtime_error("Unknown opcode");
        }
    }
}
