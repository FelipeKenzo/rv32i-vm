#include "../include/rv32i.h"

// Private Utilities
uint32_t RV32i::signExtend(uint32_t data, uint8_t size) {
    if (data >> size-1) {
        return data |= 0xFFFFFFFF << size;
    }
    return data;
}

uint32_t RV32i::twosComplement(uint32_t data) {
    return (0xFFFFFFFF - data + 1);
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
                    
                    setRegister(rd, reg[rs1] + imm);
                    
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 1: // SLLI
                    if (verbose) {
                        std::cout << " -> SLLI:\n";
                        std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                    }
                    
                    setRegister(rd, reg[rs1] << (imm & 0x1F));
                    
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 2: // SLTI
                    if (verbose) {
                        std::cout << " -> SLTI:\n";
                        std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                    }
                    
                    setRegister(rd, ((int32_t)reg[rs1] < (int32_t)imm));
                    
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 3: // SLTIU
                    if (verbose) {
                        std::cout << " -> SLTIU:\n";
                        std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                    }
                    
                    setRegister(rd, (reg[rs1] < imm));
                    
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 4: // XORI
                    if (verbose) {
                        std::cout << " -> XORI:\n";
                        std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                    }
                    
                    setRegister(rd, reg[rs1] ^ imm);
                    
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 5: { //SRLI or SRAI
                    uint32_t shamt = imm & 0x1F;
                    if ((imm >> 10) & 0x1) { // SRAI
                        if (verbose) {
                            std::cout << " -> SRAI:\n";
                            std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                            std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                        }   
                        setRegister(rd, (int32_t)reg[rs1] >> shamt);
                    }
                    else { // SRLI
                        if (verbose) {
                            std::cout << " -> SRLI:\n";
                            std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                            std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                        }
                        setRegister(rd, reg[rs1] >> shamt);
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
                    
                    setRegister(rd, reg[rs1] | imm);
                    
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 7: // ANDI
                    if (verbose) {
                        std::cout << " -> ANDI:\n";
                        std::cout << "   imm: 0x" << std::setw(8) << std::hex << imm << "\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                    }
                    
                    setRegister(rd, reg[rs1] & imm);
                    
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
            
            setRegister(rd, imm);
            
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

            setRegister(rd, imm + reg[pc] - 4);

            if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
            break;
        }

        /*** Integer Register-Register Instructions ***/
        
        case 0x33: {
            
            // extract operands:
            uint32_t rd     = (instr >>  7) & 0x1F;
            uint32_t funct3 = (instr >> 12) & 0x07;
            uint32_t rs1    = (instr >> 15) & 0x1F;
            uint32_t rs2    = (instr >> 20) & 0x1F;

            switch(funct3) {
                case 0: // ADD or SUB:
                    if ((instr >> 30) & 0x1) { // SUB
                        if (verbose) {
                            std::cout << " -> SUB:\n";
                            std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                            std::cout << "   rs2: 0x" << std::setw(8) << std::hex << reg[rs2] << "\n";
                        }

                        setRegister(rd, reg[rs1] - reg[rs2]);
                    }
                    else { // ADD
                        if (verbose) {
                            std::cout << " -> ADD:\n";
                            std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                            std::cout << "   rs2: 0x" << std::setw(8) << std::hex << reg[rs2] << "\n";
                        }

                        setRegister(rd, reg[rs1] + reg[rs2]);
                    }
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 1: // SLL
                    if (verbose) {
                        std::cout << " -> SLL:\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                        std::cout << "   rs2: 0x" << std::setw(8) << std::hex << reg[rs2] << "\n";
                    }

                    setRegister(rd, reg[rs1] << (reg[rs2] & 0x1F));

                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 2: // SLT
                    if (verbose) {
                        std::cout << " -> SLT:\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                        std::cout << "   rs2: 0x" << std::setw(8) << std::hex << reg[rs2] << "\n";
                    }

                    setRegister(rd, ((int32_t)reg[rs1] < (int32_t)reg[rs2]));

                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 3: // SLTU
                    if (verbose) {
                        std::cout << " -> SLTU:\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                        std::cout << "   rs2: 0x" << std::setw(8) << std::hex << reg[rs2] << "\n";
                    }

                    setRegister(rd, (reg[rs1] < reg[rs2]));

                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 4: // XOR
                    if (verbose) {
                        std::cout << " -> XOR:\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                        std::cout << "   rs2: 0x" << std::setw(8) << std::hex << reg[rs2] << "\n";
                    }

                    setRegister(rd, reg[rs1] ^ reg[rs2]);

                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 5: // SRL ou SRA
                    if ((instr >> 30) & 0x1) { // SRA
                        if (verbose) {
                            std::cout << " -> SRA:\n";
                            std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                            std::cout << "   rs2: 0x" << std::setw(8) << std::hex << reg[rs2] << "\n";
                        }

                        setRegister(rd, (int32_t)reg[rs2] >> (reg[rs2] & 0x1F));
                    }
                    else { // SRL
                        if (verbose) {
                            std::cout << " -> SRL:\n";
                            std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                            std::cout << "   rs2: 0x" << std::setw(8) << std::hex << reg[rs2] << "\n";
                        }

                        setRegister(rd, reg[rs1] >> (reg[rs2] & 0x1F));
                    }
                    
                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 6: // OR
                    if (verbose) {
                        std::cout << " -> OR:\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                        std::cout << "   rs2: 0x" << std::setw(8) << std::hex << reg[rs2] << "\n";
                    }

                    setRegister(rd, reg[rs1] | reg[rs2]);

                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
                case 7: // AND
                    if (verbose) {
                        std::cout << " -> AND:\n";
                        std::cout << "   rs1: 0x" << std::setw(8) << std::hex << reg[rs1] << "\n";
                        std::cout << "   rs2: 0x" << std::setw(8) << std::hex << reg[rs2] << "\n";
                    }

                    setRegister(rd, reg[rs1] & reg[rs2]);

                    if (verbose) std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n\n";
                    break;
            }
            break;
        }
        
        /*** Control Transfer Instructions ***/
        // Unconditional jumps:
        case 0x6F: { //JAL
            
            // extract operands:
            uint32_t rd     = (instr >>  7) & 0x1F;
            uint32_t offset =  signExtend((instr & 0xFFFFF000) >> 12, 20) * 2; // offset is multiple of 2 bytes.

            if (verbose) {
                std::cout << " -> JAL:\n";
                std::cout << "offset: 0x" << std::setw(8) << std::hex << offset << "\n";
            }
            
            setRegister(rd, reg[pc]); // J is implemented with rd = 0.

            reg[pc] = reg[pc] - 4 + (int32_t)offset;
            if (verbose) {
                std::cout << "    rd: 0x" << std::setw(8) << std::hex << reg[rd] << "\n";
                std::cout << "    pc: 0x" << std::setw(8) << std::hex << reg[pc] << "\n\n";
            }
            break;
        }
        case 0x67: { //JALR

            // extract operands:
            uint32_t rd     = (instr >>  7) & 0x1F;
            uint32_t rs1    = (instr >> 15) & 0x1F;
            uint32_t imm    = (instr >> 20, 12);

            if (verbose) {
                std::cout << " -> JALR:\n";
                std::cout << "offset: 0x" << std::setw(8) << std::hex << offset << "\n";
            }

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

        //if (verbose) std::cout << "    pc: 0x" << std::setw(8) << std::hex << reg[pc] << "\n";
        
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
    if (i > 0) reg[i] = data;
}