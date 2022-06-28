#pragma once

#include <map>
#include <functional>
#include <stack>

struct cpu_8080 {
    unsigned char B;    // 8-bit reg
    unsigned char C;    // 8-bit reg
    unsigned char D;    // 8-bit reg
    unsigned char E;    // 8-bit reg
    unsigned char H;    // 8-bit reg
    unsigned char L;    // 8-bit reg

    unsigned char W;    // 8-bit temp reg
    unsigned char Z;    // 8-bit temp reg

    unsigned short pc;  // Program Counter (16-bit reg)
    unsigned short sp;  // Stack Pointer (16-bit reg)
};

struct alu_8080 {
    unsigned char acc;  // 8-bit accumulator
    unsigned char act;  // 8-bit temp accumulator

    unsigned char F;    // 5-bit Flag Register (zero, carry, sign, parity, aux carry)

    unsigned char tmp;  // 8-bit temp reg
};

class VM_8080 {
public:
    VM_8080();

    cpu_8080 cpu;           // 8080 CPU
    alu_8080 alu;           // 8080 ALU

    unsigned char* memory;  // Mem array

    std::map<int, std::function<void(const int, const int, const int)>> opMap;  // Opcode map

    int mainCPUloop();

private:
    bool on;

    void notImplemented(unsigned char op);
    void initOps();
};