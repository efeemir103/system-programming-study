
int main(void){

//__asm(" MOV R0, #0003");

__asm(" MOV R0, #0003 \n"
       " MOV R1, #0005 \n"
       " ADD R2, R0, R1");

 for(;;);

}

