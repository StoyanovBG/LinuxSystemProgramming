#include <stdio.h>
#include <string.h>
char* str;
char* reversestr;
int length;
void setString(char* string) {
	str = string;
}
char* reverse(char* str){
	length = strlen(str);
	for (int i=0; i<length;i++){
		reversestr[length-i]=str[i];
	}
	return reversestr;
}
void __attribute__ ((constructor)) initLibrary(void){
	printf("Library is initialized\n");
	str='\0';
}
void __attribute__ ((destructor)) cleanUpLibrary(void){
	printf("Library is exited\n");
}


