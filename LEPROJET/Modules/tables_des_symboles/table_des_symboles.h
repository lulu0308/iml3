
#include "analyseur.h"

#define MAX_SYMBOL_COUNT 100


typedef struct  {
    char  nom_label[MAX_LABEL_SIZE];
    int valeur;
    enum status {CODE , DATA , UNDEFINED};
    enum scope {LOCAL , GLOBAL , EXTERN};
} symbol;

typedef struct {
    int effective_size;
    symbol table[MAX_SYMBOL_COUNT][MAX_SYMBOL_COUNT];
} model_symbol_table;

char *get_opcode(int);
int is_pseudo(t_asm_line);
//void write_pseudo(t_asm_line *, FILE *);
//void print_t_operand(t_operand);
//void print_t_instruction(t_instruction);
//void print_t_directive(t_directive);
int size_of_data(t_directive, int);
//void print_t_asm_line(t_asm_line *);
int get_size_of_pseudo(int);
void print_symboltable();
int recherche(char *);
int recherche_and_have_value(char *);
void insert_symbol(char *, int, int, int);
void premier_passe(t_asm_line *);
