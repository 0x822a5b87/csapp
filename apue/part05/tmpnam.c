#include "../apue.h"

int main(int argc, char **argv)
{
    char name[L_tmpnam], line[MAXLINE];
    FILE *fp;

    char *tp = tmpnam(NULL);
    printf("%s\n", tp);

    char *tp2 = tmpnam(name);
    printf("tp = %s, tp2 = %s, name = %s\n", tp, tp2, name);

    tp2 = tmpnam(NULL);
    printf("tp = %s, tp2 = %s, name = %s\n", tp, tp2, name);


    if ((fp = tmpfile()) == NULL)
        err_sys("tmpfile error");
    fputs("one line of output\n", fp);
    rewind(fp);
    if (fgets(line, MAXLINE, fp) == NULL)
        err_sys("fgets error");
    fputs(line, stdout);
}