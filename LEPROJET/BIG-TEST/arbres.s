#/*
#-------------------------------------------------------------------
#Nom du fichier : arbres.s
#Auteur :
#Objet : Module implantant les arbres binaires de recherche
#        contenant des entiers. Les noeuds sont doublement chainees.
#--------------------------------------------------------------------
#*/
##include <stdlib.h> //pour la constante NULL
#
##include "arbres.h" //pour verification de la coherence et définition
#                    // des types Arbre et Noeud
# arbres.h définit les types Noeud et Arbre.
# un élément de type Noeud sera represente'
# dans une zone 16 octets (4 pour le champ pere,
# 4 pour le champ info, 4 pour le champ fils_droit,
# et 4 pour le champ fils_gauche).
# Le champ pere est a un deplacement 0 par rapport
# au debut de cette zone, le champ info a un deplacement de 4,
# le champ fils_droit a un deplacement de 8,
# et le champ fils_gauche a un deplacement de 12.
# Un Arbre est un pointeur sur un Noeud. Un élément de type Arbre
# occupe 4 octets en mémoire ou dans un registre.

##include "memoire.h"
# memoire.h ne contient que des prototypes de fonctions.
##include "interface.h"
# interface.h ne contient que des prototypes de fonctions.
#
#/*
# Code des fonctions definies dans le module (entetes)
# - creer_arbre_vide, inserer, afficher_arbre_decroissant,rechercher,
# afficher_max, supprime_max, ...
# */
#
#Arbre creer_arbre_vide(void)
#/* creer_arbre_vide : retourne l'arbre vide
       .text
        .globl creer_arbre_vide
creer_arbre_vide:
#*/
#{
#  return(NULL);
        move $v0, $0
        # retour a l'appelant
        jr $ra
#}
#
#
#Arbre inserer(Arbre a, int x)
#/* inserer :
#insere l'entier x dans l'arbre binaire de recherche a et retourne
#l'arbre resultat
#*/
# parametres : a dans $a0, x dans $a1
# resultat dans $v0
        .globl inserer
inserer:
#{
#      Noeud * p; # dans $s0
#      Noeud * q; # dans $s1
#      Noeud * r; # dans $s2

    #Sauver $s0 $s1 $s2 et $ra
    sw $s0, -4($sp)
    sw $s1, -8($sp)
    sw $s2, -12($sp)
    sw $ra, -16($sp)
    addi $sp, $sp, -16
    #      Noeud * p; dans $s0
    #      Noeud * q; dans $s1
    #      Noeud * r; dans $s2
    #      Il faut sauver $s0, $s1, $s2
    #      On doit aussi sauver $v0
    #      p = (Noeud *)my_malloc(); appel de fonction avec jal
    # le résultat est dans $v0
          jal my_malloc
          move $s0, $v0
    #     if (p==NULL)
          bne $s0, $0, finif2
    #     {
    #         afficher_chaine("insertion impossible : memoire pleine\n");
    # $a0 a déjà quelque chose dedans donc on le sauvegarde
              sw $a0, -4($sp)
              addi $sp, $sp, -4
              la $a0, chaineInser1
              jal afficher_chaine
    # restaurer $a0
              addi $sp, $sp, 4
              lw $a0, -4($sp)
    #          return(a);
              move $v0, $a0
              j fininserer
    #     }
    finif2:
    #     p->info = x ;
          sw $a1, 4($s0)
    #     p->fils_gauche = NULL ;
          sw $0, 12($s0)
    #     p->fils_droit = NULL ;
          sw $0, 8($s0)
    #     if (a == NULL)
          bne $a0, $0, finif3
    #     {
    #          p->pere = NULL ;
              sw $0, 0($s0)
    #          return(p);
              move $v0, $s0
              j fininserer
    #     }
    finif3:
    #     q=a;
          move $s1, $a0
    #     do
    #     {
    do:
    #          r=q;
              move $s2, $s1
    #          if (x < q->info)
    #          {
              lw $t0, 4($s1)
              bge $a1, $t0, else1
    #              q=q->fils_gauche ;
                  lw $s1, 12($s1)
    #          }
    #         aller à finif4
              j finif4
    #          else
    else1:
    #          {
    #              q=q->fils_droit ;
                  lw $s1, 8($s1)
    #          }
    finif4:
    #     }while(q!=NULL);
          bne $s1, $0, do
    #     p->pere = r ;
          sw $s2, 0($s0)
    #     if (x < r->info)
    #     {
          lw $t0, 4($s2)
          bge $a1, $t0, else2
    #         r->fils_gauche=p ;
              sw $s0, 12($s2)
              j finif5
    #     }
    else2:
    #     else
    #     {
    #         r->fils_droit=p ;
              sw $s0, 8($s2)
    #     }
    finif5:
    #     return(a);
          move $v0, $a0
fininserer: #restauration
    #Sauver $s0 $s1 $s2 et $ra
    addi $sp, $sp, 16
    lw $s0, -4($sp)
    lw $s1, -8($sp)
    lw $s2, -12($sp)
    lw $ra, -16($sp)

    jr $ra

#}


#void afficher_arbre_decroissant(Arbre a)
#/* afficher_arbre_decroissant : affiche les elements de l'arbre a
#   dans l'ordre decroissant
#*/
# parametre a dans $a0
        .globl afficher_arbre_decroissant
afficher_arbre_decroissant:
#{
  # Sauvegarde $ra
  sw $ra, -4($sp)
  addi $sp, $sp, -4

#     if (a!= NULL)
      beq $a0, $0, finif6

#     {
  #        afficher_arbre_decroissant(a->fils_droit);
        # Sauver $a0 sur la pile
        sw $a0, -4($sp)
        addi $sp, $sp, -4
        lw $a0, 8($a0) # Passer le paramètre

        jal afficher_arbre_decroissant

        # afficher_chaine(" ");
        la $a0, space
        jal afficher_chaine

        #   afficher_entier(a->info);
        # on garde $a0 sauver sur la pile à 0($sp)
        lw $a0, 0($sp)  # a
        lw $a0, 4($a0)
        jal afficher_entier

        #   afficher_arbre_decroissant(a->fils_gauche);
        #a toujours sur la pile
          lw $a0, 0($sp)
          lw $a0, 12($a0)
          jal afficher_arbre_decroissant

        #Restaurer $a0
        addi $sp, $sp, 4
        lw $a0, -4($sp)

#     }
finif6:

#}
    # Restaurer $ra
    addi $sp, $sp, 4
    lw $ra, -4($sp)

    # Retour à l'appelant
    jr $ra


#int rechercher(Arbre a, int x)
#/* rechercher : retourne 1 si x est dans l'arbre a, 0 sinon
#*/
# parametres : a dans $a0, x dans $a1
# resultat dans $v0
        .globl rechercher
rechercher:
#Sauvegarde
sw $ra, -4($sp)
addi $sp, $sp, -4
#{
#     if (a == NULL) return(0) ;
      bne $a0, $0, fin_if1_rech
        li $v0,0
        j fin_recherche
      fin_if1_rech:
        lw $t0, 4($a0)
#     if (a->info == x) return(1) ;
          bne $t0, $a1, fin_if2_rech
          li $v0,1
          j fin_recherche
      fin_if2_rech:
#     if (a->info > x)
#     {
          ble $t0, $a1, else1_rech
#         return(rechercher(a->fils_gauche, x));

          #sauvegarde du parametre $a0
          sw $a0, -4($sp)
          addi $sp, $sp,-4

          lw $a0, 12($a0)
          jal rechercher

          #restauration du parametre $a0
          addi $sp, $sp,4
          lw $a0, -4($sp)
          j fin_recherche
#     }
#     else
      else1_rech:
#     {
#         return(rechercher(a->fils_droit, x));
#         sauvegarde du parametre $a0
          sw $a0,-4($sp)
          addi $sp, $sp, -4

          lw $a0, 8($a0)
          jal rechercher

#         restauration du parametre $a0
          addi $sp,$sp,4
          lw $a0, -4($sp)
#     }
fin_recherche:
    #restauration
    addi $sp, $sp, 4
    lw $ra, -4($sp)
#retour a l'appelant
jr $ra
#}

#
#int max(Arbre a)
#/* afficher_max :
#  Renvoie la valeur maximale dans l'arbre a
#*/
# parametre a dans $a0
# resultat dans $v0
        .globl max
max:
#sauvegarde
sw $ra, -4($sp)
sw $s0, -8($sp)
addi $sp, $sp, -8
#{
#      Noeud *p = a;
      move $s0 $a0
#
#      if (a==NULL)
      bne $a0, $0, else1_max
#      {
#          afficher_chaine("\nArbre vide!\n");
          la $a0, arbre_vide
          jal afficher_chaine
#          return -1;
          li $v0, -1
          j fin_if1_max
#      }
#      else
      else1_max:
#      {
#          while(p->fils_droit != NULL)
        while1_max:
            lw $t0, 8($s0)
            beq $t0, $0, finwhile1_max
#          {
#               p=p->fils_droit ;
                lw $s0, 8($s0)
                j while1_max
#          }
        finwhile1_max:
#          return (p->info);
            lw $s1, 4($s0)
            move $v0, $s1
#      }
    fin_if1_max:
#}
#restauration
addi $sp, $sp, 8
lw $ra, -4($sp)
lw $s0, -8($sp)
#retour a l'appelant
jr $ra

#void afficher_max(Arbre a)
#/* afficher_max :
#  Affiche la valeur maximale dans l'arbre a
#*/
# parametre a dans $a0
        .globl afficher_max
afficher_max:
#sauvegarde
sw $ra, -4($sp)
sw $s0, -8($sp)
addi $sp, $sp, -8
#{
#      Noeud *p = a;
      move $s0 $a0
#
#      if (a==NULL)
      bne $a0, $0, else1_affmax
#      {
#          afficher_chaine("\nArbre vide!\n");
          la $a0, arbre_vide
          jal afficher_chaine
#          return -1;
          li $v0, -1
          j fin_if1_affmax
#      }
#      else
      else1_affmax:
#      {
#          while(p->fils_droit != NULL)
        while1_affmax:
            lw $t0, 8($s0)
            beq $t0, $0, finwhile1_affmax
#          {
#               p=p->fils_droit ;
                lw $s0, 8($s0)
                j while1_affmax
#          }
        finwhile1_affmax:
#          afficher_chaine("\n");
            la $a0, retour_ligne
            jal afficher_chaine
#          afficher_entier(p->info);
            lw $a0, 4($s0)
            jal afficher_entier
#          afficher_chaine("\n");
            la $a0, retour_ligne
            jal afficher_chaine
#      }
    fin_if1_affmax:
#}
#restauration
addi $sp, $sp, 8
lw $ra, -4($sp)
lw $s0, -8($sp)
#retour a l'appelant
jr $ra


#
#Arbre supprimer_max(Arbre a)
#/* supprimer_max :
#  Supprime de l'arbre a un element ayant une valeur maximale et retourne
#  l'arbre resultat
#*/
# parametre a dans $a0
# resultat dans $v0
        .globl supprimer_max
supprimer_max:
#{
#sauvegarde
  sw $ra, -4($sp)
  sw $s0, -8($sp)
  addi $sp, $sp, -8
#      Noeud *p = a;
#on met p dans $s0
  move $s0,$a0
#
#      if (a==NULL)
       bne $a0,$0,fin_if1_suppr
#      {
#          afficher_chaine("\nArbre vide!\n");
          la $a0,arbre_vide
          jal afficher_chaine
          move $v0,$0
          j fin_suppr
#          return(NULL);
#      }
fin_if1_suppr:
while1_suppr:
#      while(p->fils_droit != NULL)
      lw $t0, 8($s0)
      beq $t0,$0,fin_while1_suppr
#      {
#           p=p->fils_droit ;
        lw $s0, 8($s0)
        j while1_suppr
#      }
fin_while1_suppr:
#      if (p->fils_gauche != NULL)
       lw $t0,12($s0)
       beq $t0,$0, else1_suppr
#      {
#          p->fils_gauche->pere=p->pere ;
          lw $t0,12($s0)
          lw $t1, 0($s0)
          sw $t1, 0($t0)
#         if (p != a)
          beq $s0,$a0,else2_suppr
#         {
#              p->pere->fils_droit = p->fils_gauche ;
              lw $t0, 0($s0)
              lw $t1, 12($s0)
              sw $t1, 8($t0)
              j fin_if2_suppr
#         }
  else2_suppr:
#         else
#         {
#              a = a->fils_gauche ;
            lw $a0,12($a0)
#         }
fin_if2_suppr:
        j fin_if4_suppr
#      }
else1_suppr:
#      else // p n'a pas de fils gauche
#      {
#             if (p == a) a = NULL ;
        bne $s0,$a0,else3_suppr
          move $a0,$0
          j fin_if3_suppr
#             else p->pere->fils_droit = NULL ;
else3_suppr:
    lw $t0, 0($s0)
    sw $0, 8($t0)
#      }
fin_if3_suppr:
fin_if4_suppr:
#      my_free(p);

#sauvegarde $a0
  sw $a0, -4($sp)
  addi $sp, $sp, -4

  move $a0,$s0
  jal my_free

# restaurer $a0
  addi $sp, $sp, 4
  lw $a0, -4($sp)

#      return(a);
  move $v0,$a0
#}
#restauration
fin_suppr:
  addi $sp, $sp, 8
  lw $ra, -4($sp)
  lw $s0, -8($sp)
  jr $ra


#  /* afficher_info :
#    Affiche la valeur stockée au noeud racine
#  */
# parametre a dans $a0
# resultat dans $v0
      .globl supprimer_racine
supprimer_racine:
#  Arbre supprimer_racine(Arbre a)
#  {
#sauvegarde
  sw $ra, -4($sp)
  sw $s0, -8($sp)
  addi $sp, $sp, -8
#    Noeud *p;
#On met p dans $t0
#
#    if (a == NULL)
     bne $a0, $0, fin_if1_racine
#    {
#      afficher_chaine("Arbre vide !");
        la $a0,arbre_vide
        jal afficher_chaine
#      return (Arbre)NULL;
        move $v0, $0
        j fin_racine
#    }
fin_if1_racine:
#
#sauvegarde $a0
  sw $a0, -4($sp)
  addi $sp, $sp, -4
#  	afficher_entier(a->info);
  lw $a0,4($a0)
  jal afficher_entier
#
# restaurer $a0
  addi $sp, $sp, 4
  lw $a0, -4($sp)
#
#  	if (a->fils_gauche != NULL)
    lw $t0, 12($a0)
    beq $t0,$0,fin_if2_racine
#  	{
#sauvegarde $a0
        sw $a0, -4($sp)
        addi $sp, $sp, -4
#      a->info = max(a->fils_gauche);
        lw $a0,12($a0)
        jal max
#
# restaurer $a0
        addi $sp, $sp, 4
        lw $a0, -4($sp)
        sw $v0 4($a0)
#sauvegarde $a0
        sw $a0, -4($sp)
        addi $sp, $sp, -4
#      p = supprimer_max(a->fils_gauche);
        lw $a0,12($a0)
        jal supprimer_max
#
# restaurer $a0
        addi $sp, $sp, 4
        lw $a0, -4($sp)
        move $s0, $v0
#      a->fils_gauche = p;
        sw $s0, 12($a0)
#      return a;
        move $v0, $a0
        j fin_racine
#  	}
fin_if2_racine:
#    if (a->fils_droit != NULL)
     lw $t0, 8($a0)
     beq $t0, $0, fin_if3_racine
#    {
#      p = a->fils_droit;
        lw $s0, 8($a0)
#      p->pere = NULL;
        sw $0,0($s0)
#      my_free(a);
        jal my_free
#      return p;
        move $v0,$s0
        j fin_racine
#    }
fin_if3_racine:
#  return (Arbre)NULL;
  move $v0,$0
fin_racine:
#restauration
  addi $sp, $sp, 8
  lw $ra, -4($sp)
  lw $s0, -8($sp)
#retour a l'appelant
  jr $ra
#  }
#


.data
# constantes chaines de caracteres utilisees dans la fonction menu
chaineInser1: .asciiz "insertion impossible : memoire pleine\n"
arbre_vide: .asciiz "Arbre vide!\n"
retour_ligne: .asciiz "\n"
space: .asciiz " "


#/*--------------------fin arbres.s---------------------------*/
#
