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
    void reset();
    uint8_t readByte(); 
    void validateRegister(uint8_t reg) const;

    std::vector<uint8_t> memory;
    uint8_t registers[8] = {0};

    size_t ip = 0;
    bool running = false;
};
