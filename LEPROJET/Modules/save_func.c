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