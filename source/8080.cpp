#include "../include/8080.h"

#include <iostream>

VM_8080::VM_8080() {
    on = true;

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
    for (int i = 0x0; i < 0xFF; i++) {
        opMap[i] = [this](int i, int j, int k) { notImplemented(i); };
    }

    opMap[0x00] = [this](int i, int j, int k) { return; };
    opMap[0x01] = [this](int i, int j, int k) { cpu.C = j; cpu.B = k; cpu.pc += 2;};

    opMap[0x41] = [this](int i, int j, int k) { cpu.B = cpu.C; };
    opMap[0x42] = [this](int i, int j, int k) { cpu.B = cpu.D; };
    opMap[0x43] = [this](int i, int j, int k) { cpu.B = cpu.E; };
}