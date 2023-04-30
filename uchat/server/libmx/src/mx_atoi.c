#include "../inc/libmx.h"

bool mx_isdigit(int c) {
    if(c>47&&c<58) {
        return true;
    }
    else { 
        return false;
    }
}
bool mx_isspace(char c) {
    if(c==' '||c=='\t'
    ||c=='\n'
    ||c=='\v'
    ||c=='\f'
    ||c=='\r') {
        return true;
    }
    else { 
        return false;
    }
}


int mx_atoi(const char *str) {
    int i=0;
    int neg=1;
    if(str[i]=='-') {
        i++;
        neg=-1;
    }else if(str[i]=='+'){
    	i++;
    }
    int res=0;
    while(mx_isdigit(str[i])) {
        res*=10;
        res+=str[i]-'0';
        i++;
    }
    return res*neg;
}

