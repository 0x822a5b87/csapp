#include <stdio.h>
#include <unistd.h>


int main() {
    pid_t child_pid;
    child_pid = fork();
    if (child_pid) { // fork a child, child will exit straight away
        char name[128];
        sprintf(name, "/proc/%d/stat", child_pid);
        char line[2048];

        // read childs /proc/pid/stat, field 3 will give its status
        FILE * fp = fopen(name, "r");

        while (fgets(line, sizeof(line), fp))
            puts(line);

        fclose(fp);

        usleep(5000000);

        // by now the child will have exited for sure, repeat
        fp = fopen(name, "r");

        while (fgets(line, sizeof(line), fp))
            puts(line);

        fclose(fp);

        // make another child to repeat the process and exit the parent
        if (!fork()) {
            usleep(5000000);
            // both parent and child will have exited by now

            fp = fopen(name, "r");

            // this should fail because init has already cleaned up the child
            if (!fp) {
                perror("fopen");
                return -1;
            }

            while (fgets(line, sizeof(line), fp))
                puts(line);

            fclose(fp);
        }

    }

    return 0;
}