#include <stdio.h>
#include <stdlib.h>

#include "hw/cpu.h"
//#include "hw/cartridge.h"
#include "hw/memory.h"

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

    /*
    while( !feof(rom_fp) ) {
      rom_data++ = fgetc(rom_fp);
    }
    rom_data = EOF;
	*/

    fclose(rom_fp);
	
	return 0;
} 