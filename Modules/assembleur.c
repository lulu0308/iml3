
#include <stdio.h>
#include <string.h>

#include "../LIBHEADERS/analyseur.h"
#include "./HEADERS/table_des_symboles.h"
#include "../LIBHEADERS/mnemoniques.h" /* Code interne des instructions cf Analyseur */

/* Enregistrement contenant une chaine (un pointeur sur un char) et 3 int.
 Utilisé dans des tables des codes operations */

typedef struct s3i
{
	char *name;
	int value1;
	int value2;
	int value3;
} inst_info1;

static inst_info1 table1[] = {
#undef OP
#define OP(NAME, INTERNALCODE, TYPE, OPCODE) {NAME, INTERNALCODE, TYPE, (int)OPCODE},
#include "../CODOPS/ops.h"
};

static model_symbol_table symbol_table;
char *get_opcode(int opcode_id)
{
	for (int i = 0; i <= (sizeof(table1) / sizeof(inst_info1)); i++)
	{
		if (table1[i].value1 == opcode_id)
			return table1[i].name;
	}
}
int is_pseudo(t_asm_line k)
{
	int x = k.inst.instruction.operation_id;
	if ((x == 439) || (x == 430) || (x == 421) || (x == 432) || (x == 425) || (x == 427) || (x == 442) || (x == 423) || (x == 429))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void write_pseudo(t_asm_line *line, FILE *file)
{
	switch (line->inst.instruction.operation_id)
	{
	case 439:
		//move
		fprintf(file, "		addi ");
		fprintf(file, "$%d, ", line->inst.instruction.operand1.reg_number);
		fprintf(file, "$%d, ", line->inst.instruction.operand2.reg_number);
		fprintf(file, "0\n");
		break;
	case 430:
		//la
		fprintf(file, "	 lui ");
		fprintf(file, "$%d, ",line->inst.instruction.operand1.reg_number);
		fprintf(file, "%s\n", line->inst.instruction.operand2.label);
		break;
	case 421:
		//bge
		fprintf(file, "		slt ");
		fprintf(file, "$t0,");
		fprintf(file, "$%d, ", line->inst.instruction.operand2.reg_number);
		fprintf(file, "$%d\n", line->inst.instruction.operand1.reg_number);
		fprintf(file, "		beq ");
		fprintf(file, "$t0,");
		fprintf(file, "$0, ");
		fprintf(file, "%s\n", line->inst.instruction.operand3.label);
		break;
	case 432:
		//li
		fprintf(file, "	lui ");
		fprintf(file, "$%d, ", line->inst.instruction.operand1.reg_number);
		fprintf(file, "%d\n", line->inst.instruction.operand2.value.i_value);
		break;
	case 425:
		//ble
		fprintf(file, "		slt ");
		fprintf(file, "$t0, ");
		fprintf(file, "$%d, ", line->inst.instruction.operand1.reg_number);
		fprintf(file, "$%d\n", line->inst.instruction.operand2.reg_number);
		fprintf(file, "		beq ");
		fprintf(file, "$t0, ");
		fprintf(file, "$0, ");
		fprintf(file, "%s\n", line->inst.instruction.operand3.label);
		break;
	case 427:
		//bgt
		fprintf(file, "		slt ");
		fprintf(file, "$t0,");
		fprintf(file, "$%d, ", line->inst.instruction.operand2.reg_number);
		fprintf(file, "$%d\n", line->inst.instruction.operand1.reg_number);
		fprintf(file, "		bne ");
		fprintf(file, "$t0,");
		fprintf(file, "$0, ");
		fprintf(file, "%s\n", line->inst.instruction.operand3.label);
		break;
	case 442:
		//mul
		fprintf(file, "		mult ");
		fprintf(file, "$%d, ", line->inst.instruction.operand2.reg_number);
		fprintf(file, "$%d\n", line->inst.instruction.operand3.reg_number);
		fprintf(file, "		mflo ");
		fprintf(file, "$%d\n ", line->inst.instruction.operand1.reg_number);
		break;
	case 423:
		//blt
		fprintf(file, "		slt ");
		fprintf(file, "$t0, ");
		fprintf(file, "$%d, ", line->inst.instruction.operand1.reg_number);
		fprintf(file, "$%d\n", line->inst.instruction.operand2.reg_number);
		fprintf(file, "		beq ");
		fprintf(file, "$t0, ");
		fprintf(file, "$0, ");
		fprintf(file, "%s\n", line->inst.instruction.operand3.label);
		break;
	case 429:
		//b
		fprintf(file, "		beq ");
		fprintf(file, "$0, ");
		fprintf(file, "$0, ");
		fprintf(file, "%s\n", line->inst.instruction.operand3.label);
		break;
	}
}

const char *regNumberToRegString(t_operand reg)
{

	if (reg.reg_number == 0)
	{
		return "0";
	}

	if (reg.reg_number == 1)
	{
		return "at";
	}

	if (reg.reg_number == 2)
	{
		return "v0";
	}

	if (reg.reg_number == 3)
	{
		return "v1";
	}

	if (reg.reg_number == 4)
	{
		return "a0";
	}

	if (reg.reg_number == 5)
	{
		return "a1";
	}

	if (reg.reg_number == 6)
	{
		return "a2";
	}

	if (reg.reg_number == 7)
	{
		return "a3";
	}

	if (reg.reg_number == 8)
	{
		return "t0";
	}

	if (reg.reg_number == 9)
	{
		return "t1";
	}

	if (reg.reg_number == 10)
	{
		return "t2";
	}

	if (reg.reg_number == 11)
	{
		return "t3";
	}

	if (reg.reg_number == 12)
	{
		return "t4";
	}

	if (reg.reg_number == 13)
	{
		return "t5";
	}

	if (reg.reg_number == 14)
	{
		return "t6";
	}

	if (reg.reg_number == 15)
	{
		return "t7";
	}

	if (reg.reg_number == 16)
	{
		return "s0";
	}

	if (reg.reg_number == 17)
	{
		return "s1";
	}

	if (reg.reg_number == 18)
	{
		return "s2";
	}

	if (reg.reg_number == 19)
	{
		return "s3";
	}

	if (reg.reg_number == 20)
	{
		return "s4";
	}

	if (reg.reg_number == 21)
	{
		return "s5";
	}

	if (reg.reg_number == 22)
	{
		return "s6";
	}

	if (reg.reg_number == 23)
	{
		return "t7";
	}

	if (reg.reg_number == 24)
	{
		return "t8";
	}

	if (reg.reg_number == 25)
	{
		return "t9";
	}

	if (reg.reg_number == 26)
	{
		return "k0";
	}

	if (reg.reg_number == 27)
	{
		return "k1";
	}

	if (reg.reg_number == 28)
	{
		return "gp";
	}

	if (reg.reg_number == 29)
	{
		return "sp";
	}

	if (reg.reg_number == 30)
	{
		return "fp";
	}

	if (reg.reg_number == 31)
	{
		return "ra";
	}
	///Demande a leon a quoi sert le moins -1
	if (reg.reg_number == -1)
	{
		return "";
	}
}



void print_t_operand(t_operand x)
{
	if (x.mode == 3)
		printf("%s + %d($%s)", x.label, x.value.i_value, regNumberToRegString(x));
	if (x.mode == 2)
		printf(" %d ", x.value.i_value);
	if (x.mode == 1)
		printf(" $%s ", regNumberToRegString(x));

	//printf("\n[ MODE : %d | REG_NUMBER : %d | VALUE : %d | LABEL : %s ]\n",x.mode , x.reg_number , x.value.i_value , x.label);
}

void print_t_instruction(t_instruction x)
{
	//printf("\n[\n OPERATION_ID : %s \n", get_opcode(x.operation_id));
	printf("\t %s ", get_opcode(x.operation_id));
	printf("\t");
	print_t_operand(x.operand1);
	printf("\t");
	print_t_operand(x.operand2);
	printf("\t");
	print_t_operand(x.operand3);
	printf("\n");
}

void print_t_directive(t_directive x)
{

	if (509 == x.directive_id)
	{
		printf(".word %s\n", x.string_operand);
	}

	if (488 == x.directive_id)
	{
		printf(".globl %s\n", x.string_operand);
	}

	if (470 == x.directive_id)
	{
		printf(".asciiz %s\n", x.string_operand);
	}

	if (468 == x.directive_id)
	{
		printf(".align %d\n", x.operands.int_operands->value);
	}

	if (504 == x.directive_id)
	{
		printf(".space %d\n", x.operands.int_operands->value);
	}

	if (476 == x.directive_id)
	{
		printf(".data %s\n", x.string_operand);
	}
}

void print_t_asm_line(t_asm_line *x)
{
	if (x->instruction_type == 2)
	{
		//printf("[ LABEL : %s | COMMENT : %s\n", x->label, x->comment);
		//	printf("\t");
		print_t_instruction(x->inst.instruction);
	}
	if (x->instruction_type == 1)
	{
		//printf("[ LABEL : %s | COMMENT : %s\n", x->label, x->comment);
		//	printf("\t");
		print_t_directive(x->inst.directive);
	}
	if (strlen(x->label))
		printf(" %s :\n", x->label);
}

void fprint_t_operand(t_operand x, FILE *fp)
{
	if (x.mode == 3)
	{
		if (x.value.i_value && strlen(x.label))
			fprintf(fp, "%s + %d($%s)", x.label, x.value.i_value, regNumberToRegString(x));

		if (x.value.i_value)
			fprintf(fp, "%d($%s)", x.value.i_value, regNumberToRegString(x));
		else
			fprintf(fp, "%s ", x.label);
	}
	if (x.mode == 2)
		fprintf(fp, " %d ", x.value.i_value);
	if (x.mode == 1)
		fprintf(fp, " $%s ", regNumberToRegString(x));

	//fprintf(fp,"\n[ MODE : %d | REG_NUMBER : %d | VALUE : %d | LABEL : %s ]\n",x.mode , x.reg_number , x.value.i_value , x.label);
}

void fprint_t_instruction(t_instruction x, FILE *fp)
{
	//fprintf(fp,"\n[\n OPERATION_ID : %s \n", get_opcode(x.operation_id));
	fprintf(fp, "\t %s ", get_opcode(x.operation_id));
	fprintf(fp, "\t");
	fprint_t_operand(x.operand1, fp);
	fprintf(fp, "\t");
	fprint_t_operand(x.operand2, fp);
	fprintf(fp, "\t");
	fprint_t_operand(x.operand3, fp);
	fprintf(fp, "\n");
}

void fprint_t_directive(t_directive x, FILE *fp)
{
	if (509 == x.directive_id)
	{
		fprintf(fp, "  .word %s\n", x.string_operand);
	}

	if (506 == x.directive_id)
	{
		fprintf(fp, "  .text\n");
	}

	if (488 == x.directive_id)
	{
		fprintf(fp, "  .globl %s\n", x.string_operand);
	}

	if (470 == x.directive_id)
	{
		fprintf(fp, ".asciiz %s\n", x.string_operand);
		fprintf(fp, ".asciiz %s\n", x.string_operand);
	}

	if (468 == x.directive_id)
	{
		fprintf(fp, ".align %d\n", x.operands.int_operands->value);
	}

	if (504 == x.directive_id)
	{
		fprintf(fp, ".space %d\n", x.operands.int_operands->value);
	}

	if (476 == x.directive_id)
	{
		fprintf(fp, ".data %s\n", x.string_operand);
	}
}
void fprint_t_asm_line(t_asm_line *x, FILE *fp)
{
	if (x->instruction_type == 2)
	{
		//fprintf(fp,"[ LABEL : %s | COMMENT : %s\n", x->label, x->comment);
		fprintf(fp, "\t");
		if (is_pseudo(*(x)))
		{
			write_pseudo(x, fp);
		}
		else
		{
			fprint_t_instruction(x->inst.instruction, fp);
		}
	}
	if (x->instruction_type == 1)
	{
		//fprintf(fp,"[ LABEL : %s | COMMENT : %s\n", x->label, x->comment);
		fprintf(fp, "  ");
		fprint_t_directive(x->inst.directive, fp);
	}
	if (strlen(x->label))
		fprintf(fp, " %s :\n", x->label);
}

int main(int argc, char **argv)
{

	FILE *fp;
	int i;
	/* open the file for writing*/
	char output_file[MAX_STRING_SIZE];
	//strcat(output_file,"./Modules/");
	strcat(output_file, argv[2]);
	strcat(output_file, "_no_pseudo");
	printf("Le out File est  %s", output_file);
	//fp = fopen(output_file, "w+");
	//fprintf(fp,"HEmlo ");
	/* close the file*/

	test();
	t_asm_line *ligne;

	if (argc < 2)
	{
		printf("preciser le fichier a analyser\n");
		return (1);
	}
	else
	{
		/*PRE-PASSE POUR DEGAGER LES PSEUDO */
		/*		init_parser(argv[1]);
		ligne = get_parsed_line_addr();
		while (!parse_line())
		{
			print_parsed_line(ligne);
		}
		terminate_parser();
*/
		init_parser(argv[1]);
		ligne = get_parsed_line_addr();
		while (!parse_line())
		{
			//	if(ligne->instruction_type ==  2)
			//	printf("MA chaine %d %d %d %s\n",ligne->inst.instruction.operand1.reg_number,ligne->inst.instruction.operand2.reg_number,ligne->inst.instruction.operand3.reg_number,ligne->inst.instruction.operand2.label);
			//print_t_asm_line(ligne);
		//	fprint_t_asm_line(ligne, fp);
			//print_parsed_line(ligne);
		}
		terminate_parser();
		//fclose(fp);
		printf("JARRIVE ICI");
		init_parser(argv[3]);
		ligne = get_parsed_line_addr();
		print_parsed_line(ligne);
		while (!parse_line())
		{
			//	if(ligne->instruction_type ==  2)
			//	printf("MA chaine %d %d %d %s\n",ligne->inst.instruction.operand1.reg_number,ligne->inst.instruction.operand2.reg_number,ligne->inst.instruction.operand3.reg_number,ligne->inst.instruction.operand2.label);
			//print_t_asm_line(ligne);
			//fprint_t_asm_line(ligne, fp);
			print_parsed_line(ligne);
		}
		terminate_parser();
		return (0);

		return (0);
	}

	fclose(fp);
}