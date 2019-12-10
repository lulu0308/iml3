#include "analyseur.h"


//procédure 1ere passe
void traiter_entete (int id_module, int taille);
void traiter_ref_externe(string/int id_symbole);
void traiter_ref_externe_non_satisfaites();

//procédure 2nde passe
void traiter_enregistrement(string adr, int n, int r, int code, int base);
void translater_enreg (string adr, int n, int r, int code, int base);
void traiter_point_entree (int id);
