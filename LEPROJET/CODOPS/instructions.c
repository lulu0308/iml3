/*
---------------------------------------------------------------------------
File : instructions.c
Auteur : Leon Mugwaneza

Contenu : Exemple d'initialisation d'une table de code operations
------------------------------------------------------------------------------
*/

#include <stdio.h>

#include "mnemoniques.h"  /* Code interne des instructions cf Analyseur */

/* Enregistrement contenant une chaine (un pointeur sur un char) et 3 int.
 Utilisé dans des tables des codes operations */

typedef struct s3i
{
  char *name;
  int value1;
  int value2;
  int value3;
} inst_info1;

/* Enregistrement contenant une chaine (un pointeur sur un char) et 2 int.
 Utilisé dans des tables des codes operations */

typedef struct s2i
{
  char *name;
  int value1;
  int value2;
} inst_info2;


/* Exemple table contenant le nom, le no interne, le type, et le code */

static inst_info1 table1 [] = {
#undef OP
#define OP(NAME, INTERNALCODE, TYPE, OPCODE) {NAME, INTERNALCODE, TYPE, (int)OPCODE},
#include "ops.h"
};

/* Exemple table contenant le nom, le no interne, et le code */

static inst_info2 table2 [] = {
#undef OP
#define OP(NAME, INTERNALCODE, TYPE, OPCODE) {NAME, INTERNALCODE, (int) OPCODE},
#include "ops.h"
};


int main(void)
{

int i;

	/* Afficher le contenu de la premiere table */
        printf("Table 1: nom, no interne, type interne et opcode\n");
	for(i=0; i<=(sizeof(table1)/sizeof(inst_info1)); i++)
	{
	   printf("{%s , %d, %d, 0x%8.8X} \n", table1[i].name, 
				     table1[i].value1, 
				     table1[i].value2,
				     table1[i].value3);
	}
	
        /* Afficher le contenu de la deuxième table */
        printf("Table 2: nom, no interne et opcode\n");
	for(i=0; i<=(sizeof(table2)/sizeof(inst_info2)); i++)
	{
	   printf("{%s , %d, 0x%8.8X} \n", table2[i].name, 
				     table2[i].value1, 
				     table2[i].value2);
	}
	return(0);
}
