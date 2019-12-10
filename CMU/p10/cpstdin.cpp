//
// Created by 杜航宇 on 2019/12/10.
//

#include <fcntl.h>
#include <unistd.h>
#include <printf.h>

int main()
{
    const unsigned int buf_size = 128;
    char *buf = new char[buf_size];

    int fd = open(__FILE__, O_RDONLY);
    ssize_t read_size;
    while ((read_size = read(fd, buf, buf_size)) > 0)
    {
        write(STDOUT_FILENO, buf, read_size);
        // 下面这种是错误的，当缓冲区不包含 buf_size 个字符时将打印错误的字符
        //write(STDOUT_FILENO, buf, buf_size);
    }
    if (read_size != 0)
    {
        printf("read data error : [%lu]\n", read_size);
    }


    close(fd);
}
