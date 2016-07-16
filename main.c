#include <stdio.h>
#include <stdlib.h>

#include "hw/cpu.h"
#include "hw/cartridge.h"
#include "hw/memory.h"
#include "core/bios.h"

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
    memory_t memory[MEMORY_SIZE];

    for (int i = 0; i < CARTRIDGE_BANK_SIZE; ++i) {
        memory[i] = fgetc(rom_fp);
    }

    // Print game title, just to test things
    printf("Game title is: ");
    for (int i = CARTRIDGE_GAME_TITLE_LOWER; i <= CARTRIDGE_GAME_TITLE_UPPER; i++) {
        uword_t myword = memory_read_word(memory, i);
        printf("%c", myword);
    }
    printf("\n");

    // Pull up relevant info about the ROM
    if (0x00 != memory_read_byte(memory, CARTRIDGE_COLOR_COMPATIBILITY_BYTE)) {
        die("Color GameBoy ROM detected");
    } else {
        printf("Regular B&W GameBoy ROM detected.\n");
    }

    if (memory_read_byte(memory, CARTRIDGE_RAM_SIZE) != CARTRIDGE_RAM_SIZE_0_BANKS)
        die("Only supporting cartridges with no ram so far");
    else
        printf("No RAM banks on cartridge.\n");

    if (memory_read_byte(memory, CARTRIDGE_ROM_SIZE) != CARTRIDGE_ROM_SIZE_2_BANKS)
        die("Only supporting cartridges with 2 ROM banks so far");
    else
        printf("2 ROM banks on cartridge.\n");

        


    // 


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