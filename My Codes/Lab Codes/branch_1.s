.cpu cortex-m0plus
.thumb

.global main
Mem_Addr = 0x20000040
Result_Addr = 0x20000030
main:
	// Fill the memory from 0x20000040
	ldr r0, =Mem_Addr // set pointer to memory location (0x20000040)
	ldr r1, =0xf0f1f2f3 // r1 = 0xf0f1f2f3
	str r1, [r0, #0] // store r1 in memory
	ldr r1, =0xf4f5f6f7 // r1 = 0xf4f5f6f7
	str r1, [r0, #4] // store r1 in memory
	ldr r1, =0xf8f9fafb // r1 = 0xf8f9fafb
	str r1, [r0, #8] // store r1 in memory
	ldr r1, =0xfcfdfeff // r1 = 0xfcfdfeff
	str r1, [r0, #12] // store r1 in memory

	// Start of loop that will read bytes from memory and count odd and even characters.
	mov r4, #0 // odd counter
	mov r5, #0 // even counter

	mov r7, #0 // this register will hold total bytes read from memory.
	mov r1, #1 // this will be used later to get a logical not using xor.

memory_iterate_loop: // this loop will read total 16 bytes of memory by a nested loop which uses shifting to parse bytes.
	mov r6, #0 // this register will hold total bytes buffered and tested to be odd or even from 4 byte block.
	ldr r2, [r0, r7] // read from address r0 by offset r7

parser_loop: // This loop will parse 4 byte block byte by byte till it reads all the bytes by shifting right.
	mov r3, #1 // Just a dummy register will be used later to hold if number is odd or not.
	and r3, r3, r2 // odd: r3 = 1 even: r3 = 0
	add r4, r4, r3 // add to odd counter
	eor r3, r3, r1 // r3 = !r3 (not operation using exclusive or)
	add r5, r5, r3 // add to even counter
	lsr r2, r2, #8 // shift a byte to right
	add r6, #1 // increment the number of bytes read from memory
	cmp r6, #4 // If all 4 bytes block was read.
	beq end_parser // branch to end of 4 byte parsing loop.
	b parser_loop // else just re-loop until condition is satisfied.

end_parser:
	add r7, #4 // If all 4 bytes were parsed we can increment our total number of bytes read by 4.
	cmp r7, #16 // If all 16 bytes were read
	beq end_memory_iterate_loop // branch to end of 16 byte parsing loop.
	b memory_iterate_loop // else just re-loop until condition is satisfied.

end_memory_iterate_loop:

	cmp r5, r4 // check if r5 (even count) is greater then r4 (odd count)
	bgt even_gt_odd // If so branch to label matched.
	b otherwise // Otherwise branch to last label.

even_gt_odd:
	ldr r0, =Result_Addr // Point r0 to memory address 0x20000030.
	ldr r1, =0xffffffff // r1 = 0xffffffff
	str r1, [r0] // Fill the memory address 0x20000030 with 0xffffffff.
	b end

otherwise:
	ldr r0, =Result_Addr // Point r0 to memory address 0x20000030.
	ldr r1, =0xf0f0f0f0 // r1 = 0xf0f0f0f0
	str r1, [r0] // Fill the memory address 0x20000030 with 0xf0f0f0f0.

end: b end

.end

