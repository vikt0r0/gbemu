#ifndef CPU_H
#define CPU_H

#include "../core/types.h"
#include "memory.h"

/* TODO: Document */

typedef struct {
    // AF register
    union {
        struct {
            ubyte_t F;
            ubyte_t A;
        };
        uword_t AF;
    };
    // BC register
    union {
        struct {
            ubyte_t C;
            ubyte_t B;
        };
        uword_t BC;
    };
    // DE register 
    union {
        struct {
            ubyte_t E;
            ubyte_t D;
        };
        uword_t DE;
    };
    // HL register
    union {
        struct {
            ubyte_t L;
            ubyte_t H;
        };
        uword_t HL;
    };
    // Flags register
    struct {
        // Carry flag:
        // This bit is set if a carry occurred from the last
        // math operation or if register A is the smaller value
        // when executing the CP instruction.
        ubyte_t C : 1;
        // Half carry flag:
        // This bit is set if a carry occurred from the lower
        // nibble in the last math operation.
        ubyte_t H : 1;
        // Subtract flag:
        // This bit is set if a subtraction was performed in the
        // last math instruction.
        ubyte_t N : 1;
        // Zero flag:
        // This bit is set when the result of a math operation
        // is zero or two values match when using the CP
        // instruction.
        ubyte_t Z : 1;
    } flags;
    // Stack pointer - should be initialized to 0x100 upon startup.
    uword_t SP;
    // Program counter
    uword_t PC;
} registers_t;

typedef struct {
    char *disassembly;
    void (*function)(memory_t memory, ubyte_t* operands);
    ubyte_t operand_length;
} instruction_t;

#endif
