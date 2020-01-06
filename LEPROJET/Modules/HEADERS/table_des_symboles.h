
#include "../../LIBHEADERS/analyseur.h"

#define MAX_SYMBOL_COUNT 100


typedef struct  {
    char  nom_label[MAX_LABEL_SIZE];
    int valeur;
    enum  {CODE , DATA , UNDEFINED}status;
    enum  {LOCAL , GLOBAL , EXTERN}scope;
} symbol;

typedef struct {
    int effective_size;
    symbol table[MAX_SYMBOL_COUNT];
} model_symbol_table;

//model_symbol_table symbol_table; (à déclarer dans assembleur)

int insert_symbol(t_instruction instruction);
//function rechercher
//function insert_with_value
//function insert_no_value
 
void test();
int is_pseudo(t_asm_line line);
void trad_pseudo( t_asm_line line , FILE * file);