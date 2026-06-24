/**
 * Name:  Ali Alwaily
 * Date:  24 June 2026
 * About: 
 */

#ifndef MC_H
#define MC_H

#include <iostream>
#include <string>
#include <vector>
#include <bitset>

/** 
 * Register Class
 * 		Registers here are represented as integer data types, which are 32-bits
 *		long, or 4 bytes. I have mostly followed ARM architure in the way I set
 *		up the purpose of every register.
 *		Every register is accessed through the reg_arr[] array.
 */
class reg {
	public:
		/**
		 * Structure of the Register array reg_arr[]
		 */
		int reg_arr[16];
		/**
		 * Constructor that initializes the registers.
		 */
		reg(){
			/**
			 * ----------  SCHEME  --------------------------------------------
			 * REG_0  = General Purpose, Argument, Return Value [Not Preserved]
			 * REG_1  = General Purpose, Argument 				[Not Preserved]
			 * REG_2  = General Purpose, Argument 				[Not Preserved]
			 * REG_3  = General Purpose, Argument 				[Not Preserved]
			 * REG_4  = General Purpose							[Preserved]
			 * REG_5  = General Purpose 						[Preserved]
			 * REG_6  = General Purpose 						[Preserved]
			 * REG_7  = General Purpose 						[Preserved]
			 * REG_8  = General Purpose 						[Preserved]
			 * REG_9  = General Purpose 						[Preserved]
			 * REG_10 = General Purpose 						[Preserved]
			 * REG_11 = Frame Pointer 							[Preserved]
			 * REG_12 = Instra Procedure Call 					[Not Preserved]
			 * REG_13 = Stack Pointer  							[Preserved]
			 * REG_14 = Link Register 							[Preserved]
			 * REG_15 = Program Counter 						[Not Preserved]
			 *
			 * ----------  STRUCTURE  OF  A  REGISTER  ------------------------
			 * +============+=======+=======================+
			 * | INDEX BIT	| FLAG	| DESCRIPTION			|
			 * +------------+-------+-----------------------+
			 * | 31			| N 	| Negative				|
			 * +------------+-------+-----------------------+
			 * | 30			| Z		| Zero					|
			 * +------------+-------+-----------------------+
			 * | 29			| C		| Carry-out				|
			 * +------------+-------+-----------------------+
			 * | 28			| V		| oVerflow				|
			 * +------------+-------+-----------------------+
			 * | 15-0		| A		| Integer Value the		|
			 * |			|		|  register contains	|
			 * +------------+-------+-----------------------+
			 */
			for(int i = 0; i < 16; ++i) { reg_arr[i] |= 0x0000ffff; }
			reg_arr[11] = 0;
			reg_arr[12] = 0;
			reg_arr[13] = 0;
			reg_arr[14] = 0;
			reg_arr[15] = 4;
		}
		void incr_pc();
};

/**
 * Instructions Class
 *		This class is used to parse through every 32-bit input and break it up 
 *		into 6 categories:
 *			Condition:			[See Enum Defined Below]
 *			Operation Code:		[See Enum Defined Below]
 *			Immediate Bit:		For any instruction other than branching:
 * 								If 0, operand 2 will be treated as a register,
 *								If 1, operand 2 will be treated as an immediate.
 *								For Branching,
 *								If 0, branch will not link,
 *								If 1, this will represent branching and linking.
 *			Destination Reg:	//
 *			Oper1:				//
 *			Oper2:				//
 */
class instr {
	public:
		/**
		 * 0b COND_OPCD_I001_DEST_OPR1_OPER_2REG_IMME
		 */
		unsigned int condition;			// COND
		unsigned int opcode;			// OPCD
		unsigned int immediate_bit;		// I
		unsigned int dest_reg;			// DEST
		unsigned int oper1_reg;			// OPR1
		unsigned int oper2;				// OPER_2REG_IMME
		
		/**
		 * Constructor
		 * @PARAM1:	//
		 */
		instr(unsigned int value){
			condition		= (value & 0xf0000000) >> 28;
			opcode			= (value & 0x0f000000) >> 24;
			immediate_bit	= (value & 0x00800000) >> 23;
			dest_reg		= (value & 0x000f0000) >> 16;
			oper1_reg		= (value & 0x0000f000) >> 12;
			oper2			= (value & 0x00000fff);
		}
};

/**
 * Condition Enum that represents the value of every condition
 */
enum cond {
	EQ = 0,		// =  equal to
	NE = 1,		// != not equal to
	LT = 2,		// <  less than
	LE = 3,		// <= less than or equal to
	GT = 4,		// >  greater than
	GE = 5,		// >= greater than or equal to
	AL = 6,		// ALWAYS
};

/** 
 * Op_code Enum that represents the value of every operation code
 */
enum op_code {
	// Logical Operations
	NEG = 0, 	// negates the value (or, flips every bit)
	AND = 1,	// &&
	ORR = 2,	// ||
	XOR = 3,	// ^
	BIC = 4,	// 
	LSR = 5,	//
	ASR = 6,	//
	LSL = 7,	//
	// Arithmetic Operations
	ADD = 8,	// +
	SUB = 9,	// -
	MOV = 10,	// 
	MVN = 11,	// 
	// Data Transfer
	LDR = 12,	//
	STR = 13,	//
	// Control Flow
	CMP = 14,	//
	B	= 15,	//
};

/**
 * A global vector that holds the instructions for a program.
 */
std::vector<instr> program;

#endif
