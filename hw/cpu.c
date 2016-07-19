#include <stdio.h>

#include "cpu.h"
#include "memory.h"
#include "../core/types.h"

// TODO: Implement ad-hoc, add CB instructions!
// Disassembly from http://imrannazar.com/Gameboy-Z80-Opcode-Map

void nop(memory_t *mem, registers_t *regs, ubyte_t operand_length) {
	// Update the program counter
	regs->PC += 1;
	return;
}

void ld_bc_nn(memory_t *mem, registers_t *regs, ubyte_t operand_length) {
	// Get operands, here 8 bytes.
	regs->BC = memory_read_word(mem, (regs->PC)+1);
	regs->PC += operand_length + 1;
	return;
}

void ld_sp_nn(memory_t *mem, registers_t *regs, ubyte_t operand_length) {
	// Get operands, here 8 bytes.
	regs->SP = memory_read_word(mem, (regs->PC)+1);
	regs->PC += operand_length + 1;
	return;
}

instruction_t cpu_instructions[256] = {
	{ "NOP", nop, 0 },
	{ "LD BC, 0x%04X", ld_bc_nn, 2 },
	{ "LD (BC), A", NULL, 0 },
	{ "INC BC", NULL, 0 },
	{ "INC B", NULL, 0 },
	{ "DEC B", NULL, 0 },
	{ "LD B, 0x%02X", NULL, 1 },
	{ "RLC A", NULL, 0 },
	{ "LD (0x%04X), SP", NULL, 2 },
	{ "ADD HL, BC", NULL, 0 },
	{ "LD A, (BC)", NULL, 0 },
	{ "DEC BC", NULL, 0 },
	{ "INC C", NULL, 0 },
	{ "DEC C", NULL, 0 },
	{ "LD C, 0x%02x", NULL, 1 },
	{ "RRC A", NULL, 0 },

	{ "STOP", NULL, 0 },
	{ "LD DE, 0x%04X", NULL, 2 },
	{ "LD (DE), A", NULL, 0 },
	{ "INC DE", NULL, 0 },
	{ "INC D", NULL, 0 },
	{ "DEC D", NULL, 0 },
	{ "LD D, 0x%02X", NULL, 1 },
	{ "RL A", NULL, 0 },
	{ "JR 0x%02X", NULL, 1 },
	{ "ADD HL, DE", NULL, 0 },
	{ "LD A, (DE)", NULL, 0 },
	{ "DEC DE", NULL, 0 },
	{ "INC E", NULL, 0 },
	{ "DEC E", NULL, 0 },
	{ "LD E, 0x%02x", NULL, 1 },
	{ "RR A", NULL, 0 },

	{ "JR NZ, 0x%02X", NULL, 1 },
	{ "LD HL, 0x%04X", NULL, 2 },
	{ "LDI (HL), A", NULL, 0 },
	{ "INC HL", NULL, 0 },
	{ "INC H", NULL, 0 },
	{ "DEC H", NULL, 0 },
	{ "LD H, 0x%02X", NULL, 1 },
	{ "DAA", NULL, 0 },
	{ "JR Z, 0x%02X", NULL, 1 },
	{ "ADD HL, HL", NULL, 0 },
	{ "LDI A, (HL)", NULL, 0 },
	{ "DEC HL", NULL, 0 },
	{ "INC L", NULL, 0 },
	{ "DEC L", NULL, 0 },
	{ "LD L, 0x%02x", NULL, 1 },
	{ "CPL", NULL, 0 },

	{ "JR NC, 0x%02X", NULL, 1 },
	{ "LD SP, 0x%04X", ld_sp_nn, 2 },
	{ "LDD (HL), A", NULL, 0 },
	{ "INC SP", NULL, 0 },
	{ "INC (HL)", NULL, 0 },
	{ "DEC (HL)", NULL, 0 },
	{ "LD (HL), 0x%02X", NULL, 1 },
	{ "SCF", NULL, 0 },
	{ "JR C, 0x%02X", NULL, 1 },
	{ "ADD HL, SP", NULL, 0 },
	{ "LDI A, (HL)", NULL, 0 },
	{ "DEC SP", NULL, 0 },
	{ "INC A", NULL, 0 },
	{ "DEC A", NULL, 0 },
	{ "LD A, 0x%02x", NULL, 1 },
	{ "CCF", NULL, 0 },

	{ "LD B, B", NULL, 0 },
	{ "LD B, C", NULL, 0 },
	{ "LD B, D", NULL, 0 },
	{ "LD B, E", NULL, 0 },
	{ "LD B, H", NULL, 0 },
	{ "LD B, L", NULL, 0 },
	{ "LD B, (HL)", NULL, 0 },
	{ "LD B, A", NULL, 0 },
	{ "LD C, B", NULL, 0 },
	{ "LD C, C", NULL, 0 },
	{ "LD C, D", NULL, 0 },
	{ "LD C, E", NULL, 0 },
	{ "LD C, H", NULL, 0 },
	{ "LD C, L", NULL, 0 },
	{ "LD C, (HL)", NULL, 0 },
	{ "LD C, A", NULL, 0 },

	{ "LD D, B", NULL, 0 },
	{ "LD D, C", NULL, 0 },
	{ "LD D, D", NULL, 0 },
	{ "LD D, E", NULL, 0 },
	{ "LD D, H", NULL, 0 },
	{ "LD D, L", NULL, 0 },
	{ "LD D, (HL)", NULL, 0 },
	{ "LD D, A", NULL, 0 },
	{ "LD E, B", NULL, 0 },
	{ "LD E, C", NULL, 0 },
	{ "LD E, D", NULL, 0 },
	{ "LD E, E", NULL, 0 },
	{ "LD E, H", NULL, 0 },
	{ "LD E, L", NULL, 0 },
	{ "LD E, (HL)", NULL, 0 },
	{ "LD E, A", NULL, 0 },

	{ "LD H, B", NULL, 0 },
	{ "LD H, C", NULL, 0 },
	{ "LD H, D", NULL, 0 },
	{ "LD H, E", NULL, 0 },
	{ "LD H, H", NULL, 0 },
	{ "LD H, L", NULL, 0 },
	{ "LD H, (HL)", NULL, 0 },
	{ "LD H, A", NULL, 0 },
	{ "LD L, B", NULL, 0 },
	{ "LD L, C", NULL, 0 },
	{ "LD L, D", NULL, 0 },
	{ "LD L, E", NULL, 0 },
	{ "LD L, H", NULL, 0 },
	{ "LD L, L", NULL, 0 },
	{ "LD L, (HL)", NULL, 0 },
	{ "LD L, A", NULL, 0 },

	{ "LD (HL), B", NULL, 0 },
	{ "LD (HL), C", NULL, 0 },
	{ "LD (HL), D", NULL, 0 },
	{ "LD (HL), E", NULL, 0 },
	{ "LD (HL), H", NULL, 0 },
	{ "LD (HL), L", NULL, 0 },
	{ "LD (HL), (HL)", NULL, 0 },
	{ "LD (HL), A", NULL, 0 },
	{ "LD A, B", NULL, 0 },
	{ "LD A, C", NULL, 0 },
	{ "LD A, D", NULL, 0 },
	{ "LD A, E", NULL, 0 },
	{ "LD A, H", NULL, 0 },
	{ "LD A, L", NULL, 0 },
	{ "LD A, (HL)", NULL, 0 },
	{ "LD A, A", NULL, 0 },

	{ "ADD A, B", NULL, 0 },
	{ "ADD A, C", NULL, 0 },
	{ "ADD A, D", NULL, 0 },
	{ "ADD A, E", NULL, 0 },
	{ "ADD A, H", NULL, 0 },
	{ "ADD A, L", NULL, 0 },
	{ "ADD A, (HL)", NULL, 0 },
	{ "ADD A, A", NULL, 0 },
	{ "ADC A, B", NULL, 0 },
	{ "ADC A, C", NULL, 0 },
	{ "ADC A, D", NULL, 0 },
	{ "ADC A, E", NULL, 0 },
	{ "ADC A, H", NULL, 0 },
	{ "ADC A, L", NULL, 0 },
	{ "ADC A, (HL)", NULL, 0 },
	{ "ADC A, A", NULL, 0 },

	{ "SUB A, B", NULL, 0 },
	{ "SUB A, C", NULL, 0 },
	{ "SUB A, D", NULL, 0 },
	{ "SUB A, E", NULL, 0 },
	{ "SUB A, H", NULL, 0 },
	{ "SUB A, L", NULL, 0 },
	{ "SUB A, (HL)", NULL, 0 },
	{ "SUB A, A", NULL, 0 },
	{ "SBC A, B", NULL, 0 },
	{ "SBC A, C", NULL, 0 },
	{ "SBC A, D", NULL, 0 },
	{ "SBC A, E", NULL, 0 },
	{ "SBC A, H", NULL, 0 },
	{ "SBC A, L", NULL, 0 },
	{ "SBC A, (HL)", NULL, 0 },
	{ "SBC A, A", NULL, 0 },

	{ "AND B", NULL, 0 },
	{ "AND C", NULL, 0 },
	{ "AND D", NULL, 0 },
	{ "AND E", NULL, 0 },
	{ "AND H", NULL, 0 },
	{ "AND L", NULL, 0 },
	{ "AND (HL)", NULL, 0 },
	{ "AND A", NULL, 0 },
	{ "XOR B", NULL, 0 },
	{ "XOR C", NULL, 0 },
	{ "XOR D", NULL, 0 },
	{ "XOR E", NULL, 0 },
	{ "XOR H", NULL, 0 },
	{ "XOR L", NULL, 0 },
	{ "XOR (HL)", NULL, 0 },
	{ "XOR A", NULL, 0 },

	{ "OR B", NULL, 0 },
	{ "OR C", NULL, 0 },
	{ "OR D", NULL, 0 },
	{ "OR E", NULL, 0 },
	{ "OR H", NULL, 0 },
	{ "OR L", NULL, 0 },
	{ "OR (HL)", NULL, 0 },
	{ "OR A", NULL, 0 },
	{ "CP B", NULL, 0 },
	{ "CP C", NULL, 0 },
	{ "CP D", NULL, 0 },
	{ "CP E", NULL, 0 },
	{ "CP H", NULL, 0 },
	{ "CP L", NULL, 0 },
	{ "CP (HL)", NULL, 0 },
	{ "CP A", NULL, 0 },

	{ "RET NZ", NULL, 0 },
	{ "POP BC", NULL, 0 },
	{ "JP NZ, 0x%04X", NULL, 2 },
	{ "JP 0x%04X", NULL, 2 },
	{ "CALL NZ, 0x%04X", NULL, 2 },
	{ "PUSH BC", NULL, 0 },
	{ "ADD A, 0x%02X", NULL, 1 },
	{ "RST 0", NULL, 0 },
	{ "RET Z", NULL, 0 },
	{ "RET", NULL, 0 },
	{ "JP Z, 0x%04X", NULL, 2 },
	{ "EXT OPS (CB)", NULL, 0 },
	{ "CALL Z, 0x%04X", NULL, 2 },
	{ "CALL 0x%04X", NULL, 2 },
	{ "ADC A, 0x%02X", NULL, 1 },
	{ "RST 8", NULL, 0 },

	{ "RET NC", NULL, 0 },
	{ "POP DE", NULL, 0 },
	{ "JP NC, 0x%04X", NULL, 2 },
	{ "UNUSED", NULL, 0 },
	{ "CALL NC, 0x%04X", NULL, 2 },
	{ "PUSH DE", NULL, 0 },
	{ "SUB A, 0x%02X", NULL, 1 },
	{ "RST 10", NULL, 0 },
	{ "RET C", NULL, 0 },
	{ "RETI", NULL, 0 },
	{ "JP C, 0x%04X", NULL, 2 },
	{ "UNUSED", NULL, 0 },
	{ "CALL C, 0x%04X", NULL, 2 },
	{ "UNUSED", NULL, 0 },
	{ "SBC A, 0x%02X", NULL, 1 },
	{ "RST 18", NULL, 0 },

	{ "LDH (0x%02X), A", NULL, 1 },
	{ "POP HL", NULL, 0 },
	{ "LDH (C),A", NULL, 0 },
	{ "UNUSED", NULL, 0 },
	{ "UNUSED", NULL, 0 },
	{ "PUSH HL", NULL, 0 },
	{ "AND 0x%02X", NULL, 1 },
	{ "RST 20", NULL, 0 },
	{ "ADD SP, 0x%02X", NULL, 0 },
	{ "JP (HL)", NULL, 0 },
	{ "LD (0x%04X), A", NULL, 2 },
	{ "UNUSED", NULL, 0 },
	{ "UNUSED", NULL, 0 },
	{ "UNUSED", NULL, 0 },
	{ "XOR 0x%02X", NULL, 1 },
	{ "RST 28", NULL, 0 },

	{ "LDH A, (0x%02X)", NULL, 1 },
	{ "POP AF", NULL, 0 },
	{ "UNUSED", NULL, 0 },
	{ "DI", NULL, 0 },
	{ "UNUSED", NULL, 0 },
	{ "PUSH AF", NULL, 0 },
	{ "OR 0x%02X", NULL, 1 },
	{ "RST 30", NULL, 0 },
	{ "LDHL SP, 0x%02X", NULL, 0 },
	{ "LD SP, HL", NULL, 0 },
	{ "LD A, (0x%04X)", NULL, 2 },
	{ "EI", NULL, 0 },
	{ "UNUSED", NULL, 0 },
	{ "UNUSED", NULL, 0 },
	{ "CP 0x%02X", NULL, 1 },
	{ "RST 38", NULL, 0 }    													
};

instruction_t cpu_get_instruction(memory_t *mem, uword_t addr) {
	return cpu_instructions[memory_read_byte(mem, addr)];
}

char* cpu_get_disassembly(memory_t *mem, uword_t addr) {
	instruction_t instruction = cpu_get_instruction(mem, addr);
	char *disassembly;

	// Create the disassembly
	switch (instruction.operand_length) {
		case 0:
			asprintf(&disassembly, instruction.disassembly);
			break;
		case 1:
			asprintf(&disassembly, instruction.disassembly, memory_read_byte(mem, addr+1));
			break;
		case 2:
			asprintf(&disassembly, instruction.disassembly, memory_read_word(mem, addr+1));
	}

	return disassembly;
}

int cpu_interpret_next_instruction(memory_t *mem, registers_t *regs) {
	// Fetch current instruction
	instruction_t curr = cpu_get_instruction(mem, regs->PC);

	// Check if implemented
	if (curr.function == NULL)
		return CPU_UNIMPLEMENTED_INSTRUCTION;

	// Execute the instruction
	curr.function(mem, regs, curr.operand_length);

	return 0;
}
