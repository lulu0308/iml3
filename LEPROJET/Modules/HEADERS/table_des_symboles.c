#include "table_des_symboles.h"
#include <stdio.h>

void test(){
    printf("HelloWorld");
}

static int i;
int insert_symbol(t_asm_line line, model_symbol_table symtable)
{
	symtable.table[i].label = line.label;
	symtable.table[i].valeur = line.inst.operand3;//.value
	symtable.table[i].status = line.instruction_type;
	symtable.table[i].scope = line. ??
	i++;
}


int recherche(t_asm_line line, model_symbol_table symtable)
{
	for (int i = 0; i < effective_size; i++)
	{
		if(line == symtable.table[i])
		{
			return true;
		}else{
			return false;
		}
}
