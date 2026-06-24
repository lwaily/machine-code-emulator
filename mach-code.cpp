#include "mach-code.hpp"

void reg::incr_pc(){
	reg_arr[15] += 4;
}

int main(){
	// Local Variables
	std::string  input_str;
	unsigned int inst = 4294967295;
	
	// Receive User Input
	std::cout << "Each instruction should be represented as:" << std::endl;
	std::cout << "0b<COND>_<OPCD>_<I>001_<DEST>_<OPR1>_<OPER_2REG_IMME>" << std::endl;
	std::cout << "Input Instructions:            v" << std::endl;
	
	while (std::cin >> input_str && input_str != "exit") {
		if(input_str.size() == 32){
			// This converts the string of 1s and 0s into a 32-bit unsigned int
			std::bitset<32> bits(input_str);
			inst = static_cast<unsigned int>(bits.to_ulong());
			// 
			instr my_instr(inst);
			program.push_back(my_instr);
		} else {
			std::cout << "Invalid Input (Must be 32-bits long)" << std::endl;
		}
	}

	// Creates a reg object
	reg my_reg;
/*	
	// TEST
	std::cout << "----  TEST  ----" << std::endl;
	for(unsigned int i = 0; i < program.size(); ++i){
		std::cout <<
				program[i].condition		<< " " <<
				program[i].opcode			<< " " <<
				program[i].immediate_bit	<< " " <<
				program[i].dest_reg			<< " " <<
				program[i].oper1_reg		<< " " <<
				program[i].oper2			<< " " 
				<< std::endl;
	}
*/
	// Parse through instructions and ``execute" them
	for(unsigned int i = 0; i < program.size(); ++i){
		if(program[i].opcode == NEG){
			std::cout << "NEG" << std::endl;
		} else if(program[i].opcode == AND){
			if(program[i].immediate_bit == 0){
				int rn  = (int)program[i].oper1_reg;
				int op = (int)program[i].oper2;
				my_reg.reg_arr[(int)program[i].dest_reg]
						= my_reg.reg_arr[rn] & my_reg.reg_arr[op];
			} else if(program[i].immediate_bit == 1){
				int rn  = (int)program[i].oper1_reg;
				int imm = (int)program[i].oper2;
				my_reg.reg_arr[(int)program[i].dest_reg]
						= my_reg.reg_arr[rn] & imm;
			}
		} else if(program[i].opcode == ORR){
			if(program[i].immediate_bit == 0){
				int rn  = (int)program[i].oper1_reg;
				int op = (int)program[i].oper2;
				my_reg.reg_arr[(int)program[i].dest_reg]
						= my_reg.reg_arr[rn] | my_reg.reg_arr[op];
			} else if(program[i].immediate_bit == 1){
				int rn  = (int)program[i].oper1_reg;
				int imm = (int)program[i].oper2;
				my_reg.reg_arr[(int)program[i].dest_reg]
						= my_reg.reg_arr[rn] | imm;
			}
		} else if(program[i].opcode == XOR){
			if(program[i].immediate_bit == 0){
				int rn  = (int)program[i].oper1_reg;
				int op = (int)program[i].oper2;
				my_reg.reg_arr[(int)program[i].dest_reg]
						= my_reg.reg_arr[rn] ^ my_reg.reg_arr[op];
			} else if(program[i].immediate_bit == 1){
				int rn  = (int)program[i].oper1_reg;
				int imm = (int)program[i].oper2;
				my_reg.reg_arr[(int)program[i].dest_reg]
						= my_reg.reg_arr[rn] ^ imm;
			}
		} else if(program[i].opcode == BIC){
			//
		} else if(program[i].opcode == LSR){
			//
		} else if(program[i].opcode == ASR){
			//
		} else if(program[i].opcode == LSL){
			//
		} else if(program[i].opcode == ADD){
			if(program[i].immediate_bit == 0){
				int rn = (int)program[i].oper1_reg;
				int op = (int)program[i].oper2;
				my_reg.reg_arr[(int)program[i].dest_reg]
						= my_reg.reg_arr[rn] + my_reg.reg_arr[op];
			} else if(program[i].immediate_bit == 1){
				int imm = (int)program[i].oper2;
				int rn  = (int)program[i].oper1_reg;
				my_reg.reg_arr[(int)program[i].dest_reg]
						= my_reg.reg_arr[rn] + imm;
			}
		} else if(program[i].opcode == SUB){
			if(program[i].immediate_bit == 0){
				int rn = (int)program[i].oper1_reg;
				int op = (int)program[i].oper2;
				my_reg.reg_arr[(int)program[i].dest_reg]
						= my_reg.reg_arr[rn] - my_reg.reg_arr[op];
			} else if(program[i].immediate_bit == 1){
				int imm = (int)program[i].oper2;
				int rn  = (int)program[i].oper1_reg;
				my_reg.reg_arr[(int)program[i].dest_reg]
						= my_reg.reg_arr[rn] - imm;
			}
		} else if(program[i].opcode == MOV){
			if(program[i].immediate_bit == 0){
				int value = (int)program[i].oper2;
				my_reg.reg_arr[(int)program[i].dest_reg] = my_reg.reg_arr[value];
			} else if(program[i].immediate_bit == 1){
				int value = (int)program[i].oper2;
				my_reg.reg_arr[(int)program[i].dest_reg] = value;
			}
		} else if(program[i].opcode == MVN){
			//
		} else if(program[i].opcode == LDR){
			//
		} else if(program[i].opcode == STR){
			//
		} else if(program[i].opcode == CMP){
			/**
			 * cmp a, b
			 * \where a is rd, b is oper2
			 *	Will have to utilize r12 for this as I have no other
			 *		use for it right now.
			 * ========  POSSIBLE  SCHEME  =========================
			 * +========+===========+===============+
			 * | SUFFIX	| SYMBOL	| FLAG			|
			 * +--------+-----------+---------------+
			 * | EQ		| (==)		| r12 = 0x001	|
			 * +--------+-----------+---------------+
			 * | NE		| (!=)		| r12 = 0x010	|
			 * +--------+-----------+---------------+
			 * | GE 	| (>=) 		| r12 = 0x011	|
			 * +--------+-----------+---------------+
			 * | GT 	| (>)		| r12 = 0x100	|
			 * +--------+-----------+---------------+
			 * | LE 	| (<=)		| r12 = 0x101	|
			 * +--------+-----------+---------------+
			 * | LT 	| (<)		| r12 = 0x110	|
			 * +--------+-----------+---------------+
			 */
			if(program[i].immediate_bit == 0){
				int rd_value = my_reg.reg_arr[(int)program[i].dest_reg];
				int op_value = (int)program[i].oper2;
				if(rd_value == op_value) { my_reg.reg_arr[12] |= 0x001; }
				else if(rd_value > op_value) { my_reg.reg_arr[12] |= 0x001; }
				else if(rd_value < op_value) { my_reg.reg_arr[12] |= 0x001; }
				else if(rd_value == op_value) { my_reg.reg_arr[12] |= 0x001; }
				else if(rd_value == op_value) { my_reg.reg_arr[12] |= 0x001; }
				else if(rd_value == op_value) { my_reg.reg_arr[12] |= 0x001; }
			} else if(program[i].immediate_bit == 1){
				int rd_value  = my_reg.reg_arr[(int)program[i].dest_reg];
				int imm_vaule = (int)program[i].oper2;
				//
			}
		} else if(program[i].opcode == B){
			//
		}
		my_reg.incr_pc();
	}

	std::cout << "-=-=-=- FINAL REGISTER VALUES -=-=-=-" << std::endl;
	for(int j = 0; j < 16; ++j){
		std::cout << "\tr" << j << "\t" << my_reg.reg_arr[j] << std::endl;
	}

	return 0;
}

