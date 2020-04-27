#include <cstdint>
#include <iostream>
#include <string>

#include "../include/rv32i.h"
#include "../include/memory.h"

int main (int argc, char* argv[]) {
    bool verbose = false;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-v" || arg == "--verbose") {
            verbose = true;
            std::cout << "Running in Verbose mode.\n";
        }
    }

    Memory mem = Memory();
    RV32i proc = RV32i(&mem, verbose);

    proc.setRegister(1, 0x00000010);
    proc.setRegister(1, 0x0000F010);
    proc.setRegister(2, 0x0C0A0010);
    proc.setRegister(3, 0x00003050);
    proc.setRegister(4, 0x0000FFFF);
    proc.setRegister(5, 0x00001234);

    proc.printRegisters();

    proc.run(0x0, 3);

    return 0;
}