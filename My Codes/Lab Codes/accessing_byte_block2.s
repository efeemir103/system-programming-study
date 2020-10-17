.cpu cortex-m0plus
.thumb

.global main
Mem_Addr = 0x20000040
Results_Addr = 0x20000044
Mem_Block_Size = 4
main:
	// Fill the memory from 0x20000040

	ldr r0, =Mem_Addr // set pointer to memory location (0x20000040)
	mov r1, #0xF0 // r1 = #0xF0
	lsl r1, r1, #8 // r1 = #0xF000
	add r1, r1, #0xF1 // r1 = #0xF0F1
	lsl r1, r1, #8 // r1 = #0xF0F100
	add r1, r1, #0xF2 // r1 = #0xF0F1F2
	lsl r1, r1, #8 // r1 = #0xF0F1F200
	add r1, r1, #0xF3 // r1 = #0xF0F1F2F3
	str r1, [r0] // save to memory location (0x20000040)

	// Read from memory to register

	mov r1, #1
	mov r4, #0 // odd counter
	mov r5, #0 // even counter
	ldr r2, [r0] // read whole register

	// Count even and odd ones

	mov r3, #1
	and r3, r3, r2 // odd: r3 = 1 even: r3 = 0
	add r4, r4, r3 // add to odd counter
	eor r3, r3, r1 // r3 = !r3 (not operation using exclusive or)
	add r5, r5, r3 // add to even counter
	lsr r2, r2, #8 // shift a byte to right

	mov r3, #1
	and r3, r3, r2 // odd: r3 = 1 even: r3 = 0
	add r4, r4, r3 // add to odd counter
	eor r3, r3, r1 // r3 = !r3 (not operation using exclusive or)
	add r5, r5, r3 // add to even counter
	lsr r2, r2, #8 // shift a byte to right

	mov r3, #1
	and r3, r3, r2 // odd: r3 = 1 even: r3 = 0
	add r4, r4, r3 // add to odd counter
	eor r3, r3, r1 // r3 = !r3 (not operation using exclusive or)
	add r5, r5, r3 // add to even counter
	lsr r2, r2, #8 // shift a byte to right

	mov r3, #1
	and r3, r3, r2 // odd: r3 = 1 even: r3 = 0
	add r4, r4, r3 // add to odd counter
	eor r3, r3, r1 // r3 = !r3 (not operation using exclusive or)
	add r5, r5, r3 // add to even counter
	lsr r2, r2, #8 // shift a byte to right

	ldr r6, =Results_Addr // save results to some memory location (0x20000044)
	str r4, [r6] // save odds
	str r5, [r6, #Mem_Block_Size] // save evens to next memory location (0x20000048)

end: b end

.end

