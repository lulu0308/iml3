
static int compteur1;
function passe1(t_asm_line line, t_asm_directive directive)
{
  while (!fin-de-fichier())
  {
    parse_line();
    if (line != '#')
    {
      if (&line == line.label)
      {
        if (recherche(line.label))
        {
          printf("erreur double définition");
        }else{
          insert_symbol (line.label, inst_info1 table1 []);
          compteur1 ++;
        }
      }
      if (line.instruction_type == ASM_DIRECTIVE)
      {
        lg_data = line.directive.int_operands;
        compteur1 = compteur1 + lg_data;
      }
      if (!recherche(line.label))
      {
        insert.symbol(line.label, inst_info1 table1 []);
      }
      if (line.label = .globl)
          if (!recherche(line.label))
          {
            insert_symbol (line.label, inst_info1 table1 []);
          }else{
            modif_table();
          }
      }
      if (line.instruction_type == NONE)
      {
        compteur1 == 0;
        /* entrer le nom section dans TS*/
      }
      if (line.instruction_type == ASM_INSTRUCTION)
      {
        if (valide)
        {
        lg_instr = ??;
        compteur1 = compteur1 + lg_instr;
        }else{
          printf("erreur instruction invalide");
        }
      }
    }
  }
}


static int compteur2;  
function passe2(){
  while (!fin-de-fichier())
  {
    parse_line();
    if (line != '#')
    {
      if (line.instruction_type == NONE)
      {
        compteur1 == 0;
        /* mettre à jour l'entête*/
      }
      if (line.instruction_type == ASM_INSTRUCTION)
      {
        lg_instr = ??;
        //assembler instr
        //ecrire code instr
        compteur2 = compteur2 + lg_instr;
      }
      if (line.instruction_type == ASM_DIRECTIVE)
      {
        lg_data = ??;
        compteur2 = compteur2 + lg_data;
        //traiter directive
      }
    }
  }
  //maj entete
  //ecrire tgre
  //ecrire autres infos
}
    
  
  
}

static model_symbol_table symbol_table;
