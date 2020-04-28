#ifndef RV32I_H
#define RV32I_H

#include <cstdint>
#include <iostream>
#include <string>
#include <iomanip>

#include "../include/memory.h"

class RV32i {
    bool halt = false;
    bool verbose;
    
    // Registers
    uint32_t reg[33] = {0}; // 32 general purpose + pc
    enum {pc = 32};

    // Memory
    Memory* mem;

    // Private utilities
    uint32_t signExtend(uint32_t data, uint8_t size);
    uint32_t twosComplement(uint32_t data);

    void executeInstr(uint32_t instr);

    public:
    RV32i(Memory* mem, bool verbose);
    void run(uint32_t origin);
    void run(uint32_t origin, int maxcount); // run maxcount instructions

    // Public Utilities
    void printRegisters();
    void printRegister(int i);
    void setRegister(uint8_t i, uint32_t data);

};

#endif