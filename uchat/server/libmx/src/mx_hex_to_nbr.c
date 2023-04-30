#include "../inc/libmx.h"




bool mx_isalpha(int c) {
    if((c>64&&c<91)||(c>96&&c<123)) {
        return true;
    }
    else { 
        return false;
    }
}


unsigned long mx_hex_to_nbr(const char * hex) {
    if(!hex)return 0;
    unsigned long res=0;
    for(int i = 0; hex[i] !='\0'; i++) {
        if(mx_isdigit(hex[i])) {
            res*=16;
            res+=hex[i]-'0';
        }else if(mx_isalpha(hex[i])) {
                if(hex[i]=='a'||hex[i]=='A') {
                    res*=16;
                    res+=10;
                }else if(hex[i]=='b'||hex[i]=='B') {
                    res*=16;
                    res+=11;
                }
                else if(hex[i]=='c'||hex[i]=='C') {
                    res*=16;
                    res+=12;
                }else if(hex[i]=='d'||hex[i]=='D') {
                    res*=16;
                    res+=13;
                }else if(hex[i]=='e'||hex[i]=='E') {
                    res*=16;
                    res+=14;
                }else if(hex[i]=='f'||hex[i]=='F') {
                    res*=16;
                    res+=15;
                }else return 0;
        }else return 0;
    }
    return res;
}


