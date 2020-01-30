#include "iostream"

const char   Keyboard[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";

int main(int argc, char **argv)
{
    int ch;
    while ((ch = getchar()) != EOF)
    {
        int i;
        for (i = 0; Keyboard[i] && Keyboard[i] != ch; ++i)
            ;

        if (Keyboard[i] && ch != '`')
            putchar(Keyboard[i-1]);
        else
            putchar(ch);
    }

    exit(0);
}