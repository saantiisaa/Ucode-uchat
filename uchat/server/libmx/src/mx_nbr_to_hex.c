#include "../inc/libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    if(!nbr) {
        return 0;
    }
    unsigned long nbr2=nbr;
    int count = 0;
    while (nbr2 > 0) {
        //nbr2%16;
        nbr2/=16;
        count++;
    }
    
    char *temp=mx_strnew(count);
    for(int i = 0; i < count; i++) {
        if(nbr%16<10) {
            temp[i]=nbr%16+'0';
        }else if(nbr%16==10) {
            temp[i]='a';
        }else if(nbr%16==11) {
            temp[i]='b';
        }else if(nbr%16==12) {
            temp[i]='c';
        }else if(nbr%16==13) {
            temp[i]='d';
        }else if(nbr%16==14) {
            temp[i]='e';
        }else if(nbr%16==15) {
            temp[i]='f';
        }
        nbr/=16;
    }
    char *res=mx_strnew(count);
    int j=count-1;
    for(int i = 0; i < count; i++) {
        res[i]=temp[j];
        j--;
    }
    return res;
}

