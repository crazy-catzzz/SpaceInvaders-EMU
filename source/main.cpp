#include "../include/8080.h"

int main(int argc, char** argv) {

    VM_8080 vm8080;
    
    return vm8080.mainCPUloop();

}