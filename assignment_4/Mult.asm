// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

//Set Register 2 equal to 0.
@R2
M=0

(LOOP)
    @R0 //SET D TO R0 VALUE
    D=M

    @EXITLOOP //EXIT LOOP IF D IS EQUAL TO 0
    D;JEQ

    @R0 //DECREASE R0 VALUE BY 1
    M=M-1

    @R1 //SET D TO R1 VALUE
    D=M

    @R2 //ADD D TO R0 VALUE
    M=M+D

    @LOOP //GO TO BEGINING OF LOOP
    0;JMP

(EXITLOOP)