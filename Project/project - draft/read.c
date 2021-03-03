#include <stdio.h>

int main(void) {
    char str[16];
    int i;
    while(fgets(str, sizeof str, stdin) != NULL) {  // reads newline too
        i = 0;
        while (str[i] >= ' ') {                     // shortcut to testing newline and nul
            printf("%d", str[i]);                  // print char value
            i++;
        }
        printf ("\n");
        str[i] = '\0';                              // truncate the array
    }
    return 0;
}
