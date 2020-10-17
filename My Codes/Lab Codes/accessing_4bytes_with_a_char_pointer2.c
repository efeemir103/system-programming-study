unsigned int *memoryPtr_1;
unsigned char *memoryPtr_2;

int main(void)
{
	int i;
	unsigned char buffer; // we will read to this variable to after check if the buffered number is even or odd.
	memoryPtr_1 = (unsigned int *) 0x20000040; // start point to write to memory.
	for(i=0;i<16;i+=4){ // increment by 4 just to get the wanted format for hexadecimals.
		*memoryPtr_1 = 0xF0F0F0F0 + 0x1000000*i + 0x10000*(i+1) + 0x100*(i+2) + 0x1*(i+3); // constructing hexadecimals to write to memory.
		memoryPtr_1++; // increment to new memory location (4 bytes memory block size because of integer).
	}
	memoryPtr_2 = (unsigned char *) 0x20000040; // start point to read from memory.
	for(i=0;i<16;i++){
		buffer = *memoryPtr_2; // read with a char pointer.
		if(buffer%2){
			*memoryPtr_2 = 0x00; // assign 0x00 if even.
		}
		else{
			*memoryPtr_2 = 0xFF; // assign 0xFF if odd.
		}
		memoryPtr_2++; // increment the char pointer to reach to next space of 1 bytes.
	}
	for(;;);
}

