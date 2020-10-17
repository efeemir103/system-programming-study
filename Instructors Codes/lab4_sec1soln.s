.cpu cortex-m0plus
.thumb

.global main

Mem_Addr1=0x20000040
Mem_Addr2=0x20000030

Val1=0xFFFFFFFF
Val2=0xF0F0F0F0

main:

 LDR R0, =Mem_Addr1

//Fill the memory content
//can be done by brnach instructions as well.
 LDR R1, =0x0F1F2F3F
 STR R1, [R0]

 ADD R0, R0, #4
 LDR R1, =0x4F5F6F7F
 STR R1, [R0]

 ADD R0, R0, #4
 LDR R1, =0x8F9FAFBF
 STR R1, [R0]

 ADD R0, R0, #4
 LDR R1, =0xCFDFEFFF
 STR R1, [R0]

 //revisit the memory content, find their average
 LDR R0, =Mem_Addr1

 //reset the total sum
 MOV R1, #0x00
 LDR R3, =Mem_Addr2
 STR R1, [R3]

 MOV R1, #0x03
Loop1:

 LDR R3, =0x000000FF

 LDR R2, [R0]

 MOV R4, R2
 AND R4, R4, R3

 LSR R5, R2, #8
 AND R5, R5, R3

 LSR R6, R2, #16
 AND R6, R6, R3

 LSR R7, R2, #24
 AND R7, R7, R3

 ADD R4, R4, R5
 ADD R4, R4, R6
 ADD R4, R4, R7

 LDR R3, =Mem_Addr2
 LDR R5, [R3]
 ADD R4, R4, R5
 STR R4, [R3]

 ADD R0, R0, #0x04

 SUB R1, R1, #0x01 // R1 = R1 - 1
 BPL Loop1

//take the average value
 LDR R3, =Mem_Addr2
 LDR R1, [R3]
 LSR R1, R1, #4

 LDR R2, =0x1000
 CMP R1, R2
 BHS Greater // Branch if higher or same
 LDR R5, =Val2
 STR R5, [R3]
 B Done1
Greater:
 LDR R5, =Val1
 STR R5, [R3]
Done1:

end: B end

