#include <analyseur.h>


typedef struct p_instruction{

    t_instruction line ;
    struct p_instruction * next;

} node_t_instruction;

/*Regarder l'init dans insctruction.c */
int is_pseudo(int x);
int get_size_of_pseudo(t_instruction);
node_t_instruction * get_inst_sequence_trad(t_instruction);
 
