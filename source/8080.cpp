#include "../include/8080.h"

#include <iostream>

VM_8080::VM_8080() {
    on = true;

    memory = new unsigned char[0xFFFF];

    initOps();
}

int VM_8080::mainCPUloop() {
    while (on == true) {
        opMap[memory[cpu.pc]](memory[cpu.pc], memory[cpu.pc + 1], memory[cpu.pc + 2]);
        cpu.pc++;
    }
    return 0;
}

void VM_8080::notImplemented(unsigned char op) {
    std::cout << (void *)op << ": Not implemented" << std::endl;
}

void VM_8080::initOps() {   // Lambda expressions <3

    // Only a subset of every opcode available on the 8080 is implemented as of now, I may implement more opcodes to obtain a full 8080 emulation

    for (int i = 0x00; i < 0xFF; i++) {
        opMap[i] = [this](int i, int j, int k) { notImplemented(i); };
    }

    // Line 0
    opMap[0x00] = [this](int i, int j, int k) { return; };                                      // NOP
    opMap[0x01] = [this](int i, int j, int k) { cpu.C = j; cpu.B = k; cpu.pc += 2; };           // LXI B,d16
    opMap[0x02] = [this](int i, int j, int k) { memory[cpu.C << 8 | cpu.B] = cpu.A; };          // STAX B
    opMap[0x03] = [this](int i, int j, int k) { cpu.C++; if (cpu.C == 0) cpu.B++; };            // INX B
    opMap[0x04] = [this](int i, int j, int k) { cpu.B++; };                                     // INR B
    opMap[0x05] = [this](int i, int j, int k) { cpu.B--; };                                     // DCR B
    opMap[0x06] = [this](int i, int j, int k) { cpu.B = j; cpu.pc++; };                         // MVI B,d8
    opMap[0x07] = [this](int i, int j, int k) { notImplemented(i); };                           // RLC
    opMap[0x08] = [this](int i, int j, int k) { return; };                                      // NOP (ILLEGAL)
    opMap[0x09] = [this](int i, int j, int k) { 
        unsigned short HLpair = (cpu.H << 8 | cpu.L);
        unsigned short BCpair = (cpu.B << 8 | cpu.C);
        unsigned short result = HLpair + BCpair;
        cpu.H = (result & 0xFF00) >> 8;
        cpu.L = (result & 0x00FF);
        alu.CY = ((result & 0xFFFF0000) != 0);
    };                                                                                          // DAD B
    opMap[0x0A] = [this](int i, int j, int k) { cpu.A = memory[cpu.C << 8 | cpu.B]; };          // LDAX B
    opMap[0x0B] = [this](int i, int j, int k) { notImplemented(i); };                           // DCX B
    opMap[0x0C] = [this](int i, int j, int k) { cpu.C++; };                                     // INR C
    opMap[0x0D] = [this](int i, int j, int k) { cpu.C--; };                                     // DCR C
    opMap[0x0E] = [this](int i, int j, int k) { cpu.C = j; cpu.pc++; };                         // MVI C,d8
    opMap[0x0F] = [this](int i, int j, int k) { 
        unsigned char x = cpu.A;
        cpu.A = ((x & 1) << 7) | (x >> 1); 
        alu.CY = (1 == (x&1));
    };                                                                                          // RRC

    // Line 1
    opMap[0x11] = [this](int i, int j, int k) { cpu.E = j; cpu.D = k; cpu.pc += 2; };           // LXI D,d16
    opMap[0x13] = [this](int i, int j, int k) { cpu.E++; if (cpu.E == 0) cpu.D++; };            // INX D
    opMap[0x19] = [this](int i, int j, int k) { 
        unsigned short HLpair = (cpu.H << 8 | cpu.L);
        unsigned short DEpair = (cpu.D << 8 | cpu.E);
        unsigned short result = HLpair + DEpair;
        cpu.H = (result & 0xFF00) >> 8;
        cpu.L = (result & 0x00FF);
        alu.CY = ((result & 0xFFFF0000) != 0);
    };                                                                                           // DAD D
    opMap[0x1A] = [this](int i, int j, int k) { cpu.A = (cpu.D << 8 | cpu.E); };                 // LDAX D

    // Line 2
    opMap[0x21] = [this](int i, int j, int k) { cpu.L = j; cpu.H = k; cpu.pc += 2; };            // LXI H,d16
    opMap[0x23] = [this](int i, int j, int k) { cpu.L++; if (cpu.L == 0) cpu.H++; };             // INX H
    opMap[0x26] = [this](int i, int j, int k) { cpu.H = j; cpu.pc++; };                          // MVI H,d8
    opMap[0x29] = [this](int i, int j, int k) {
        unsigned short HLpair = (cpu.H << 8 | cpu.L);
        unsigned short result = HLpair + HLpair;
        cpu.H = (result & 0xFF00) >> 8;
        cpu.L = (result & 0x00FF);
        alu.CY = ((result & 0xFFFF0000) != 0);
    };                                                                                           // DAD H

    // Line 4
    opMap[0x41] = [this](int i, int j, int k) { cpu.B = cpu.C; };
    opMap[0x42] = [this](int i, int j, int k) { cpu.B = cpu.D; };
    opMap[0x43] = [this](int i, int j, int k) { cpu.B = cpu.E; };
}