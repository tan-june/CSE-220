.text

null_cipher_sf:
    
    # keep track of how many chars are stored
    li $t9, 0              

    li $t0, 0              # loop counter
    move $t1, $a3          # max loop count   


    move $t2, $a1          # cipher text
    move $t5, $a0          # plaintext 
    move $t6, $a2          # indices array
  
    loop_index:
        # max check
        beq  $t0, $t1, done_all    
        
        # load value from indices array
        lw $t3, 0($t6)      
        
        # move 4 bytes or get next index (doesn't matter yet)
        addi $t6, $t6, 4

        #i++ (add to t0)    
        addi $t0, $t0, 1

        #if index is 0, find next word
        beqz $t3, find_next_space
        
        #increment words stored, and subtract one for index from indicies array
        addi $t9, $t9, 1      # increment byte count
        addi $t3, $t3, -1     # subtract 1 from index
        j find_char


    #loop until 0; then go into store char
    find_char:
        beqz $t3, store_char   
        addi $t2, $t2, 1    
        addi $t3, $t3, -1   
        j find_char

    #store char in plaintext buffer
    store_char:
        #load the byte into t4
        lbu $t4, 0($t2)
        #set the byte in t5
        sb $t4, 0($t5)  
        #increment for next time    
        addi $t5, $t5, 1
        #find next word
        j find_next_space

    find_next_space:

        #check for space; if space; then jump out
        lbu $t4, 0($t2)     
        li $t8, ' '         
        beq $t4, $t8, loop_index_add_spacer
        addi $t2, $t2, 1    

        #max loop counter; possibility of no more spaces otherwise infinite loop
        addi $t7, $t7, 1    
        li $t8, 100         
        bne $t7, $t8, find_next_space     

        j done_all

    loop_index_add_spacer:
        addi $t2, $t2, 1  #get to first letter of the word
        j loop_index

    done_all:
        #null terminate
        sb $zero, 0($t5)
        #put how many loops in v0
        move $v0, $t9
        jr $ra

transposition_cipher_sf:
    li $t0, 0 #col
    li $t1, 0 #row
    li $t2, 0 #index in text

    # columns loop
    col_loop:
        #row check; if not go to done_col
        blt $t0, $a3, row_loop
        j done_col_loop

    row_loop:

        #index calculation in text array
        mul $t3, $t1, $a3
        add $t3, $t3, $t0

        #load the byte
        lbu $t4, 0($a1)
        addi $a1, $a1, 1

        #store
        add $t5, $a0, $t3
        sb $t4, 0($t5)

        #update the indicies
        addi $t2, $t2, 1
        addi $t1, $t1, 1

        #row max check
        bge $t1, $a2, add_to_col
        j done_row_loop

    add_to_col:
        #add one to column, and set row indexing to 0 again
        addi $t0, $t0, 1
        li $t1, 0


    done_row_loop:
        #make sure that it is not the end of the array, otherwise go back into row loop
        mul $t9, $a2, $a3
        blt $t2, $t9, row_loop

    done_col_loop:
        #add null terminator
        add $t5, $a0, $t3
        addi $t5, $t5, 1
        sb $zero, 0($t5)
        move $t6, $a0

    #load each byte until **found; if not return; otherwise replace with $zero
    find_star:
        lb $t7, 0($t6)
        beq $t7, $zero, finish
        li $t9, 42
        beq $t7, $t9, star_found
        addi $t6, $t6, 1
        j find_star

    #asterisk byte becomes null terminator
    star_found:
        sb $zero, 0($t6)

    finish:
        jr $ra

decrypt_sf:

    #move all the arguments into temporary registers
    move $t0, $a0 #plaintext
    move $t1, $a1 #cipher text
    move $t2, $a2 # rows
    move $t3, $a3 #cols 
    lw $t4, 0($sp) #indices #
    lw $t5, 4($sp) #indices array

    #save stack original stack pointer
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    #save the 6 registers
    addi $sp, $sp, -28
    sw $s0, 0($sp)
    sw $s1, 4($sp)
    sw $s2, 8($sp)
    sw $s3, 12($sp)
    sw $s4, 16($sp)
    sw $s5, 20($sp)
    sw $s6, 24($sp)

    #move all temporarys into saved registers
    move $s0,$t0 #plaintext
    move $s1,$t1 #ciphertext
    move $s2,$t2 #rows
    move $s3,$t3 #cols
    move $s4,$t4 #indices#
    move $s5,$t5 #indices array
    
    #find how much memory needed for transposition_cipher output and add null terminator
    mul $s6, $t2, $t3   
    addi $s6, $s6, 1    
    
    #allocated memory according to the s6 registers
    sub $sp, $sp, $s6
    
    #make a0 argument the starting pointer
    addi $t7, $sp, 0  
    move $a0, $t7      
    
    #get output of transposition_cipher_sf
    jal transposition_cipher_sf
    
    #swap and load new arguments
    addu $a1, $a0, $zero
    addu $a0, $s0, $zero
    addu $a3, $s4, $zero
    addu $a2, $s5, $zero
    
    jal null_cipher_sf

    #dealloc memory
    add $sp, $sp, $s6

    #load back all registers and return    
    lw $s6, 24($sp)
    lw $s5, 20($sp)
    lw $s4, 16($sp)
    lw $s3, 12($sp)
    lw $s2, 8($sp)
    lw $s1, 4($sp)
    lw $s0, 0($sp)
    addi $sp, $sp, 28

    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra