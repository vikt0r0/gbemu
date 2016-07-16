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
    registers_t regs;

    // Check if a filename was specified.
    if (argc < 2)
        die("No arguments specified");

    FILE *rom_fp;

    // Read the file
    char* filename = argv[1];
    rom_fp = fopen(filename, "rb");

    if (rom_fp == NULL)
        die("File does not exist");

    char ch;

    // Read the first bank of the cartridge into memory
    memory_t memory[MEMORY_SIZE];

    for (int i = 0; i < CARTRIDGE_BANK_SIZE; ++i) {
        memory[i] = fgetc(rom_fp);
    }

    // Print game title, just to test things
    printf("Game title is: ");
    for (int i = CARTRIDGE_GAME_TITLE_LOWER; i <= CARTRIDGE_GAME_TITLE_UPPER; ++i)
        printf("%c", memory_read_byte(memory, i));

    printf("\n");

    // TODO: Start interpreting, and implement instructions ad-hoc

    /*
    while( !feof(rom_fp) ) {
      rom_data++ = fgetc(rom_fp);
    }
    rom_data = EOF;
    */

    fclose(rom_fp);
    
    return 0;
} 