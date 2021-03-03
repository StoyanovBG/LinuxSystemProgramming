#include <stdio.h>
#include "reverselib/reverse.h"
#include "reverselib/answer.h"

int main(int argc, char* argv[]){
	setString("abc");
	printf("The reverse of 'abc' is %s\n", reverse("abc"));
	printf("The answer is: %s\n", answer());
	return 0;
}
