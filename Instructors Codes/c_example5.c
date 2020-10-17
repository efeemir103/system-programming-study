//STM32L0
unsigned int a;
int *mem_loc;

int main(void){

 mem_loc = (int *) 0x20000040;

 *(mem_loc)   = 0x1;
 *(mem_loc+1) = 0x2;

 __asm(" LDR R7, =0x20000040 \n"
	   " LDR R0, [R7] \n"
	   " LDR R7, =0x20000044 \n"
	   " LDR R1, [R7] \n"
	   " ADD R2, R1, R0 \n"
	   " LDR R7, =0x20000048 \n"
	   " STR R2, [R7] \n");

 a=*(mem_loc+2);

 for(;;);
}

