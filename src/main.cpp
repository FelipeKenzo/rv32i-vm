#include <cstdint>
#include <iostream>
#include <string>

#include "../include/rv32i.h"
#include "../include/memory.h"

int main (int argc, char* argv[]) {
    // Arguments Parsing
    bool verbose = false;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-v" || arg == "--verbose") {
            verbose = true;
            std::cout << "Running in Verbose mode.\n\n";
        }
    }

    Memory mem = Memory();
    RV32i proc = RV32i(&mem, verbose);
    
    proc.setRegister(1, 0xF0000010);
    proc.setRegister(2, 0xF000F010);
    proc.setRegister(3, 0x0C0A0010);
    proc.setRegister(4, 0x00003050);
    proc.setRegister(5, 0x0000FFAF);
    proc.setRegister(6, 0xC0001234);
    proc.setRegister(7, 0xC0000008);

    
    // Tests:
    // Register-Immediate Operations:
    mem.write_w(0x00, 0xAAA10113); // ADDI com overflow
    mem.write_w(0x04, 0xAAA1A113); // SLTI
    mem.write_w(0x08, 0xAAA1B113); // SLTIU
    mem.write_w(0x0C, 0x0AA2C113); // XORI
    mem.write_w(0x10, 0x0AA2E113); // ORI
    mem.write_w(0x14, 0x0FF2F113); // ANDI
    mem.write_w(0x18, 0x00429113); // SLLI
    mem.write_w(0x1C, 0x00435113); // SRLI
    mem.write_w(0x20, 0x40435113); // SRAI
    mem.write_w(0x24, 0xAAAAA137); // LUI
    mem.write_w(0x28, 0xAAAAA117); // AIUPC

    // Register-Register Operations:
    mem.write_w(0x2C, 0x00620133); // ADD 
    mem.write_w(0x30, 0x40620133); // SUB 
    mem.write_w(0x34, 0x00721133); // SLL 
    mem.write_w(0x38, 0x0030A133); // SLT
    mem.write_w(0x3C, 0x0030B133); // SLTU
    mem.write_w(0x40, 0x00734133); // XOR
    mem.write_w(0x44, 0x00735133); // SRL
    mem.write_w(0x48, 0x40735133); // SRA
    mem.write_w(0x4C, 0x00626133); // OR
    mem.write_w(0x50, 0x0050F133); // AND

    // Unconditional Jumps:
    mem.write_w(0x54, 0x000140EF); // JAL positive offset
    mem.write_w(0x7C, 0xFFFEE0EF); // JAL negative offset
    mem.write_w(0x58, 0x0001406F); // J   positive offset
    //mem.write_w(0x80, 0x0);

    proc.run(0,24);
    return 0;
}