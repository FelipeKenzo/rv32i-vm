#include "../include/memory.h"

uint32_t* Memory::read(uint32_t addr) {
    return (uint32_t*) &mem[addr];
}

void Memory::write_b(uint32_t addr, uint8_t data) {
    mem[addr] = data;
}

void Memory::write_w(uint32_t addr, uint32_t data) {
    mem[addr]   = data;
    mem[addr+1] = data>>8;
    mem[addr+2] = data>>16;
    mem[addr+3] = data>>24;
}

Memory::Memory() {
}
