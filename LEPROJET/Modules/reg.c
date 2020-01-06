char * trad_reg(t_operand reg)
{

	if (reg.reg_number == 0)
	{
		return "0";
	}

	if (reg.reg_number == 1)
	{
		return"at";
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
		return"t0";
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

}
