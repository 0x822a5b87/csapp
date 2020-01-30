#include "iostream"

int main(int argc, char **argv)
{
    int ch;
    bool leftQuote = true;
    while ((ch = getchar()) != EOF)
    {
        if (ch == '"')
        {
            if (leftQuote)
            {
                printf("``");
            }
            else
            {
                printf("''");
            }
            leftQuote = !leftQuote;
        }
        else
        {
            putchar(ch);
        }
    }
    exit(0);
}