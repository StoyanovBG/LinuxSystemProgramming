#include<stdio.h>
#include<stdlib.h>

void inplace_reverse(char str[])
{
	int i, num;
	int temp = 0;
	
	for(num = 0; str[num] != 0; num++)
	{
		for(i = 0; i < num / 2; i++)
		{
			temp = str[i];
			str[i] = str[num - 1 - i];
			str[num - 1 -i] = temp;
		}
	}
	for(i = 0; i < num; i++)
		putchar(str[i]);
}

void __attribute__ ((constructor)) initLibrary(void)
{
	printf("Library is initialized\n");
}
void __attribute__ ((destructor)) cleanupLibrary(void)
{
	printf("Library is exited \n");
}
