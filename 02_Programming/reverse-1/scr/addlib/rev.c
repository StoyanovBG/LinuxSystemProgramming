#include <string.h> 

void inplace_reverse(char * str)
{
  if (str)
  {
    char * end = str + strlen(str) - 1;

#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

    while (str < end)
    {
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}
