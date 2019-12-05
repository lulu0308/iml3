
#include "analyseur.h"

#define MAX_SYMBOL_COUNT 100


typedef struct  {

    char  nom_label[MAX_LABEL_SIZE];
    int valeur;
    enum status { CODE , DATA , UNDEFINED};
    enum scope { LOCAL , GLOBAL , EXTERN}

} symbol;

typedef struct {
    int effective_size;
    symbol table[MAX_SYMBOL_COUNT];
} model_symbol_table;

model_symbol_table symbol_table;


int insert_symbol(t_instruction instruction);