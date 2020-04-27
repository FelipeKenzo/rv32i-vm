#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <iostream>
#include <string>

class Memory {
    private:
    // Memory (note: Little-Endian)
    uint8_t mem[UINT16_MAX] = {0}; // 65 KB of memory (up to 4GB)

    public:
    Memory();
    uint32_t* read(uint32_t addr);
    void write_b(uint32_t addr, uint8_t data);
    void write_w(uint32_t addr, uint32_t data);
};

#endif