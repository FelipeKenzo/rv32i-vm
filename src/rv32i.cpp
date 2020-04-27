#include "../include/rv32i.h"

// Private Utilities
uint32_t RV32i::signExtend(uint32_t data, uint8_t size) {
    if (data >> size-1) {
        return data |= 0xFFFFFFFF << size;
    }
    return data;
}

// Instruction Execution
void RV32i::executeInstr(uint32_t instr) {
    if (verbose) {
        std::cout << std::internal
                  << std::setfill('0');

        std::cout << "0x" << std::hex << std::setw(4) << reg[pc]-4 << ": "
                  << "0x" << std::setw(8) << instr;
    }

    uint32_t op = instr & 0x7F;

    switch(op) {
        /*** Integer Register-Immediate Instructions ***/
        case 0x13: { // Arithmetic, logical and shift immediate operations.
            
            // extract operands:
            uint32_t rd     = (instr >>  7) & 0x1F;
            uint32_t funct3 = (instr >> 12) & 0x07;
            uint32_t rs1    = (instr >> 15) & 0x1F;
            uint32_t imm   = signExtend(instr >> 20, 12);
            
            switch(funct3) {
                case 0: // ADDI
                    if (verbose) {
                        std::cout << " -> ADDI:\n";
                        std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                    }
                    
                    reg[rd] = reg[rs1] + imm;
                    
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 1: // SLLI
                    if (verbose) {
                        std::cout << " -> SLLI:\n";
                        std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                    }
                    
                    reg[rd] = reg[rs1] << (imm & 0x1F);
                    
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 2: // SLTI
                    if (verbose) {
                        std::cout << " -> SLTI:\n";
                        std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                    }
                    
                    reg[rd] = ((int32_t)reg[rs1] < (int32_t)imm);
                    
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 3: // SLTIU
                    if (verbose) {
                        std::cout << " -> SLTIU:\n";
                        std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                    }
                    
                    reg[rd] = (reg[rs1] < imm);
                    
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 4: // XORI
                    if (verbose) {
                        std::cout << " -> XORI:\n";
                        std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                    }
                    
                    reg[rd] = reg[rs1] ^ imm;
                    
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 5: { //SRLI and SRAI
                    uint32_t shamt = imm & 0x1F;
                    if ((imm >> 10) & 0x1) { // SRAI
                        if (verbose) {
                            std::cout << " -> SRAI:\n";
                            std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                            std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                        }   
                        reg[rd] = (int32_t)reg[rs1] >> shamt;
                    }
                    else { // SRLI
                        if (verbose) {
                            std::cout << " -> SRLI:\n";
                            std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                            std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                        }
                        reg[rd] = reg[rs1] >> shamt;
                    }
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                }
                case 6: // ORI
                    if (verbose) {
                        std::cout << " -> ORI:\n";
                        std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                    }
                    
                    reg[rd] = reg[rs1] | imm;
                    
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 7: // ANDI
                    if (verbose) {
                        std::cout << " -> ANDI:\n";
                        std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                    
                    }
                    
                    reg[rd] = reg[rs1] & imm;
                    
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                default:
                    std::cout << "\n";
            }
            break;
        }
        case 0x37: { // LUI
            
            // extract operands:
            uint32_t rd     = (instr >>  7) & 0x1F;
            uint32_t imm   =  instr & 0xFFFFF000;

            if (verbose) {
                std::cout << " -> LUI:\n";
                std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
            }
            
            reg[rd] = imm;
            
            if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
            break;
        }
        case 0x17: { // AIUPC
            
            // extract operands:
            uint32_t rd     = (instr >>  7) & 0x1F;
            uint32_t imm   =  instr & 0xFFFFF000;

            if (verbose) {
                std::cout << " -> AIUPC:\n";
                std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
            }

            reg[rd] = imm + reg[pc] - 4;

            if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
            break;
        }
        default:
            std::cout << "\n\n";
    }
}

RV32i::RV32i(Memory* mem, bool verbose) : mem(mem), verbose(verbose){
    //ctor
}

void RV32i::run(uint32_t origin) {
    int count = 0;
    int maxcount = 2;
    reg[pc] = origin;
    uint32_t instr;
    
    while(!halt) {
        // Fetch Instruction
        instr = *(mem->read(reg[pc]));
        reg[pc] += 4;
        
        // Decode and Execute instructions
        executeInstr(instr);
        count++;
    }
}

// run maxcount instructions
void RV32i::run(uint32_t origin, int maxcount) {
    int count = 0;
    reg[pc] = origin;
    uint32_t instr;
    
    for (int i = 0; i < maxcount; i++) {
        // Fetch Instruction
        instr = *(mem->read(reg[pc]));
        reg[pc] += 4;
        
        // Decode and Execute instructions
        executeInstr(instr);
    }
}

// Public Utilities
void RV32i::printRegisters() {
    std::cout << std::internal << std::setfill('0');

    for (int i = 0; i < 32; i++) {
        std::cout << "x" << std::setw(2) << std::dec << i << ": 0x"
                         << std::setw(8) << std::hex << reg[i] << std::endl;
    }
    std::cout << "pc:  0x" << std::setw(8) << std::hex << reg[pc] << "\n\n";
}

void RV32i::printRegister(int i) {
    std::cout << std::internal << std::setfill('0');
    
    if (i < 32) std::cout << "x" << std::dec << i << ": 0x" << std::setw(8) << std::hex << reg[i] << "\n\n";
    else if (i == 33) std::cout << "pc: " << std::setw(8) << std::hex << reg[pc] << "\n\n";
}

void RV32i::setRegister(uint8_t i, uint32_t data) {
    reg[i] = data;
}