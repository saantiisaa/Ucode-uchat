#include "../inc/libmx.h"
void mx_print_unicode(wchar_t c) {
    char chr[4];
    int size = 0;
	if (c<0x80) {
		chr[0] = (c >> 0 & 0x7F) | 0x00;
        size = 1;
	} else if (c<0x0800) {
		chr[0] = (c >> 6 & 0x1F) | 0xC0;
		chr[1] = (c >> 0 & 0x3F) | 0x80;
        size = 2;
	} else if (c<0x010000) {
		chr[0] = (c >> 12 & 0x0F) | 0xE0;
		chr[1] = (c >> 6 & 0x3F) | 0x80;
		chr[2] = (c >> 0 & 0x3F) | 0x80;
        size = 3;
	} else {
		chr[0] = (c >> 18 & 0x07) | 0xF0;
		chr[1] = (c >> 12 & 0x3F) | 0x80;
		chr[2] = (c >> 6 & 0x3F) | 0x80;
		chr[3] = (c >> 0 & 0x3F) | 0x80;
        size = 4;
	}
    //for(int i = 0; i < )
    write(1,&chr,size);
}   

//int main(){
//    setlocale(LC_CTYPE, "");
    //mx_print_unicode((wchar_t)"й");
//    mx_print_unicode((wchar_t)'i');
//}
