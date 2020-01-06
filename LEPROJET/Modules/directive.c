void deal_directive(t_asm_line line)
{

	if(line.instruction_type == ASM_DIRECTIVE)
	{
		if(509 == directive_id)
		{
			printf(".word %s", string_operand);
		}

		if(488 == directive_id)
		{
			printf(".glbl %s", string_operand);
		}

		if(470 == directive_id)
		{
			printf(".asciiz %s", string_operand);
		}

		if(468 == directive_id)
		{
			printf(".align %d", int_operand);
		}

		if(504 == directive_id)
		{
			printf(".space %d", int_operand);
		}

		if(476 == directive_id)
		{
			printf(".data %s", string_operand);
		}
	}
}
