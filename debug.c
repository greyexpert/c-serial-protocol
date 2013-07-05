#include <stdio.h>
#include <string.h>

#include "debug.h"


void printb( uint64_t n) {
    int size = sizeof(n) * 8;
    char buff[size];
    memset(buff, '0', size);
    
    int i = 0;
    
    while (n) {
        buff[i] = n & 1 ? '1' : '0';
        n >>= 1;
        i++;
    }

    int foo = i % 8;
    i = foo > 0 ? i - foo + 8 : i;

    for (i = i - 1; i >= 0; i-- ) {
        putchar(buff[i]);
        
        if ( i % 8 == 0 ) {
            putchar(' ');
        }
    }
 
    printf("\n");
}
