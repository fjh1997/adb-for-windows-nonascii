#include <stdio.h>
#include <locale.h>
extern char * __cdecl basename (char *path);
extern char * __cdecl dirname (char *path);

void xprint(const char *s)
{
    while (*s)
        printf("\\x%02x", (int)(unsigned char)(*s++));
}

int main(int argc, char **argv)
{
    char input[] ={0x2f,0xe8,0xaf,0x97,0x79,0x2f,0xe8,0xaf,0x97,0x7a,0x00};// /诗y/诗z
    char input2[] ={0x2f,0xe8,0xaf,0x97,0x79,0x2f,0xe8,0xaf,0x97,0x7a,0x00};// /诗y/诗z
    char *output;
    printf("basename(\"");
    xprint(input);
    printf("\") = \"");
    output = basename(input);
    xprint(output);
    printf("\ndirname(\"");
    xprint(input2);
    printf("\") = \"");
    output = dirname(input2);
    xprint(output);
    printf("\"\n");
 
    return 0;
}

