
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

char *get_opcode(int opcode_id);
int is_pseudo(t_asm_line k);
//void write_pseudo(t_asm_line *line, FILE *file);
//void print_t_operand(t_operand x);
//void print_t_instruction(t_instruction x);
//void print_t_directive(t_directive x);
int size_of_data(t_directive x, int compteur);
//void print_t_asm_line(t_asm_line *x);
int get_size_of_pseudo(int x);
void print_symboltable();
int recherche(char *string);
int recherche_and_have_value(char *string);
void insert_symbol(char *string, int compteur, int scope, int status);
void premier_passe(t_asm_line *line);
