#pragma once

#include <cstdint>
#include <vector>

class VM {
public:
    void load(const std::vector<uint8_t>& program);
    void run();

    uint8_t getRegister(size_t index) const;
    void dumpRegisters() const;

private:
    uint8_t readByte(); 

    std::vector<uint8_t> memory;
    uint8_t registers[8] = {0};

    size_t ip = 0;
    bool running = false;
};
