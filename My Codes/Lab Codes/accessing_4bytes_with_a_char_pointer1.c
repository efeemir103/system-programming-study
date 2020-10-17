unsigned int temp; // just a temporary integer to buffer 4 byte blocks of data read from memory.
unsigned char nBytes[16]; // debug array we will use to write our read bytes.
unsigned int avg;

unsigned char *charMemoryPointer; // our pointer that we will use to enter values to memory with.
unsigned int *intMemoryPointer; // our pointer that we will use to read values from memory with.

int main(void)
{
	int i, j; // indexes
	charMemoryPointer = (unsigned char *) 0x20000040; // start point
	for(i=0;i<16;i++){
		*charMemoryPointer = 0xF0 + i; // writing hexadecimals to memory using a simple char pointer.
		charMemoryPointer++;
	}

	intMemoryPointer = (unsigned int *) 0x20000040; // start point
	for(i=0;i<4;i++){
		temp = *intMemoryPointer; // getting value of 4 byte memory block just using a integer (4 byte).
		for(j=0;j<4;j++){
			nBytes[i*4+j] = temp; // assigning the values read from memory into array just to debug.
			avg += (unsigned char) temp; // summing up each number as characters (1 byte) by type casting to char.
			temp = temp >> 8; // shifting 1 byte to get next byte until we reach end of our 4 byte memory block.
		}
		intMemoryPointer++; // getting next 4 byte block of memory till we get all 16 byte space.
	}
	avg/=16;
	for(;;);
}

