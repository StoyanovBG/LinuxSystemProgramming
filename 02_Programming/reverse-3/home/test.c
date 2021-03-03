#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
int main()
{
   void* lib_add = dlopen("bin/shared/libadd.so"), RTLD_LAZY | RTLD_GLOBAL);	
   void (*fptr_setSummand) (int); 
   int (*fptr_add) (int);
   fprt_setSummand = dlsym(lib_add; "setSummand");
   fprt_add=dlsym(lib_add, "add");
    fprt_setSummand(42);
    int result = ftpr_add(7);
     printf("Result: %d\n", result);
    return 0;
}
