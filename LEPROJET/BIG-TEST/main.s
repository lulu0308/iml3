 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
     .text
menu :
 
 
        sw $ra, -4($sp)
        addiu $sp, $sp, -4
 
 
        la $a0, chmenu  
                        
        jal afficher_chaine
 
        la $a0, ch1
        jal afficher_chaine
 
        la $a0, ch2
        jal afficher_chaine
 
        la $a0, ch3
        jal afficher_chaine
 
        la $a0, ch4
        jal afficher_chaine
 
        la $a0, ch5
        jal afficher_chaine
 
        la $a0, ch6
        jal afficher_chaine
 
        la $a0, ch7
        jal afficher_chaine
 
        la $a0, ch0
        jal afficher_chaine
 
        la $a0, alaligne
        jal afficher_chaine
 
        la $a0, choix
        jal afficher_chaine
 
 
        addiu $sp, $sp, 4
        lw $ra, -4($sp)
        jr $ra

 
 
        .globl main
main:
 
 
 
 
 
 
 
 
 
 
 
 
 
 
         
         
        sw $ra, -4($sp)
        sw $s0, -8($sp)
        sw $s1, -12($sp)
        sw $s2, -16($sp)
        addiu $sp, $sp, -16
 
 
 
        jal init_mem
 
 
        jal creer_arbre_vide  
        move $s2, $v0
 
        jal menu
 
        jal lire_entier  
        move $s0, $v0
 
while: beq $s0, $0, fin_while
 
 
 
 
         
        ble $s0, $0, fin_switch
         
        li $t0, 7
        bgt $s0, $t0, fin_switch
         
        li $t0, 4
        mul $t0, $s0, $t0
        lw $t0, JT($t0)
        jr $t0 
 
 
case1:
 
         jal creer_arbre_vide
         move $s2, $v0
 
         j fin_switch
 
case2:
 
        la $a0, saisieinserer  
        jal afficher_chaine
 
        jal lire_entier
        move $s1, $v0

 
        move $a0, $s2
        move $a1, $s1
        jal inserer  
        move $s2, $v0

 
         j fin_switch
 
 
case3:
 
          beq $s2,$0, elsemain1
 
        move $a0, $s2
        jal afficher_arbre_decroissant
        j finifmain1
 
elsemain1:
 
         la $a0, arbrevide
         jal afficher_chaine
finifmain1:
 
         j fin_switch
 
case4:
 
         la $a0, saisierechercher
         jal afficher_chaine
 
         jal lire_entier
         move $s1, $v0
 
        move $a0, $s2
        move $a1, $s1,
        jal rechercher  
        beq $v0, $0, elsemain2
 
        la $a0, present
        jal afficher_chaine
        b finifmain2
 
elsemain2:
 
        la $a0, absent
        jal afficher_chaine
finifmain2:
 
         j fin_switch
 
 
case5:
 
        move $a0, $s2
        jal afficher_max
 
         j fin_switch
 
 
case6:
 
        move $a0, $s2
        jal supprimer_max
        move $s2, $v0
 
         j fin_switch
 
case7:
 
 
          move $a0, $s2
          jal supprimer_racine
          move $s2, $v0
 
        j fin_switch
 
fin_switch:
 
         jal menu
 
        jal lire_entier
        move $s0, $v0
 
        j while
fin_while:
 
 
        li $v0, 0
         
        addiu $sp, $sp, 16
        lw $ra, -4($sp)
        lw $s0, -8($sp)
        lw $s1, -12($sp)
        lw $s2, -16($sp)
        jr $ra
 


        .data
 
chmenu: .asciiz "\n------------------Menu-----------------\n"
ch1:    .asciiz " 1 : Creer un arbre vide \n"
ch2:    .asciiz " 2 : Inserer un nouvel element \n"
ch3:    .asciiz " 3 : Afficher l'arbre dans l'ordre decroissant \n"
ch4:    .asciiz " 4 : Rechercher un element\n"
ch5:    .asciiz " 5 : Afficher la valeur maximale \n"
ch6:    .asciiz " 6 : Supprimer un element ayant la valeur maximale \n"
ch7:    .asciiz " 7 : Afficher la valeur du noeud racine et supprimer le noeud racine \n"
ch7:    .asciiz " 7 : Afficher la valeur du noeud racine et supprimer le noeud racine \n"
ch7:    .asciiz " 7 : Afficher la valeur du noeud racine et supprimer le noeud racine \n"
ch7:    .asciiz " 7 : Afficher la valeur du noeud racine et supprimer le noeud racine \n"
ch7:    .asciiz " 7 : Afficher la valeur du noeud racine et supprimer le noeud racine \n"
ch0:    .asciiz " 0 : Quitter \n"
alaligne: .asciiz "\n"
choix : .asciiz "choix : \n"

 
saisieinserer: .asciiz  "nombre a inserer ? "
saisierechercher: .asciiz "nombre a rechercher ? "
present: .asciiz " present!\n"
absent: .asciiz " absent!\n"
arbrevide: .asciiz " arbre vide!"

 
       .align 2
JT :    .word 0
        .word case1
        .word case2
        .word case3
        .word case4
        .word case5
        .word case6
        .word case7

 
