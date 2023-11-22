.data

# Command-line arguments
num_args: .word 0
addr_arg0: .word 0
addr_arg1: .word 0
addr_arg2: .word 0
addr_arg3: .word 0
addr_arg4: .word 0
no_args: .asciiz "You must provide at least one command-line argument.\n"

# Output messages
straight_str: .asciiz "STRAIGHT_HAND"
four_str: .asciiz "FOUR_OF_A_KIND_HAND"
pair_str: .asciiz "TWO_PAIR_HAND"
unknown_hand_str: .asciiz "UNKNOWN_HAND"

# Error messages
invalid_operation_error: .asciiz "INVALID_OPERATION"
invalid_args_error: .asciiz "INVALID_ARGS"

# Put your additional .data declarations here, if any.
debugging_string: .asciiz "to this point"
prefix: .asciiz "0x"
zero_print: .asciiz "0"

# Main program stciiz arts here
.text
.globl main
main:
    # Do not modify any of the code before the label named "start_coding_here"
    # Begin: save command-line arguments to main memory  
    sw $a0, num_args
    beqz $a0, zero_args
    li $t0, 1
    beq $a0, $t0, one_arg
    li $t0, 2
    beq $a0, $t0, two_args
    li $t0, 3
    beq $a0, $t0, three_args
    li $t0, 4
    beq $a0, $t0, four_args
five_args:
    lw $t0, 16($a1)
    sw $t0, addr_arg4
four_args:
    lw $t0, 12($a1)
    sw $t0, addr_arg3
three_args:
    lw $t0, 8($a1)
    sw $t0, addr_arg2
two_args:
    lw $t0, 4($a1)
    sw $t0, addr_arg1
one_arg:
    lw $t0, 0($a1)
    sw $t0, addr_arg0
    j start_coding_here

zero_args:
    la $a0, no_args
    li $v0, 4
    syscall
    j exit
    # End: save command-line arguments to main memory


	
start_coding_here:

#---------------------------------------------------------------Part 1----------------------------------------------------------------------------------------------------

    #check for minimum of two arguments
	lw $t1, num_args
	li $t2, 2
	blt $t1, $t2, invalid_arg

	# load first argument, move one over; should be null terminator otherwise throw invalid_ops error
	lw $t0, addr_arg0
	addi $t0, $t0, 1
	lbu $t1, 0($t0)
	bne $t1, $zero, invalid_ops

	#load first argument again
	lw $t0, addr_arg0
	lbu $t0, 0($t0)
	
    #if equal to E, D, P based jumps
	li $t1, 'E'
	beq $t0, $t1, check_e
	li $t1, 'D'
	beq $t0, $t1, check_d
	li $t1, 'P'
	beq $t0, $t1, check_p
	
    j invalid_ops
	syscall
	j exit

	invalid_arg:
	la $a0, invalid_args_error
	li $v0, 4
	syscall
	j exit

	invalid_ops:
	la $a0, invalid_operation_error
	li $v0, 4
	syscall
	j exit
	
    #jump to various operations
	check_e:
	lw $t1, num_args
	li $t2, 5
	beq $t1, $t2, e_operation
	j invalid_arg
	
	check_d:
	lw $t1, num_args
	li $t2, 2
	beq $t1, $t2, d_operation
	j invalid_arg
	
	check_p:
	lw $t1, num_args
	li $t2, 2
	beq $t1, $t2, p_operation
	j invalid_arg

#---------------------------------------------------------------Part 2----------------------------------------------------------------------------------------------------
	e_operation:
	
	#-----------------extract second argument (stored in addr_arg1) --------------------------------------------------------------------
	lw $t0, addr_arg1
	li $t1, 0
	li $t2, 10

	#loop to extract value
	extract_value_second_arg:
        lbu $t3, 0($t0)

        #null terminator check
        beqz $t3, check_for_second_arg
        li $t8, 48
        sub $t3, $t3, $t8
        mul $t1, $t1, $t2
        add $t1, $t1, $t3
        addi $t0, $t0, 1
        j extract_value_second_arg

	check_for_second_arg:
    #should be greater than zero
    slt $t2, $t1, $zero
    bne $t2, $zero, invalid_arg 
    	
    #should be less than or equal to 63 check
	li $t2, 63 
    slt $t2, $t2, $t1
    bne $t2, $zero, invalid_arg
	
    #set result register to 0
	li $t9, 0
	#bit shift 26 bits 
	sll $t9, $t1, 26


	#-----------------extract third argument (stored in addr_arg2) ---------------------------------------------------------------------------
	
	lw $t0, addr_arg2
	li $t1, 0
	li $t2, 10
	
	#loop to extract value
	extract_value_third_arg:
    	lbu $t3, 0($t0)
    	#null terminator check
    	beqz $t3, check_for_third_arg
    	li $t8, 48
    	sub $t3, $t3, $t8
    	mul $t1, $t1, $t2
    	add $t1, $t1, $t3
	addi $t0, $t0, 1
    	j extract_value_third_arg

	check_for_third_arg:
        #should be greater than zero
    	slt $t2, $t1, $zero
    	bne $t2, $zero, invalid_arg 
    	
    #should be less than or equal to 31 check
	li $t2, 31
    slt $t2, $t2, $t1
    bne $t2, $zero, invalid_arg
    	
    #shift bits into place
    sll $t1, $t1, 21
  	or $t9, $t9, $t1
	
	#-----------------extract fourth argument (stored in addr_arg3) ---------------------------------------------------------------------------

	lw $t0, addr_arg3
	li $t1, 0
	li $t2, 10


	extract_value_fourth_arg:
    	lbu $t3, 0($t0)
    	beqz $t3, check_for_fourth_arg

    	li $t8, 48
    	sub $t3, $t3, $t8
    	mul $t1, $t1, $t2
    	add $t1, $t1, $t3

	    addi $t0, $t0, 1
    	j extract_value_fourth_arg


	check_for_fourth_arg:

	#should be greater than zero
    	slt $t2, $t1, $zero
    	bne $t2, $zero, invalid_arg 

		#should be less than or equal to 31
		li $t2, 31
    	slt $t2, $t2, $t1 
    	bne $t2, $zero, invalid_arg  

	#shift bits into place
    sll $t1, $t1, 16
  	or $t9, $t9, $t1

  	#-----------------extract fifth argument (in addr_arg4)-----------------------------------------------

	lw $t0, addr_arg4
	li $t1, 0
	li $t2, 10

	extract_value_fifth_arg:
    	lbu $t3, 0($t0)
    	beqz $t3, check_for_fifth_arg
    	li $t8, 48
    	sub $t3, $t3, $t8
    	mul $t1, $t1, $t2
    	add $t1, $t1, $t3
    	addi $t0, $t0, 1
    	j extract_value_fifth_arg

	check_for_fifth_arg:

	#should be greater than zero
    slt $t2, $t1, $zero
    bne $t2, $zero, invalid_arg 
    	
    #should be less than or equal to 65535 check
	li $t2, 65535 
    slt $t2, $t2, $t1
    bne $t2, $zero, invalid_arg

	#shift bits into place
	sll $t1, $t1, 0
  	or $t9, $t9, $t1
  	
 #--------------------------print------------------------------------------------------------------------------------------
  	#print into hex-decimal (syscall 34)
  	li $v0, 34      
	move $a0, $t9
	syscall
	
	#finish the program
	j exit

#------------------------------------------------------------------------------Part 3-------------------------------------------------------------------------------------

d_operation:
      #----------------------------------check if equal to see if equal to 0x argument ----------------
      #0x load
      la $t0, prefix
      
      #load argument
      lw $t1, addr_arg1
      
      #max loop count
      li $t2, 2
    	
      Ox_check:
      lb $t3, 0($t0)
      lbu $t4, 0($t1)
      beqz $t3, length_check
      bne $t3, $t4, invalid_arg  
      
      #add one byte to registers
      addi $t0, $t0, 1   
      addi $t1, $t1, 1    
      
      #subtract one to loop count
      addi $t2, $t2, -1  
      
      #go back to 0x_check if loop is not equal to 0
      bgtz $t2, Ox_check
	
      #----------------------------------check if equal to 10 arguments (including the 0x)----------------
      
      # load argument data (again to be safe)
      lw $t1, addr_arg1
      # counter
      li $t2, 0

      length_check:

      #load bytes
      lbu $t3, 0($t1)
      beq $t3, $zero, at_null_terminator

      #increment
      addi $t1, $t1, 1
      addi $t2, $t2, 1
      bne $t2, $zero, length_check
      j invalid_arg

      #if t2 and t9 registers are not equal to 10; then invalid_arg
      at_null_terminator:
      li $t9, 10
      bne $t2, $t9, invalid_arg
      
      #----------------------------------loop to check if the arguments are between a-f and 0-9----------------
     
      #load argument
      lw $s0, addr_arg1
      
      #skip 0x
      addi $s0, $s0, 2
      
      #result register
      li $t9, 0
    
      extract_values:
      lbu $t1, 0($s0)
      beq $t1, $zero, skip_to_print
      
      #check if it is a-f
      li $t2, 48
      subu $t3, $t1, $t2
      slti $t4, $t3, 10
      beqz $t4, check_letter
      
      sll $t9, $t9, 4
      or $t9, $t9, $t3
      addi $s0, $s0, 1
      j extract_values
    
      check_letter:
      li $t2, 97
      subu $t3, $t1, $t2
      sltiu $t4, $t3, 6
      beqz $t4, invalid_arg
      addi $t3, $t3, 10
      sll $t9, $t9, 4
      or $t9, $t9, $t3
      addi $s0, $s0, 1
      j extract_values
    
      #-------------------------------------------printing values---------------------------------------------------------

    skip_to_print:

    ##-------print digit 1
        #op code field
        srl $t0, $t9, 26  
        slti $t4, $t0, 10
        beq $t4, $zero, print_value_1

        #print leading zero if necessary
        li $v0, 4
        la $a0, zero_print
        syscall

        print_value_1:
        move $a0, $t0
        li $v0, 1
        syscall

        #space
        li $a0, 32   
        li $v0, 11
        syscall

    ##-------print digit 2
        #rs field
        srl $t1, $t9, 21
        sll $t1, $t1, 27
        srl $t1, $t1, 27

        slti $t4, $t1, 10
        beq $t4, $zero, print_value_2

        #print leading zero if necessary
        li $v0, 4
        la $a0, zero_print
        syscall

        print_value_2:
        move $a0, $t1
        li $v0, 1
        syscall


        #space
        li $a0, 32   
        li $v0, 11
        syscall
    
    ##-------print digit 3
        #rt field
        srl $t2, $t9, 16
        sll $t2, $t2, 27  
        srl $t2, $t2, 27  

        slti $t4, $t2, 10
        beq $t4, $zero, print_value_3

        #print leading zero if necessary
        li $v0, 4
        la $a0, zero_print
        syscall

        print_value_3:
        move $a0, $t2
        li $v0, 1
        syscall
            
        #space
        li $a0, 32   
        li $v0, 11
        syscall
    
    ##-------print digit 4
        #extract immediate field
        sll $t3, $t9, 16
        srl $t3, $t3, 16

        #if value is greater than 10
        li $t0, 10
        bge $t3, $t0, three_zero_check
        
        #otherwise print 4 zereos
        li $v0, 4
        la $a0, zero_print
        syscall
        li $v0, 4
        la $a0, zero_print
        syscall
        li $v0, 4
        la $a0, zero_print
        syscall
        li $v0, 4
        la $a0, zero_print
        syscall
        j print_value
        
        three_zero_check:
        #if value is greater than 100
        li $t0, 100
        bge $t3, $t0, two_zero_check
        
        #print 3 zereos
        li $v0, 4
        la $a0, zero_print
        syscall
        li $v0, 4
        la $a0, zero_print
        syscall
        li $v0, 4
        la $a0, zero_print
        syscall
        j print_value
        
        two_zero_check:
        li $t0, 1000
        bge $t3, $t0, one_zero_check
        
        #print 2 zereos and then value
        li $v0, 4
        la $a0, zero_print
        syscall
        li $v0, 4
        la $a0, zero_print
        syscall
        j print_value
        
        one_zero_check:
        #greater than or equal to 10000
        li $t0, 10000
        bge $t3, $t0, no_zeros
        
        #add one zero and print value
        li $v0, 4
        la $a0, zero_print
        syscall    
        j print_value
        
        no_zeros:
        j print_value
        
        #final print; zereos should be added
        print_value:
        move $a0, $t3
        li $v0, 1
        syscall

        j exit    
#------------------------------------------------------------------------------Part 4-------------------------------------------------------------------------------------

	p_operation:

    #load p argument 
    lw $s0, addr_arg1

    #get card values only
    lbu $t0, 0($s0)
    lbu $t1, 1($s0)
    lbu $t2, 2($s0)
    lbu $t3, 3($s0)
    lbu $t4, 4($s0)

    li $s0, 0x0F
    and $t0, $t0, $s0
    and $t1, $t1, $s0
    and $t2, $t2, $s0
    and $t3, $t3, $s0
    and $t4, $t4, $s0

    #load argument again - get rank values
    lw $s0, addr_arg1

    #load into registers t5-t9
    lbu $t5, 0($s0)
    lbu $t6, 1($s0)
    lbu $t7, 2($s0)
    lbu $t8, 3($s0)
    lbu $t9, 4($s0)

    #normalize
    addi $t5, $t5, -0x30
    addi $t6, $t6, -0x30
    addi $t7, $t7, -0x30
    addi $t8, $t8, -0x30
    addi $t9, $t9, -0x30

    #shift out the bits
    srl $t5, $t5, 4
    sll $t5, $t5, 4
    srl $t5, $t5, 4

    srl $t6, $t6, 4
    sll $t6, $t6, 4
    srl $t6, $t6, 4

    srl $t7, $t7, 4
    sll $t7, $t7, 4
    srl $t7, $t7, 4

    srl $t8, $t8, 4
    sll $t8, $t8, 4
    srl $t8, $t8, 4

    srl $t9, $t9, 4
    sll $t9, $t9, 4
    srl $t9, $t9, 4

    #add one so that clubs = 1; hearts = 4
    addi $t5, $t5, 1
    addi $t6, $t6, 1
    addi $t7, $t7, 1
    addi $t8, $t8, 1
    addi $t9, $t9, 1

    addi $s1, $zero, 1

    while:
    addi $s2, $zero, 0

    slt $s3, $t1, $t0
    bne $s3, $zero, swap_t0_t1

    slt $s3, $t2, $t1
    bne $s3, $zero, swap_t1_t2

    slt $s3, $t3, $t2
    bne $s3, $zero, swap_t2_t3

    slt $s3, $t4, $t3
    bne $s3, $zero, swap_t3_t4

    beq $s2, $zero, sort_complete
    j while


    swap_t0_t1:
    
    #swap ranks (swapped cards)
    add $s3, $t0, $zero
    add $t0, $t1, $zero
    add $t1, $s3, $zero

    #swap ranks (swapped cards)
    add $s3, $t5, $zero
    add $t5, $t6, $zero
    add $t6, $s3, $zero

    addi $s2, $zero, 1    
    j while

    swap_t1_t2:
    
    # swap card values
    add $s3, $t1, $zero
    add $t1, $t2, $zero
    add $t2, $s3, $zero

    #swap ranks (swapped cards)
    add $s3, $t6, $zero
    add $t6, $t7, $zero
    add $t7, $s3, $zero

    addi $s2, $zero, 1    
    j while

    swap_t2_t3:
    
    #swap ranks (swapped cards)
    add $s3, $t2, $zero
    add $t2, $t3, $zero
    add $t3, $s3, $zero

    #swap ranks (swapped cards)
    add $s3, $t7, $zero
    add $t7, $t8, $zero
    add $t8, $s3, $zero

    addi $s2, $zero, 1    
    j while

    swap_t3_t4:
    
    #swap ranks (swapped cards)
    add $s3, $t3, $zero
    add $t3, $t4, $zero
    add $t4, $s3, $zero

    #swap ranks (swapped cards)
    add $s3, $t8, $zero
    add $t8, $t9, $zero
    add $t9, $s3, $zero

    addi $s2, $zero, 1    
    j while


    sort_complete:

    look_for_straight:
    sub $s0, $t4, $t0
    li $s1, 4
    beq $s0, $s1, straight_found
    j look_for_four

    look_for_four:

    #check if t0-t3 have the same values
    seq $s0, $t0, $t1 
    seq $s1, $t1, $t2   
    seq $s2, $t2, $t3   

    and $s3, $s0, $s1
    and $s3, $s3, $s2 
    
    #if equal to zero, check if t1-t4  
    beq $s3, $zero, not_four_of_a_kind

    #if they do, make sure all the registers do not match
    seq $s0, $t5, $t6   
    seq $s1, $t5, $t7   
    seq $s2, $t5, $t8  
    seq $s3, $t6, $t7   
    seq $s4, $t6, $t8   
    seq $s5, $t7, $t8 

    or $s6, $s0, $s1   
    or $s6, $s6, $s2  
    or $s6, $s6, $s3   
    or $s6, $s6, $s4   
    or $s6, $s6, $s5   

    beq $s6, $zero, four_found   
    j not_four_of_a_kind 

    not_four_of_a_kind:

    #check if t1-t4 have the same values
    seq $s0, $t1, $t2  
    seq $s1, $t2, $t3   
    seq $s2, $t3, $t4   

    and $s3, $s0, $s1  
    and $s3, $s3, $s2
    
    #if equal to zero, look for double pairs instead now   
    beq $s3, $zero, look_for_pairs

    #if they do, make sure all the registers do not match
    seq $s0, $t6, $t7   
    seq $s1, $t6, $t8   
    seq $s2, $t6, $t9  
    seq $s3, $t7, $t8   
    seq $s4, $t7, $t9   
    seq $s5, $t8, $t9 

    or $s6, $s0, $s1   
    or $s6, $s6, $s2  
    or $s6, $s6, $s3   
    or $s6, $s6, $s4   
    or $s6, $s6, $s5 

    #if registers equal to 0, four pair found otherwise look for next condition of two set pairs
    beq $s6, $zero, four_found
    j look_for_pairs

    look_for_pairs:

    check_t0_t1:
    #check first pair
    seq $s0, $t0, $t1
    beq $s0, $zero, check_t1_t2

    beq $t5, $t6, check_t1_t2

    #keep track of pairs found
    addi $s6, $s6, 1

    check_t1_t2:

    seq $s0, $t1, $t2
    beq $s0, $zero, check_t2_t3

    beq $t6, $t7, check_t2_t3

    addi $s6, $s6, 1

    check_t2_t3:
    seq $s0, $t2, $t3
    beq $s0, $zero, check_t3_t4

    beq $t6, $t7, check_t3_t4

    addi $s6, $s6, 1

    check_t3_t4:

    seq $s0, $t3, $t4
    beq $s0, $zero, check_complete

    beq $t6, $t7, check_complete

    addi $s6, $s6, 1

    check_complete:
    li $s5, 2
    beq $s6, $s5, two_pair_found


    unknown_hand:
    la $a0, unknown_hand_str
    li $v0, 4
    syscall
    j exit

    straight_found:
    la $a0, straight_str
    li $v0, 4
    syscall
    j exit

    four_found:
    la $a0, four_str
    li $v0, 4
    syscall
    j exit

    two_pair_found:
    la $a0, pair_str
    li $v0, 4
    syscall
    j exit

exit:
  li $v0, 10
  syscall
