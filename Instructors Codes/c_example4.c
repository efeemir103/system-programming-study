/*
int a=3;
int *a_pointer;

int main(void)
{

	a_pointer=&a;
	*a_pointer=5;

	for(;;);
}
*/

int main(void)
{

	int a[5]={1,2,3,4,5};
	int *a_pointer;
	int b;

	a_pointer=a;
	a_pointer+=3;
	*a_pointer=0;

	a_pointer+=2;
	*a_pointer=6;
	b=a[5];


	for(;;);
}

