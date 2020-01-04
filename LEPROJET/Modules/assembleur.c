
#include <stdio.h>

#include "../LIBHEADERS/analyseur.h"
#include "table_des_symboles.h"
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

void print_t_operand(t_operand x)
{
	if (x.mode == 3)
		printf("%s + %d($%d)", x.label, x.value.i_value, x.reg_number);
	if (x.mode == 2)
		printf(" %d ", x.value.i_value);
	if (x.mode == 1)
		printf(" $%d ", x.reg_number);

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

void print_t_asm_line(t_asm_line *x)
{
	if (x->instruction_type != -1)
	{
		//printf("[ LABEL : %s | COMMENT : %s\n", x->label, x->comment);
	//	printf("\t");
		print_t_instruction(x->inst.instruction);
	}
	printf(" %s ", x->label);
}

int main(int argc, char **argv)
{

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
			print_t_asm_line(ligne);
			print_parsed_line(ligne);
		}
		terminate_parser();
		return (0);
	}
}


static int compteur1;
function passe1(t_asm_line line, t_asm_directive directive)
{
  while (!fin-de-fichier())
  {
    parse_line();
    if (line != '#')
    {
      if (&line == line.label)
      {
        if (recherche(line.label))
        {
          printf("erreur double définition");
        }else{
          insert_symbol (line.label, inst_info1 table1 []);
          compteur1 ++;
        }
      }
      if (line.instruction_type == ASM_DIRECTIVE)
      {
        lg_data = line.directive.int_operands;
        compteur1 = compteur1 + lg_data;
      }
      if (!recherche(line.label))
      {
        insert.symbol(line.label, inst_info1 table1 []);
      }
      if (line.label = .globl)
          if (!recherche(line.label))
          {
            insert_symbol (line.label, inst_info1 table1 []);
          }else{
            modif_table();
          }
      }
      if (line.instruction_type == NONE)
      {
        compteur1 == 0;
        /* entrer le nom section dans TS*/
      }
      if (line.instruction_type == ASM_INSTRUCTION)
      {
        if (valide)
        {
        lg_instr = 4;
        compteur1 = compteur1 + lg_instr;
        }else{
          printf("erreur instruction invalide");
        }
      }
    }
  }
}


static int compteur2;  
function passe2(){
  while (!fin-de-fichier())
  {
    parse_line();
    if (line != '#')
    {
      if (line.instruction_type == NONE)
      {
        compteur1 == 0;
        /* mettre à jour l'entête*/
      }
      if (line.instruction_type == ASM_INSTRUCTION)
      {
        lg_instr = 4;
        //assembler instr
        //ecrire code instr
        compteur2 = compteur2 + lg_instr;
      }
      if (line.instruction_type == ASM_DIRECTIVE)
      {
        lg_data = line.directive.int_operands;
        compteur2 = compteur2 + lg_data;
        //traiter directive
      }
    }
  }
  //maj entete
  //ecrire tgre
  //ecrire autres infos
}
 

static model_symbol_table symtable;
