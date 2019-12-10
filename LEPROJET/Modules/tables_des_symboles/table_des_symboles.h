
#include "analyseur.h"

#define MAX_SYMBOL_COUNT 100


typedef  enum status { CODE , DATA , UNDEFINED};
typedef  enum scope { LOCAL , GLOBAL , EXTERN};


typedef struct  {

    char  nom_label[MAX_LABEL_SIZE];
    int valeur;
    enum status status;
    enum scope scope;

} symbol;

typedef struct {
    int effective_size;
    symbol table[MAX_SYMBOL_COUNT];
} model_symbol_table;

model_symbol_table symbol_table;//mod assembleur


int insert_symbol(t_asm_line line);
int recherche(t_asm_line line);
