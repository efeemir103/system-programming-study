.cpu cortex-m0plus
.thumb

.global main

func1:
	add r0, r1, r1
	bx lr

main:
	movs r0, #2
	mov r1, #4
	bl func1
	mov r2, #3

end: b end

