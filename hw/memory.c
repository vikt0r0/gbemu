#include "memory.h"

uword_t translate_address_echo(uword_t addr) {
	// If we are in this range, we are trying to access the echo
	// region of the 8kB internal ram. Displace by 0x2000 bytes
	// to go to the 'real' ram.
	if (0xe000 <= addr && addr < 0xfe00)
		return addr - 0x2000;

	return addr;
}

// Reading from memory.
ubyte_t memory_read_byte(memory_t *mem, uword_t addr) {
	addr = translate_address_echo(addr);
	return mem[addr];
}

uword_t memory_read_word(memory_t *mem, uword_t addr) {
	addr = translate_address_echo(addr);
	// Simply cast mem to a uword_t pointer to return the
	// word from this address instead of a byte. This should
	// work as both the GameBoy as well as x86 are both little
	// endian, see (https://www.wikiwand.com/en/Endianness).
	// In case this emulator is to be ported to big-endian
	// architectures, keep in mind that this probably needs to
	// bulletproofed...
	mem += addr;
	uword_t *mem_word_ptr = (uword_t*) mem;
	return *(mem_word_ptr);
}

// Writing to memory.
void memory_write_byte(memory_t *mem, uword_t addr, ubyte_t data) {
	addr = translate_address_echo(addr);
	mem[addr] = data;
}

void memory_write_word(memory_t *mem, uword_t addr, uword_t data) {
	// TODO: Employ some defensive programming to make sure
	// we dont do things like mem[0xffff] = 0x1234, as this
	// would cause a segmentation fault. It probably won't
	// ever happen, but who knows...
	//addr = translate_address_echo(addr);
	mem += addr;
	uword_t *mem_word_ptr = (uword_t*) mem;
	*(mem_word_ptr) = data;
}