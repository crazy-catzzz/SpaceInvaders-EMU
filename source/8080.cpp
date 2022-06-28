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

    // I have to implement like another 240 opcodes  k i l l  m e

    for (int i = 0x00; i < 0xFF; i++) {
        opMap[i] = [this](int i, int j, int k) { notImplemented(i); };
    }

    opMap[0x00] = [this](int i, int j, int k) { return; };                                      // NOP
    opMap[0x01] = [this](int i, int j, int k) { cpu.C = j; cpu.B = k; cpu.pc += 2;};            // LXI B,d16
    opMap[0x02] = [this](int i, int j, int k) { memory[cpu.C << 8 | cpu.B] = cpu.A; };          // STAX B
    opMap[0x03] = [this](int i, int j, int k) { notImplemented(i); };                           // INX B
    opMap[0x04] = [this](int i, int j, int k) { cpu.B++; };                                     // INR B
    opMap[0x05] = [this](int i, int j, int k) { cpu.B--; };                                     // DCR B
    opMap[0x06] = [this](int i, int j, int k) { cpu.B = j; cpu.pc += 1; };                                   // MVI B,d8
    opMap[0x07] = [this](int i, int j, int k) { notImplemented(i); };                           // RLC
    opMap[0x08] = [this](int i, int j, int k) { return; };                                      // NOP (ILLEGAL)
    opMap[0x09] = [this](int i, int j, int k) { cpu.H += (cpu.B * 2); cpu.L += (cpu.C * 2);};   // DAD B
    opMap[0x0A] = [this](int i, int j, int k) { cpu.A = memory[cpu.C << 8 | cpu.B]; };          // LDAX B
    opMap[0x0B] = [this](int i, int j, int k) { notImplemented(i); };                           // DCX B

    opMap[0x41] = [this](int i, int j, int k) { cpu.B = cpu.C; };
    opMap[0x42] = [this](int i, int j, int k) { cpu.B = cpu.D; };
    opMap[0x43] = [this](int i, int j, int k) { cpu.B = cpu.E; };
}