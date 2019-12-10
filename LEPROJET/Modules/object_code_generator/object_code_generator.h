#include "analyseur.h"

typedef enum  {RELOCATE_DATA , RELOCATE_CODE , NO_RELOCATE} relocate;
typedef enum  {TYPE_J , TYPE_R ,TYPE_I} inst_type;



typedef struct 
{
    char  label[MAX_LABEL_SIZE];
    int position;
    relocate relocate;
    int index_in_sym_tab;
} relocation_data;

typedef struct
{
    //Label
    //Deplacement par rapport a Zero (main)
    //Definition ( relogable, non relogable, par code ou donnee)
    //numero de label

    char  label[MAX_LABEL_SIZE] ;
    int step;
    relocate relocate;
    inst_type inst_type;
    int index_in_sym_tab;

} relocation_code;

relocation_code * is_relocatable (t_instruction inst);

void write_reloc_info(relocation_code code);