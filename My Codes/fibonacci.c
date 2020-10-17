int main(void){
	unsigned int *result = (unsigned int *) 0x20000040;
	__asm(" mov r0, #0\n"
			" mov r1, #1\n"
			" mov r3, #0\n"
			" ldr r4, =0x20000040\n"
			"loop:\n"
			" add r2, r1, r0\n"
			" mov r0, r1\n"
			" mov r1, r2\n"
			" add r3, #1\n"
			" cmp r3, #10\n"
			" beq loop_end\n"
			" b loop\n"
			"loop_end:\n"
			" str r1, [r4]\n");
	for(;;);
	return 0;
}

