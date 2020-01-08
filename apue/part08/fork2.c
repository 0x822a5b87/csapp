#include "../apue.h"

// 如果调用 fork() 后，既不希望父进程等待子进程终止
// 也不希望子进程变成僵尸进程，等待父进程退出时才被回收
// 可以利用下面这个技巧，fork() 两次来实现
// 其实原理很简单，就是我们创建三个进程：parent, child, second child
// parent 使用 waitpid(child, NULL, 0) 等待 child 退出
// child 立即退出
// 这样 second child 就会被变成孤儿进程并被 init 进程收养
// 之所以要创建 second child，是因为
// 1. 我们不能直接 wait(child, NULL, 0) 来实现，这会阻塞父进程
// 2. 我们也不能在 child 中 sleep 保证 child 会比 parent 先退出
// 所以我们利用两次 fork，保证了退出顺序一定为
// child -> parent
// 而 second child 的退出可能在任意时刻，但是当 child 退出时它会立刻变成 init 的进程的子进程
// 而 child 是立即退出的，所以及时 second child 会有一段时间是僵尸进程
// 也只会持续很短的时间

int main(int argc, char **argv)
{
    pid_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0) {
        // child process
        if ((pid = fork()) < 0)
            err_sys("fork error");
        else if (pid > 0)
            // child process
            exit(0);

        // second child process
        sleep(2);
        // 必须将 getppid() 转换为 long，因为 int 不一定能存放下 getppid()，而 long 一定可以
        printf("second child, parent pid = %ld\n", (long) getppid());
        exit(0);
    }

    // parent process
    if (waitpid(pid, NULL, 0) != pid)
        err_sys("waitpid error");

    exit(0);
}