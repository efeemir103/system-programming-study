.cpu cortex-m0plus
.thumb

.global main

main:
	mov r0, #0
	mov r1, #1
	mov r3, #0
	ldr r4, =0x20000040

loop:
	add r2, r1, r0
	mov r0, r1
	mov r1, r2
	add r3, #1
	cmp r3, #10
	beq loop_end\n"
	b loop

loop_end:
	str r1, [r4]

end: b end

.end
