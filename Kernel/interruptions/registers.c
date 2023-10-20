#include <registers.h>

void copyRegisters(registers * from, registers * to){
    for (int i = 0; i< REGISTERS_SIZE; i++){
        ((uint64_t *) to)[i] = ((uint64_t *) from)[i];
    }
}