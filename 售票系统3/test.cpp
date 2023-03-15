#include <stdio.h>
#include <string.h>

int main () {
    char a[128] = "1234567890123456789012234567890";
    char b[128] = "******";
    char c[128] = "------";
    strcpy(c,a);
    strcat(c,"&&&&&&");
    printf("%s\n",c);
    strcpy(b,a);
    printf("%s\n",b);

    return(0);
}