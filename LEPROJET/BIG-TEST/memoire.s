  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

  
  
  
  
  
  
  
  
  
        .data
        .align 2
memoire:
        .space 3200   
                      
                      
  
  
  
  
blocs_libres:
        .word 0

  
  
  
  
  
  
  
        .text
        .globl init_mem
init_mem:
  
  
  
  
    move $t0, $0

  
do:

  
  
    
  li $t2, 16
  mul $t2, $t2, $t0
  la $t2, memoire($t2)
    
  addi $t3, $t2, 16
    
  sw $t3, 0($t2)

  
      addi $t0, $t0, 1

  
  li $t1, 199
  blt $t0, $t1, do

  
  
  li $t2, 3184
  sw $0, memoire($t2)

  
  la $t1, memoire($0)
  sw $t1, blocs_libres($0)

  
  jr $ra

  
  
  
  
  
  
        .globl my_malloc
my_malloc:
  
  
    

  
  lw $t0, blocs_libres($0)

  
  beq $t0, $0, finif1
  
  
      lw $t1, blocs_libres($0)
      lw $t1, 0($t1)
      sw $t1, blocs_libres($0)

  
  finif1:

  
  move $v0, $t0
  jr $ra
  


  
  
  
  
  
  
        .globl  my_free
my_free:
  
  
  lw $t0, blocs_libres($0)
  sw $t0, 0($a0)
  
  sw $a0, blocs_libres($0)
  
jr $ra

  
  
