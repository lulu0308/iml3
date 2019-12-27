
static int compteur;
function passe1(t_asm_line line, t_asm_directive directive)
{
  while (line != '/0')
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
          compteur ++;
        }
      }
      if (line.instruction_type == ASM_DIRECTIVE)
      {
        lg_data = ??;
        compteur = compteur + lg_data;
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
        compteur == 0;
        /* entrer le nom section dans TS*/
      }
      if (line.instruction_type == ASM_INSTRUCTION)
      {
        if (valide)
        {
        lg_instr = ??;
        compteur = compteur + lg_instr;
        }else{
          printf("erreur instruction invalide");
        }
      }
    }
  }
}

          
          
function passe2(){}

static model_symbol_table symbol_table;
