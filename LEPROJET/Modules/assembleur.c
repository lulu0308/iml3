
#include <stdio.h>
#include <string.h>
#include <math.h>
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

model_symbol_table symbol_table;

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
/*
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
		fprintf(file, "$%d, ", line->inst.instruction.operand1.reg_number);
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
*/
/*
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
*/
int size_of_data(t_directive x, int compteur)
{

	if (Y_WORD_DIR == x.directive_id)
	{
		return 4;
	}

	if (Y_ASCIIZ_DIR == x.directive_id)
	{
		int p = strlen(x.string_operand);
		printf("La length de la chaine est   %d  string: %s  ", p, x.string_operand);
		return p;
	}

	if (Y_ALIGN_DIR == x.directive_id)
	{
		int val = pow(2, x.operands.int_operands->value);
		if (compteur % val == 0)
			return 0;
		else
			return val - (compteur % val);
	}

	if (Y_SPACE_DIR == x.directive_id)
	{
		return 4 * x.operands.int_operands->value;
	}

	return 0;
}
/*
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
*/
int get_size_of_pseudo(int x)
{
	/*
	if ((x == 439) || (x == 429))
	{
		return 4;
	}
*/
	if ((x == 421) || (x == 425) || (x == 427) || (x == 442) || (x == 423) || (x == 430) || (x == 432))
	{
		return 8;
	}
	else
	{
		return 4;
	}
}

/*
static int compteur1;
void  passe1(t_asm_line line, t_asm_directive directive)
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
      
      if (line.instruction_type == ASM_DIRECTIVE)
      {
        if(line.inst.directive.directive_id ==){
			lg_data = line.directive.int_operands;
        compteur1 = compteur1 + lg_data;}
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
*/
void print_symboltable()
{
	for (int i = 0; i < symbol_table.effective_size; i++)
	{
		printf("%s |", symbol_table.table[i].nom_label);
		printf("%d |", symbol_table.table[i].valeur);

		if (symbol_table.table[i].status == 0)
		{
			printf("CODE");
		}
		if (symbol_table.table[i].status == 1)
		{
			printf("DATA");
		}
		if (symbol_table.table[i].status == 2)
		{
			printf("UNDEFINED");
		}
		printf("|");
		if (symbol_table.table[i].scope == 0)
		{
			printf("LOCAL");
		}
		if (symbol_table.table[i].scope == 1)
		{
			printf("GLOBAL");
		}
		if (symbol_table.table[i].scope == 2)
		{
			printf("EXTERNE");
		}
		printf("\n");
	}
}

int recherche(char *string)
{
	for (int i = 0; i != symbol_table.effective_size; i++)
	{
		if (strcmp(string, symbol_table.table[i].nom_label) == 0  )
		{

			 return i;
			  
		}
	}
	return -1;
}

int recherche_and_have_value(char *string)
{
	for (int i = 0; i != symbol_table.effective_size; i++)
	{
		if (strcmp(string, symbol_table.table[i].nom_label) == 0  )
		{
			printf("LA CHAINE RECHERCHER EST %s \n", string);
			 if(symbol_table.table[i].valeur == -1)
			 {
				 	printf("VZLUR DE %s EST -1 \n", string);
				 return -1;}
			  else{
			 return i;
			  }
		}
	}
	return -1;
}

void  insert_symbol(char *string, int compteur, int scope, int status)
{
	int index = recherche(string);
	if (index == -1)
	{
		printf("On insere %s\n", string);
		strcpy(symbol_table.table[symbol_table.effective_size].nom_label, string);
		symbol_table.table[symbol_table.effective_size].valeur = compteur;
		symbol_table.table[symbol_table.effective_size].status = status;
		symbol_table.table[symbol_table.effective_size].scope = scope;
		printf("Jarrive a la fi\n");
		symbol_table.effective_size++;
	}
	else
	{
		printf("On modifie %s à lindex %d  VALEUR %d ->  %d \n", string, index, symbol_table.table[index].valeur, compteur);
		symbol_table.table[index].valeur = compteur;
		symbol_table.table[index].status = status;
		symbol_table.table[index].scope = scope;
	}
}

int compteur = 0;
int code = 0;
int donner = 0;
void premier_passe(t_asm_line *line)
{

	if (strlen(line->label) > 0)
	{
		int x = recherche_and_have_value(line->label);
		if (x >= 0 && symbol_table.table[x].valeur > -1)
		{
			printf("Error Double Def %s \n", line->label);
			exit(0);
		}
		else
		{
			if (code == 1)
				insert_symbol(line->label, compteur, LOCAL, CODE);
			if (donner == 1)
				insert_symbol(line->label, compteur, LOCAL, DATA);
		}
	}

	if (line->instruction_type == ASM_DIRECTIVE)
	{
		compteur = compteur + size_of_data(line->inst.directive, compteur);
		if (line->inst.directive.directive_id == Y_WORD_DIR)
		{

			if(line->inst.directive.operands.int_operands == NULL){
					if (  recherche_and_have_value(line->inst.directive.string_operand) == -1)
					{
						if (code == 1)
							insert_symbol(line->inst.directive.string_operand, compteur, LOCAL, CODE);
						if (donner == 1)
							insert_symbol(line->inst.directive.string_operand, compteur, LOCAL, DATA);	
					}
			}
		}
		if (line->inst.directive.directive_id == Y_GLOBAL_DIR)
		{
			if (  recherche_and_have_value(line->inst.directive.string_operand) == -1)
			{
				if (code == 1)
					insert_symbol(line->inst.directive.string_operand, compteur, GLOBAL, CODE);
				if (donner == 1)
					insert_symbol(line->inst.directive.string_operand, compteur, GLOBAL, DATA);
			}
		}
	if (line->inst.directive.directive_id == Y_ASCIIZ_DIR)
		{ 
			
			if(  recherche_and_have_value(line->label)==-1){
				printf("JE ressors\n");
			 	if (code == 1)
			 		insert_symbol(line->label, compteur, GLOBAL, CODE);
			 	if (donner == 1)
			 		insert_symbol(line->label, compteur, GLOBAL, DATA);
			}
		}

		if (line->inst.directive.directive_id == Y_TEXT_DIR)
		{
			code = 1;
			donner = 0;
			compteur = 0;
		}
		if (line->inst.directive.directive_id == Y_DATA_DIR)
		{
			code = 0;
			donner = 1;
			compteur = 0;
		}
	}

	if (strlen(line->label) && line->instruction_type == NONE)
	{
		if (  recherche_and_have_value(line->label) == -1)
		{
			insert_symbol(line->label, -1, EXTERN, UNDEFINED);
		}
	}

	
	if (line->instruction_type == ASM_INSTRUCTION)
	{
		if (strlen(line->inst.instruction.operand1.label))
		{
			if (  recherche_and_have_value(line->inst.instruction.operand1.label) == -1)
			{
				insert_symbol(line->inst.instruction.operand1.label, -1, EXTERN, UNDEFINED);
			}
		}
		if (strlen(line->inst.instruction.operand2.label))
		{
			if (  recherche_and_have_value(line->inst.instruction.operand2.label) == -1)
			{
				insert_symbol(line->inst.instruction.operand2.label, -1, EXTERN, UNDEFINED);
			}
		}
		if (strlen(line->inst.instruction.operand3.label))
		{
			if (  recherche_and_have_value(line->inst.instruction.operand3.label) == -1)
			{
				insert_symbol(line->inst.instruction.operand3.label, -1, EXTERN, UNDEFINED);
			}
		}

		compteur = compteur + get_size_of_pseudo(line->inst.instruction.operation_id);
	}
	
}

int main(int argc, char **argv)
{
	symbol_table.effective_size = 0;

	//FILE *fp;
	//int i;
	/* open the file for writing*/
	//char output_file[MAX_STRING_SIZE];
	//strcat(output_file,"./Modules/");
	//strcat(output_file, argv[2]);
	//strcat(output_file, "_no_pseudo");
	//printf("Le out File est  %s", output_file);
	//fp = fopen(output_file, "w+");
	//fprintf(fp,"HEmlo ");
	/* close the file*/

	//test();
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
			print_parsed_line(ligne);
			printf("\n");
			premier_passe(ligne);

		}
		print_symboltable();

		terminate_parser();
		//fclose(fp);

		return (0);
	}

	//fclose(fp);
}