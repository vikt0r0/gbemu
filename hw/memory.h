#ifndef MEM_H
#define MEM_H

#include "../core/types.h"

/* TODO: Document */

// Size of memory
#define MEM_SIZE 0xffff

// $FFFF	Interrupt Enable Flag
#define MEM_INTERRUPT_ENABLE_FLAG 0xffff

// $FF80-$FFFE	Zero Page - 127 bytes
#define MEM_ZERO_PAGE_LOWER 0xff80
#define MEM_ZERO_PAGE_UPPER 0xfffe

// $FF00-$FF7F	Hardware I/O Registers
#define MEM_HARDWARE_IO_REGISTERS_LOWER 0xff00
#define MEM_HARDWARE_IO_REGISTERS_UPPER 0xff7f

// $FEA0-$FEFF	Unusable Memory
#define MEM_UNUSABLE_MEMORY_LOWER 0xfea0
#define MEM_UNUSABLE_MEMORY_UPPER 0xfeff

// $FE00-$FE9F	OAM - Object Attribute Memory
#define MEM_OBJECT_ATTRIBUTE_MEMORY_LOWER 0xfe00
#define MEM_OBJECT_ATTRIBUTE_MEMORY_UPPER 0xfe9f

// $E000-$FDFF	Echo RAM - Reserved, Do Not Use
#define MEM_ECHO_RAM_LOWER 0xe000
#define MEM_ECHO_RAM_UPPER 0xfdff

// $D000-$DFFF	Internal RAM - Bank 1-7 (switchable - CGB only)
#define MEM_INTERNAL_RAM_SWITCHABLE_LOWER 0xd000
#define MEM_INTERNAL_RAM_SWITCHABLE_UPPER 0xdfff

// $C000-$CFFF	Internal RAM - Bank 0 (fixed)
#define MEM_INTERNAL_RAM_LOWER 0xc000
#define MEM_INTERNAL_RAM_UPPER 0xcfff

// $A000-$BFFF	Cartridge RAM (If Available)
#define MEM_CARTRIDGE_RAM_LOWER 0xa000
#define MEM_CARTRIDGE_RAM_UPPER 0xbfff

// $9C00-$9FFF	BG Map Data 2
#define MEM_BG_MAP_DATA_2_LOWER 0x9c00
#define MEM_BG_MAP_DATA_2_UPPER 0x9fff

// $9800-$9BFF	BG Map Data 1
#define MEM_BG_MAP_DATA_1_LOWER 0x9800
#define MEM_BG_MAP_DATA_1_UPPER 0x9bff

// $8000-$97FF	Character RAM
#define MEM_CHARACTER_RAM_LOWER 0x8000
#define MEM_CHARACTER_RAM_UPPER 0x97ff

// $4000-$7FFF	Cartridge ROM - Switchable Banks 1-xx
#define MEM_CARTRIDGE_ROM_SWITCHABLE_LOWER 0x4000
#define MEM_CARTRIDGE_ROM_SWITCHABLE_UPPER 0x7fff

// $0150-$3FFF	Cartridge ROM - Bank 0 (fixed)
#define MEM_CARTRIDGE_ROM_LOWER 0x0150
#define MEM_CARTRIDGE_ROM_UPPER 0x3fff

// $0100-$014F	Cartridge Header Area
#define MEM_CARTRIDGE_HEADER_LOWER 0x0100
#define MEM_CARTRIDGE_HEADER_UPPER 0x014f

// $0000-$00FF	Restart and Interrupt Vectors
#define MEM_RESTART_INTERRUPT_LOWER 0x0000
#define MEM_RESTART_INTERRUPT_UPPER 0x00ff

typedef ubyte_t* memory_t;

#endif