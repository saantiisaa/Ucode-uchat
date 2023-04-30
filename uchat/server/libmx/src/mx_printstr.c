#include "../inc/libmx.h"

void mx_printstr(const char *s) {
   int size=0;
   int i=0;
   while( s[i]) {
      size++;
      i++;
   }
   write(1,s,size);
}

