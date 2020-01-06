/*
---------------------------------------------------------------------------
File : main.c
Auteur : Leon Mugwaneza

Contenu : Exemple d'utilisation de l'analyseur
------------------------------------------------------------------------------
*/

#include <stdio.h>

#include "analyseur.h"


int main(int argc, char **argv)
{
	t_asm_line *ligne ;

	if (argc < 2)
	{
	  printf("preciser le fichier a analyser\n");
	  return(1);
	}
	else
    	{
	  init_parser(argv[1]);
          ligne = get_parsed_line_addr();
	  while (!parse_line())
	  {
		print_parsed_line(ligne);
  	  }
	  terminate_parser();
	  return(0);
	}
}
