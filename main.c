#include <stdio.h>
#include <stdlib.h>

#include "hw/cpu.h"
#include "hw/cartridge.h"
#include "hw/memory.h"

#include "core/types.h"

void die(char* message) {
    printf("%s! Aborting...\n", message);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    // Check if a filename was specified.
    if (argc < 2)
        die("No arguments specified");

    FILE *rom_fp;

    // Read the file
    char* filename = argv[1];
    rom_fp = fopen(filename, "rb");

    if (rom_fp == NULL)
        die("File does not exist");

    // Read the first bank of the cartridge into memory
    memory_t mem;
    memory_init(&mem);

    // Read bank 0 into memory
    for (int i = 0; i < MEMORY_CARTRIDGE_ROM_UPPER; ++i) {
        mem.memory[i] = fgetc(rom_fp);
    }

    // Read bank 1 into memory
    for (int i = MEMORY_CARTRIDGE_ROM_SWITCHABLE_LOWER; i < MEMORY_CARTRIDGE_ROM_SWITCHABLE_UPPER; ++i) {
        mem.memory[i] = fgetc(rom_fp);
    }

    // Print game title, just to test things
    printf("Game title is: ");
    for (int i = CARTRIDGE_GAME_TITLE_LOWER; i <= CARTRIDGE_GAME_TITLE_UPPER; i++) {
        uword_t myword = memory_read_word(&mem, i);
        printf("%c", myword);
    }
    printf("\n");

    // Pull up relevant info about the ROM
    if (0x00 != memory_read_byte(&mem, CARTRIDGE_COLOR_COMPATIBILITY_BYTE)) {
        die("Color GameBoy ROM detected");
    } else {
        printf("Regular B&W GameBoy ROM detected.\n");
    }

    fclose(rom_fp);
    
    // Initialize registers
    registers_t regs;

    // Begin interpreting
    while (1) {
        if (cpu_interpret_next_instruction(&mem, &regs) == CPU_UNIMPLEMENTED_INSTRUCTION) {
            printf(
                "Unimplemented instruction at 0x%04X, opcode 0x%02X, disassembly \"%s\"\n",
                regs.PC,
                memory_read_byte(&mem, regs.PC),
                cpu_get_disassembly(&mem, regs.PC)
            );
            exit(EXIT_FAILURE);
        }
    }

    return 0;
} 