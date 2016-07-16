#ifndef MEMORY_H
#define MEMORY_H

#include "../core/types.h"

/* TODO: Document */

// Size of memory
#define MEMORY_SIZE 0xffff

// $FFFF	Interrupt Enable Flag
#define MEMORY_INTERRUPT_ENABLE_FLAG 0xffff

// $FF80-$FFFE	Zero Page - 127 bytes
#define MEMORY_ZERO_PAGE_UPPER 0xfffe
#define MEMORY_ZERO_PAGE_LOWER 0xff80

// $FF00-$FF7F	Hardware I/O Registers
#define MEMORY_HARDWARE_IO_REGISTERS_UPPER 0xff7f
#define MEMORY_HARDWARE_IO_REGISTERS_LOWER 0xff00

// $FEA0-$FEFF	Unusable Memory
#define MEMORY_UNUSABLE_MEMORY_UPPER 0xfeff
#define MEMORY_UNUSABLE_MEMORY_LOWER 0xfea0

// $FE00-$FE9F	OAM - Object Attribute Memory
#define MEMORY_OBJECT_ATTRIBUTE_MEMORY_UPPER 0xfe9f
#define MEMORY_OBJECT_ATTRIBUTE_MEMORY_LOWER 0xfe00

// $E000-$FDFF	Echo RAM - Reserved, Do Not Use
#define MEMORY_ECHO_RAM_UPPER 0xfdff
#define MEMORY_ECHO_RAM_LOWER 0xe000

// $D000-$DFFF	Internal RAM - Bank 1-7 (switchable - CGB only)
#define MEMORY_INTERNAL_RAM_SWITCHABLE_UPPER 0xdfff
#define MEMORY_INTERNAL_RAM_SWITCHABLE_LOWER 0xd000

// $C000-$CFFF	Internal RAM - Bank 0 (fixed)
#define MEMORY_INTERNAL_RAM_UPPER 0xcfff
#define MEMORY_INTERNAL_RAM_LOWER 0xc000

// $A000-$BFFF	Cartridge RAM (If Available)
#define MEMORY_CARTRIDGE_RAM_UPPER 0xbfff
#define MEMORY_CARTRIDGE_RAM_LOWER 0xa000

// $9C00-$9FFF	BG Map Data 2
#define MEMORY_BG_MAP_DATA_2_UPPER 0x9fff
#define MEMORY_BG_MAP_DATA_2_LOWER 0x9c00

// $9800-$9BFF	BG Map Data 1
#define MEMORY_BG_MAP_DATA_1_UPPER 0x9bff
#define MEMORY_BG_MAP_DATA_1_LOWER 0x9800

// $8000-$97FF	Character RAM
#define MEMORY_CHARACTER_RAM_UPPER 0x97ff
#define MEMORY_CHARACTER_RAM_LOWER 0x8000

// $4000-$7FFF	Cartridge ROM - Switchable Banks 1-xx
#define MEMORY_CARTRIDGE_ROM_SWITCHABLE_UPPER 0x7fff
#define MEMORY_CARTRIDGE_ROM_SWITCHABLE_LOWER 0x4000

// $0150-$3FFF	Cartridge ROM - Bank 0 (fixed)
#define MEMORY_CARTRIDGE_ROM_UPPER 0x3fff
#define MEMORY_CARTRIDGE_ROM_LOWER 0x0150

// $0100-$014F	Cartridge Header Area
#define MEMORY_CARTRIDGE_HEADER_UPPER 0x014f
#define MEMORY_CARTRIDGE_HEADER_LOWER 0x0100

// $0000-$00FF	Restart and Interrupt Vectors
#define MEMORY_RESTART_INTERRUPT_UPPER 0x00ff
#define MEMORY_RESTART_INTERRUPT_LOWER 0x0000

// The size of the bios
#define BIOS_SIZE 256

typedef struct {
	ubyte_t memory[MEMORY_SIZE];
	ubyte_t is_bios_mapped : 1;
} memory_t;

// Reading from memory.
ubyte_t memory_read_byte(memory_t *mem, uword_t addr);
uword_t memory_read_word(memory_t *mem, uword_t addr);

// Writing to memory.
void memory_write_byte(memory_t *mem, uword_t addr, ubyte_t data);
void memory_write_word(memory_t *mem, uword_t addr, uword_t data);

void memory_init(memory_t *mem);

#endif