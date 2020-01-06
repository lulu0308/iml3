/*
---------------------------------------------------------------------------
File : analyseur.h
Auteur : Leon Mugwaneza

Contenu : Fichier ent�te du module analyseur.c
------------------------------------------------------------------------------
*/

#ifndef __ANALYSEUR_H
#define __ANALYSEUR_H


/*
 Les constantes nommees pour designer les instructions et les directives.
le fichiers mnemoniques.h est genere par yacc sous le nom y.tab.h 
*/
#include "mnemoniques.h"


/* 
Taille maximale d'une etiquette, d'une chaine de caractere,  et d'une ligne
*/

#define MAX_LABEL_SIZE	50
#define MAX_STRING_SIZE	100
#define MAX_LINE_SIZE	100

/* 
Constante NONE  utilise pour indiquer qu'un champ n'est pas significatif
(type d'instruction, mode d'adressage, numero de registre, etc.) 
Remarque: Pour les champs de type chaine de caract�res on utilise la chaine
         vide, et pour les champs de type pointeur on utilise le pointeur NULL
*/
#define NONE		-1 	

/* 
Types d'instructions du Langage d'assemblage (directive ou instruction)
 */
#define ASM_DIRECTIVE 	1
#define ASM_INSTRUCTION 2

/* 
Modes d'adressages 
*/
#define DIRECT_REGISTER 1 /* Direct registre  */
#define IMMEDIATE 	2 /* Immediat         */
#define OTHER		3 /* Les modes autres que Direct registre ou immediat ie
			    label, label+-imm(register), imm(reg), label+-imm */

/* 
Types d'operations : utilis�s pour afficher La_ligne  
*/
#define ASM_DIR         0 /* directive ASM */
#define INTEGER_INST	1 /* operations sur les entiers  */
#define FLOAT_INST 	2 /* operations sur les flottants simple precision    */
#define DOUBLE_INST	3 /* operations sur les flottants double precision    */
#define OTHER_INST	4 /* autres instructions */
#define PSEUDO_OP       5 /* Pseudo-instructions */

/* 
Les 3 types int_record, float_record et double_record servent a representer
les operandes d'une directive assembleur par une liste chainee.
exemple : .word 200 ou .word 20, 40, 45

- int_record est le type des maillons d'une liste chainee d'entiers ou autres
  types compatibles (octets et demi-mots) 
- float_record est le type des maillons d'une liste chainee de float 
- double_record est le type des maillons d'une liste chainee de double 
*/
typedef struct irecord
	{
		int 		value ;
		struct irecord 	*next ;
	}int_record ;

typedef struct frecord
	{
		float 		value ;
		struct frecord 	*next ;
	}float_record ;

typedef struct drecord
	{
		double 		value ;
		struct drecord 	*next ;
	}double_record ;

/* 
Le type t_directive sert a representer une directive et ses operandes.
   tous les champs ne sont pas utilises en meme temps. Le champ directive_id
   permet de connaitre les champs utilises 
*/
typedef struct
	{
		int   directive_id ; /* directive if type is ASM_DIRECTIVE */
		union
		{
		  int_record	* int_operands ;
		  float_record  * float_operands ;
		  double_record * double_operands ;
		}operands ;
		char string_operand[MAX_STRING_SIZE] ;
		
	} t_directive ;

/* 
Le types  t_instruction et t_operand servent a representer une instruction 
et ses operandes.  
Tous les champs ne sont pas utilises en meme temps. Le champ operation_id
et ou le champ mode de l'une des 3 operandes permet de savoir si 
l'operation a 0, 1, 2 ou 3 operandes et a determiner le mode d'adressage.
*/
typedef	struct
	{
		int	mode ; /* addressing mode : 
				NONE ; DIRECT_REGISTER, IMMEDIATE or OTHER */
		int	reg_number ;
		union
		{
		  int	i_value ;
		  float	f_value ;
		  double d_value ;
		}value ;
		char	label[MAX_LABEL_SIZE] ;
	} t_operand ;

typedef struct
	{
		int   operation_id; /* operation if type is ASM_INSTRUCTION */
		t_operand	operand1 ;
		t_operand	operand2 ;
		t_operand	operand3 ;
		
	} t_instruction ;

/*
Le type t_asm_line sert a representer une ligne d'un programme en langage
d'assemblage SPIM.
Si la ligne ne contient pas de label ou commentaire, le champ correspondant
contient la chaine vide.
*/
typedef struct 
	{
		char	label[MAX_LABEL_SIZE] ;
		char	comment[MAX_LINE_SIZE] ;
		int	instruction_type ; /* NONE, ASM_INSTRUCTION or ASM_DIRECTIVE*/
		union
		{
		  t_directive	directive ;
		  t_instruction instruction ;
		} inst;
	} t_asm_line ;


/*
-------------------------------------------------------------------------
Fonctions Exportees
*/

/*
int_parser : transmet le nom file_name du fichier a analyser
au module d'analyse syntaxique genere par yacc   
*/
extern void init_parser(char *file_name) ;

/*
terminate_parser : ferme le fichier en cours d'analyse
*/
extern void terminate_parser(void) ;

/*
parse_line : lit, fait l'analyse syntaxique d'une ligne d'un programme en 
langage d'assemblage SPIM, et remplit une structure de type t_asm_line.
La fonction get_addr_parsed_line() retourne un pointeur sur cette structure.
*/
extern int parse_line(void) ;

/*
get_parsed_line_addr : retourne un pointeur sur une structure de type t_asm_line
                       contenant la ligne qui vient d'etre lue et analysee par
                       parse_line
*/
extern t_asm_line * get_parsed_line_addr(void) ;


/*
print_parsed_line : affiche sur stdout le contenu de la structure t_asm_line
                    pointee par pt_line
*/

extern void print_parsed_line(t_asm_line *pt_line) ;



#endif /* #ifndef __ANALYSEUR_H */

/*----------------------- end of file ----------------------------------*/
