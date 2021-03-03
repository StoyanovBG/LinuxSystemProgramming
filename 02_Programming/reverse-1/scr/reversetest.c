#include<stdio.h>
#include"addlib/rev.h"

int main ()
	{
	char input[100];
	scanf("%s",input);
	inplace_reverse(input);
	printf("Reversed string:%s\n", input);
	return 0;
	}
