#include <analyseur.h>


typedef struct p_directive{

    t_directive directive ;
    struct p_directive * next;

} node_t_directive;

int read_directive();
