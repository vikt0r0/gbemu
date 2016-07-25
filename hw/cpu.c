#include <stdio.h>

#include "cpu.h"
#include "memory.h"
#include "../core/types.h"

// TODO: Implement ad-hoc, add CB instructions!
// Disassembly from http://imrannazar.com/Gameboy-Z80-Opcode-Map

void nop(memory_t *mem, registers_t *regs) {
	// Update the program counter
	regs->PC++;
}

void ld_bc_nn(memory_t *mem, registers_t *regs) {
	// Get operands, here 8 bytes.
	regs->BC = memory_read_word(mem, (regs->PC)+1);
	regs->PC += 3;
}

void ld_sp_nn(memory_t *mem, registers_t *regs) {
	// Get operands, here 8 bytes.
	regs->SP = memory_read_word(mem, (regs->PC)+1);
	regs->PC += 3;
}

void ld_hl_nn(memory_t *mem, registers_t *regs) {
	// Get operands, here 8 bytes.
	regs->HL = memory_read_word(mem, (regs->PC)+1);
	regs->PC += 3;
}

void xor_a(memory_t *mem, registers_t *regs) {
	regs->A ^= regs->A;
	regs->PC++;
}

void xor_b(memory_t *mem, registers_t *regs) {
	regs->A ^= regs->B;
	regs->PC++;
}

void xor_c(memory_t *mem, registers_t *regs) {
	regs->A ^= regs->C;
	regs->PC++;
}

void xor_d(memory_t *mem, registers_t *regs) {
	regs->A ^= regs->D;
	regs->PC++;
}

void xor_e(memory_t *mem, registers_t *regs) {
	regs->A ^= regs->E;
	regs->PC++;
}

void xor_h(memory_t *mem, registers_t *regs) {
	regs->A ^= regs->H;
	regs->PC++;
}

void xor_l(memory_t *mem, registers_t *regs) {
	regs->A ^= regs->L;
	regs->PC++;
}

void xor_addr_hl(memory_t *mem, registers_t *regs) {
	ubyte_t op = memory_read_byte(mem, (regs->HL));
	regs->A ^= op;
	regs->PC++;
}

void xor_n(memory_t *mem, registers_t *regs) {
	ubyte_t op = memory_read_byte(mem, (regs->HL));
	regs->A ^= op;
	regs->PC++;
}

void ld_addr_hl_a(memory_t *mem, registers_t *regs) {
	// Write contents of a to (HL)
	memory_write_word(mem, regs->HL, regs->A);
	// Decrement HL
	regs->HL--;
	regs->PC++;
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
	{ "LD HL, 0x%04X", ld_hl_nn, 2 },
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
	{ "LDD (HL), A", ld_addr_hl_a, 0 },
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
	{ "AND A", xor_a, 0 },
	{ "XOR B", xor_b, 0 },
	{ "XOR C", xor_c, 0 },
	{ "XOR D", xor_d, 0 },
	{ "XOR E", xor_e, 0 },
	{ "XOR H", xor_h, 0 },
	{ "XOR L", xor_l, 0 },
	{ "XOR (HL)", xor_addr_hl, 0 },
	{ "XOR A", xor_a, 0 },

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

void bit_n_r(registers_t *regs, ubyte_t n, ubyte_t *r) {
	ubyte_t mask = 1 << n;
	regs->flags.Z = (mask & *r) ? 0 : 1;
	regs->flags.H = 1;
	regs->flags.N = 0;
	regs->PC += 2;
}

void bit_7_h(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 7, &(regs->H));
}

void bit_6_h(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 6, &(regs->H));
}

void bit_5_h(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 5, &(regs->H));
}

void bit_4_h(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 4, &(regs->H));
}

void bit_3_h(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 3, &(regs->H));
}

void bit_2_h(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 2, &(regs->H));
}

void bit_1_h(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 1, &(regs->H));
}

void bit_0_h(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 0, &(regs->H));
}

void bit_7_b(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 7, &(regs->B));
}

void bit_6_b(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 6, &(regs->B));
}

void bit_5_b(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 5, &(regs->B));
}

void bit_4_b(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 4, &(regs->B));
}

void bit_3_b(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 3, &(regs->B));
}

void bit_2_b(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 2, &(regs->B));
}

void bit_1_b(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 1, &(regs->B));
}

void bit_0_b(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 0, &(regs->B));
}

void bit_7_c(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 7, &(regs->C));
}

void bit_6_c(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 6, &(regs->C));
}

void bit_5_c(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 5, &(regs->C));
}

void bit_4_c(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 4, &(regs->C));
}

void bit_3_c(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 3, &(regs->C));
}

void bit_2_c(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 2, &(regs->C));
}

void bit_1_c(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 1, &(regs->C));
}

void bit_0_c(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 0, &(regs->C));
}

void bit_7_d(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 7, &(regs->D));
}

void bit_6_d(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 6, &(regs->D));
}

void bit_5_d(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 5, &(regs->D));
}

void bit_4_d(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 4, &(regs->D));
}

void bit_3_d(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 3, &(regs->D));
}

void bit_2_d(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 2, &(regs->D));
}

void bit_1_d(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 1, &(regs->D));
}

void bit_0_d(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 0, &(regs->D));
}

void bit_7_e(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 7, &(regs->E));
}

void bit_6_e(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 6, &(regs->E));
}

void bit_5_e(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 5, &(regs->E));
}

void bit_4_e(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 4, &(regs->E));
}

void bit_3_e(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 3, &(regs->E));
}

void bit_2_e(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 2, &(regs->E));
}

void bit_1_e(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 1, &(regs->E));
}

void bit_0_e(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 0, &(regs->E));
}

void bit_7_l(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 7, &(regs->L));
}

void bit_6_l(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 6, &(regs->L));
}

void bit_5_l(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 5, &(regs->L));
}

void bit_4_l(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 4, &(regs->L));
}

void bit_3_l(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 3, &(regs->L));
}

void bit_2_l(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 2, &(regs->L));
}

void bit_1_l(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 1, &(regs->L));
}

void bit_0_l(memory_t *mem, registers_t *regs) {
	bit_n_r(regs, 0, &(regs->L));
}

instruction_t cpu_extended_instructions[256] = {
	{ "RLC B", NULL, 0 },
	{ "RLC C", NULL, 0 },
	{ "RLC D", NULL, 0 },
	{ "RLC E", NULL, 0 },
	{ "RLC H", NULL, 0 },
	{ "RLC L", NULL, 0 },
	{ "RLC (HL)", NULL, 0 },
	{ "RLC A", NULL, 0 },
	{ "RRC B", NULL, 0 },
	{ "RRC C", NULL, 0 },
	{ "RRC D", NULL, 0 },
	{ "RRC E", NULL, 0 },
	{ "RRC H", NULL, 0 },
	{ "RRC L", NULL, 0 },
	{ "RRC (HL)", NULL, 0 },
	{ "RRC A", NULL, 0 },

	{ "RL B", NULL, 0 },
	{ "RL C", NULL, 0 },
	{ "RL D", NULL, 0 },
	{ "RL E", NULL, 0 },
	{ "RL H", NULL, 0 },
	{ "RL L", NULL, 0 },
	{ "RL (HL)", NULL, 0 },
	{ "RL A", NULL, 0 },
	{ "RR B", NULL, 0 },
	{ "RR C", NULL, 0 },
	{ "RR D", NULL, 0 },
	{ "RR E", NULL, 0 },
	{ "RR H", NULL, 0 },
	{ "RR L", NULL, 0 },
	{ "RR (HL)", NULL, 0 },
	{ "RR A", NULL, 0 },

	{ "SLA B", NULL, 0 },
	{ "SLA C", NULL, 0 },
	{ "SLA D", NULL, 0 },
	{ "SLA E", NULL, 0 },
	{ "SLA H", NULL, 0 },
	{ "SLA L", NULL, 0 },
	{ "SLA (HL)", NULL, 0 },
	{ "SLA A", NULL, 0 },
	{ "SRA B", NULL, 0 },
	{ "SRA C", NULL, 0 },
	{ "SRA D", NULL, 0 },
	{ "SRA E", NULL, 0 },
	{ "SRA H", NULL, 0 },
	{ "SRA L", NULL, 0 },
	{ "SRA (HL)", NULL, 0 },
	{ "SRA A", NULL, 0 },

	{ "SWAP B", NULL, 0 },
	{ "SWAP C", NULL, 0 },
	{ "SWAP D", NULL, 0 },
	{ "SWAP E", NULL, 0 },
	{ "SWAP H", NULL, 0 },
	{ "SWAP L", NULL, 0 },
	{ "SWAP (HL)", NULL, 0 },
	{ "SWAP A", NULL, 0 },
	{ "SRL B", NULL, 0 },
	{ "SRL C", NULL, 0 },
	{ "SRL D", NULL, 0 },
	{ "SRL E", NULL, 0 },
	{ "SRL H", NULL, 0 },
	{ "SRL L", NULL, 0 },
	{ "SRL (HL)", NULL, 0 },
	{ "SRL A", NULL, 0 },

	{ "BIT 0,B", NULL, 0 },
	{ "BIT 0,C", NULL, 0 },
	{ "BIT 0,D", NULL, 0 },
	{ "BIT 0,E", NULL, 0 },
	{ "BIT 0,H", NULL, 0 },
	{ "BIT 0,L", NULL, 0 },
	{ "BIT 0,(HL)", NULL, 0 },
	{ "BIT 0,A", NULL, 0 },
	{ "BIT 1,B", NULL, 0 },
	{ "BIT 1,C", NULL, 0 },
	{ "BIT 1,D", NULL, 0 },
	{ "BIT 1,E", NULL, 0 },
	{ "BIT 1,H", NULL, 0 },
	{ "BIT 1,L", NULL, 0 },
	{ "BIT 1,(HL)", NULL, 0 },
	{ "BIT 1,A", NULL, 0 },

	{ "BIT 2,B", NULL, 0 },
	{ "BIT 2,C", NULL, 0 },
	{ "BIT 2,D", NULL, 0 },
	{ "BIT 2,E", NULL, 0 },
	{ "BIT 2,H", NULL, 0 },
	{ "BIT 2,L", NULL, 0 },
	{ "BIT 2,(HL)", NULL, 0 },
	{ "BIT 2,A", NULL, 0 },
	{ "BIT 3,B", NULL, 0 },
	{ "BIT 3,C", NULL, 0 },
	{ "BIT 3,D", NULL, 0 },
	{ "BIT 3,E", NULL, 0 },
	{ "BIT 3,H", NULL, 0 },
	{ "BIT 3,L", NULL, 0 },
	{ "BIT 3,(HL)", NULL, 0 },
	{ "BIT 3,A", NULL, 0 },

	{ "BIT 4,B", NULL, 0 },
	{ "BIT 4,C", NULL, 0 },
	{ "BIT 4,D", NULL, 0 },
	{ "BIT 4,E", NULL, 0 },
	{ "BIT 4,H", NULL, 0 },
	{ "BIT 4,L", NULL, 0 },
	{ "BIT 4,(HL)", NULL, 0 },
	{ "BIT 4,A", NULL, 0 },
	{ "BIT 5,B", NULL, 0 },
	{ "BIT 5,C", NULL, 0 },
	{ "BIT 5,D", NULL, 0 },
	{ "BIT 5,E", NULL, 0 },
	{ "BIT 5,H", NULL, 0 },
	{ "BIT 5,L", NULL, 0 },
	{ "BIT 5,(HL)", NULL, 0 },
	{ "BIT 5,A", NULL, 0 },

	{ "BIT 6,B", NULL, 0 },
	{ "BIT 6,C", NULL, 0 },
	{ "BIT 6,D", NULL, 0 },
	{ "BIT 6,E", NULL, 0 },
	{ "BIT 6,H", NULL, 0 },
	{ "BIT 6,L", NULL, 0 },
	{ "BIT 6,(HL)", NULL, 0 },
	{ "BIT 6,A", NULL, 0 },
	{ "BIT 7,B", NULL, 0 },
	{ "BIT 7,C", NULL, 0 },
	{ "BIT 7,D", NULL, 0 },
	{ "BIT 7,E", NULL, 0 },
	{ "BIT 7,H", bit_7_h, 0 },
	{ "BIT 7,L", NULL, 0 },
	{ "BIT 7,(HL)", NULL, 0 },
	{ "BIT 7,A", NULL, 0 },

	{ "RES 0,B", NULL, 0 },
	{ "RES 0,C", NULL, 0 },
	{ "RES 0,D", NULL, 0 },
	{ "RES 0,E", NULL, 0 },
	{ "RES 0,H", NULL, 0 },
	{ "RES 0,L", NULL, 0 },
	{ "RES 0,(HL)", NULL, 0 },
	{ "RES 0,A", NULL, 0 },
	{ "RES 1,B", NULL, 0 },
	{ "RES 1,C", NULL, 0 },
	{ "RES 1,D", NULL, 0 },
	{ "RES 1,E", NULL, 0 },
	{ "RES 1,H", NULL, 0 },
	{ "RES 1,L", NULL, 0 },
	{ "RES 1,(HL)", NULL, 0 },
	{ "RES 1,A", NULL, 0 },

	{ "RES 2,B", NULL, 0 },
	{ "RES 2,C", NULL, 0 },
	{ "RES 2,D", NULL, 0 },
	{ "RES 2,E", NULL, 0 },
	{ "RES 2,H", NULL, 0 },
	{ "RES 2,L", NULL, 0 },
	{ "RES 2,(HL)", NULL, 0 },
	{ "RES 2,A", NULL, 0 },
	{ "RES 3,B", NULL, 0 },
	{ "RES 3,C", NULL, 0 },
	{ "RES 3,D", NULL, 0 },
	{ "RES 3,E", NULL, 0 },
	{ "RES 3,H", NULL, 0 },
	{ "RES 3,L", NULL, 0 },
	{ "RES 3,(HL)", NULL, 0 },
	{ "RES 3,A", NULL, 0 },

	{ "RES 4,B", NULL, 0 },
	{ "RES 4,C", NULL, 0 },
	{ "RES 4,D", NULL, 0 },
	{ "RES 4,E", NULL, 0 },
	{ "RES 4,H", NULL, 0 },
	{ "RES 4,L", NULL, 0 },
	{ "RES 4,(HL)", NULL, 0 },
	{ "RES 4,A", NULL, 0 },
	{ "RES 5,B", NULL, 0 },
	{ "RES 5,C", NULL, 0 },
	{ "RES 5,D", NULL, 0 },
	{ "RES 5,E", NULL, 0 },
	{ "RES 5,H", NULL, 0 },
	{ "RES 5,L", NULL, 0 },
	{ "RES 5,(HL)", NULL, 0 },
	{ "RES 5,A", NULL, 0 },

	{ "RES 6,B", NULL, 0 },
	{ "RES 6,C", NULL, 0 },
	{ "RES 6,D", NULL, 0 },
	{ "RES 6,E", NULL, 0 },
	{ "RES 6,H", NULL, 0 },
	{ "RES 6,L", NULL, 0 },
	{ "RES 6,(HL)", NULL, 0 },
	{ "RES 6,A", NULL, 0 },
	{ "RES 7,B", NULL, 0 },
	{ "RES 7,C", NULL, 0 },
	{ "RES 7,D", NULL, 0 },
	{ "RES 7,E", NULL, 0 },
	{ "RES 7,H", NULL, 0 },
	{ "RES 7,L", NULL, 0 },
	{ "RES 7,(HL)", NULL, 0 },
	{ "RES 7,A", NULL, 0 },

	{ "SET 0,B", NULL, 0 },
	{ "SET 0,C", NULL, 0 },
	{ "SET 0,D", NULL, 0 },
	{ "SET 0,E", NULL, 0 },
	{ "SET 0,H", NULL, 0 },
	{ "SET 0,L", NULL, 0 },
	{ "SET 0,(HL)", NULL, 0 },
	{ "SET 0,A", NULL, 0 },
	{ "SET 1,B", NULL, 0 },
	{ "SET 1,C", NULL, 0 },
	{ "SET 1,D", NULL, 0 },
	{ "SET 1,E", NULL, 0 },
	{ "SET 1,H", NULL, 0 },
	{ "SET 1,L", NULL, 0 },
	{ "SET 1,(HL)", NULL, 0 },
	{ "SET 1,A", NULL, 0 },

	{ "SET 2,B", NULL, 0 },
	{ "SET 2,C", NULL, 0 },
	{ "SET 2,D", NULL, 0 },
	{ "SET 2,E", NULL, 0 },
	{ "SET 2,H", NULL, 0 },
	{ "SET 2,L", NULL, 0 },
	{ "SET 2,(HL)", NULL, 0 },
	{ "SET 2,A", NULL, 0 },
	{ "SET 3,B", NULL, 0 },
	{ "SET 3,C", NULL, 0 },
	{ "SET 3,D", NULL, 0 },
	{ "SET 3,E", NULL, 0 },
	{ "SET 3,H", NULL, 0 },
	{ "SET 3,L", NULL, 0 },
	{ "SET 3,(HL)", NULL, 0 },
	{ "SET 3,A", NULL, 0 },

	{ "SET 4,B", NULL, 0 },
	{ "SET 4,C", NULL, 0 },
	{ "SET 4,D", NULL, 0 },
	{ "SET 4,E", NULL, 0 },
	{ "SET 4,H", NULL, 0 },
	{ "SET 4,L", NULL, 0 },
	{ "SET 4,(HL)", NULL, 0 },
	{ "SET 4,A", NULL, 0 },
	{ "SET 5,B", NULL, 0 },
	{ "SET 5,C", NULL, 0 },
	{ "SET 5,D", NULL, 0 },
	{ "SET 5,E", NULL, 0 },
	{ "SET 5,H", NULL, 0 },
	{ "SET 5,L", NULL, 0 },
	{ "SET 5,(HL)", NULL, 0 },
	{ "SET 5,A", NULL, 0 },

	{ "SET 6,B", NULL, 0 },
	{ "SET 6,C", NULL, 0 },
	{ "SET 6,D", NULL, 0 },
	{ "SET 6,E", NULL, 0 },
	{ "SET 6,H", NULL, 0 },
	{ "SET 6,L", NULL, 0 },
	{ "SET 6,(HL)", NULL, 0 },
	{ "SET 6,A", NULL, 0 },
	{ "SET 7,B", NULL, 0 },
	{ "SET 7,C", NULL, 0 },
	{ "SET 7,D", NULL, 0 },
	{ "SET 7,E", NULL, 0 },
	{ "SET 7,H", NULL, 0 },
	{ "SET 7,L", NULL, 0 },
	{ "SET 7,(HL)", NULL, 0 },
	{ "SET 7,A", NULL, 0 }
};

instruction_t cpu_get_instruction(memory_t *mem, uword_t addr) {
	return cpu_instructions[memory_read_byte(mem, addr)];
}

instruction_t cpu_get_extended_instruction(memory_t *mem, uword_t addr) {
	return cpu_extended_instructions[memory_read_byte(mem, addr+1)];
}

char* cpu_get_disassembly(memory_t *mem, uword_t addr) {

	instruction_t instruction;

    if (memory_read_byte(mem, addr) == CPU_EXTENDED_OPCODE)
    	instruction = cpu_get_extended_instruction(mem, addr);
    else
    	instruction = cpu_get_instruction(mem, addr);

	char *disassembly;

	// Create the disassembly
	switch (instruction.operand_length) {
		case 0:
			asprintf(&disassembly, instruction.disassembly, NULL);
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
	// Current instruction to interpret
	instruction_t curr;

	// Fetch current instruction
	if (memory_read_byte(mem, regs->PC) == CPU_EXTENDED_OPCODE)
		curr = cpu_get_extended_instruction(mem, regs->PC);
	else
		curr = cpu_get_instruction(mem, regs->PC);

	// Check if implemented
	if (curr.function == NULL)
		return CPU_UNIMPLEMENTED_INSTRUCTION;

	// Execute the instruction
	curr.function(mem, regs);

	return 0;
}
