#include<stdio.h>
#include<stdlib.h>
#include "addlib/reverse.h"

int main()
{
	char str[100];
	printf("Enter string to be reversed: ");
	printf("%s", str);

	printf("\n Reversed string: ");
	inplace_reverse(str);
	
	return 0;
}
