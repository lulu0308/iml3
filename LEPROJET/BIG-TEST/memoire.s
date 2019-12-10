#/*
#-------------------------------------------------------------------
#Nom du fichier : memoire.s
#Auteur :
#Objet : Module implantant les fonctions d'allocation et de liberation
#        de la memoire
#--------------------------------------------------------------------
#*/
##include <stdlib.h> // Pour la definition de NULL
##include "arbres.h" // Definition des types Noeud et Arbre
##include "memoire.h" //pour verification de la coherence
#
#
#/*
#Code des fonctions definies dans le module (entetes dans memoire.h):
# - init_mem, my_malloc et my_free
#
#Pour simplifier on alloue la memoire par blocs de taille fixe (la taille
#d'un noeud). Les blocs libres sont stockees dans une pile.
#*/
#
##define MAX 200 // nombre maximum de blocs
#
#static Noeud memoire[MAX] ; // On reserve MAX blocs

# Le type Noeud est defini dans arbres.h. Comme indiqué dans arbres.s,
# un élément de type Noeud sera represente'
# dans une zone 16 octets (4 pour le champ pere,
# 4 pour le champ info, 4 pour le champ fils_droit,
# et 4 pour le champ fils_gauche).
# Le champ pere est a un deplacement 0 par rapport
# au debut de cette zone, le champ info a un deplacement de 4,
# le champ fils_droit a un deplacement de 8,
# et le champ fils_gauche a un deplacement de 12.
        .data
        .align 2
memoire:
        .space 3200 # ON NE RESPECTE PAS LA SEMANTIQUE DU C QUI DIT
                    # QUE TOUTES LES VARIABLES GLOBALES SONT INITIALISEES
                    # A ZERO
#static Arbre blocs_libres ; // Sommet de la pile des blocs libres
#Le type Arbre est defini dans arbres.h. Un Arbre est un pointeur
#sur un Noeud. Un élément de type Arbre occupe 4 octets en mémoire
# ou dans un registre (cf arbres.s).
blocs_libres:
        .word 0

#
#/* init_mem : Initialise les structures de donnees utilisees pour gerer
#              l'allocation et la liberation de la memoire
#              On met tous les blocs libre sur une pile.
#*/
#
#void init_mem(void)
        .text
        .globl init_mem
init_mem:
#{
#   int i ; #est dans $t0
#
#   i=0 ;
    move $t0, $0

#   do
do:

#   {
#       memoire[i].pere = (Noeud *)(&memoire[i+1]);
  #   &memoire[i] dans $t2
  li $t2, 16
  mul $t2, $t2, $t0
  la $t2, memoire($t2)
  #   &memoire[i+1] dans $t3
  addi $t3, $t2, 16
  #   memoire[i].pere = &memoire[i+1]
  sw $t3, 0($t2)

#       i=i+1;
      addi $t0, $t0, 1

#   } while (i<MAX-1);
  li $t1, 199
  blt $t0, $t1, do

#   memoire[MAX-1].pere = NULL ;
#   &memoire[MAX-1].pere = &memoire +199*16 = &memoire + 3184
  li $t2, 3184
  sw $0, memoire($t2)

#   blocs_libres = memoire ;
  la $t1, memoire($0)
  sw $t1, blocs_libres($0)

#}
  jr $ra

#/* my_malloc : alloue un bloc de taille TAILLE_NOEUD (fixe: cf arbres.h) et
#               retourne l'adresse du bloc (retourne NULL si allocation
#               impossible)
#*/
#void *my_malloc(void)
# resultat dans $v0
        .globl my_malloc
my_malloc:
#{
#   Arbre p;
  #est dans $t0

#   p =  blocs_libres ;
  lw $t0, blocs_libres($0)

#   if (p!=NULL)
  beq $t0, $0, finif1
#   {
#       blocs_libres = blocs_libres->pere ;
      lw $t1, blocs_libres($0)
      lw $t1, 0($t1)
      sw $t1, blocs_libres($0)

#   }
  finif1:

#   return((void *)p);
  move $v0, $t0
  jr $ra
#}


#/* my_free : libere le bloc passe en parametre.
#     ajoute le bloc au sommet de la pile des blocs
#     libres
#*/
#void my_free(void *bloc)
# Parametre bloc dans $a0
        .globl  my_free
my_free:
#{
#   ((Arbre)bloc)->pere = blocs_libres ;
  lw $t0, blocs_libres($0)
  sw $t0, 0($a0)
#   blocs_libres = (Arbre)bloc ;
  sw $a0, blocs_libres($0)
#}
jr $ra

#/*----------------fin memoire.s--------------------------------------*/
#
