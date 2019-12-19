# 网络编程

## 11.1 客户端-服务器编程模型

1. 每个网络应用都是基于 `客户端-服务器` 模型的
2. **服务端和客户端是进程，而不是机器**

## 11.2 网络

1. **网络也是一种 I/O 设备**
2. 网卡的输入和输出就是与内存的数据交换：网卡 <-> I/O 总线 <-> 内存总线 <-> 内存
3. 网络的最底层是 `LAN(local address netword, 局域网)`
	3.1 `以太网(Ethernet)` 是一种局域网
	3.2 局域网通过集线器连接
	3.3 多个小的局域网可以通过 `桥(bridge)` 连接成一个更大的局域网
4. 多个局域网可以通过 `路由器` 形成一个更大的互联网

## 11.3 全球 IP 因特网

### 11.3.1 IP 地址

1. IP 地址是一个 **32位无符号整数** 被存放在一个 struct 中：

```c
struct in_addr {
	uint32_t s_addr;
};
```
2. `TCP/IP` 协议族定义了 **网络字节顺序**，所以只要是 TCP/IP 协议，它们的网络字节序就是一样的

### 11.3.2 域名

1. 域名是一个层次性的结构，最顶级的是未命名的根目录；
2. 在根目录下的是一级域名：例如 `com`, `edu`
3. 随后的是个人和组织可以申请的二级域名，例如 `tencent`, `oa` 
4. 当有一级域名和二级域名之后，可以随意的分配后续的域名了。例如 `hello.oa.com` 和 `hello.world.oa.com` 实际上都是在域名 `oa.com` 下
5. `DNS` 维护了 **域名和IP地址之间的映射关系**
6. 每个主机都有本地定义的域名 `localhost` 并且该地址映射为 `127.0.0.1`

### 11.3.3 因特网连接

1. 由于服务端和客户端的是进程级的，所以我们可以认为他们是 **点对点** 的，而从数据流动的角度来讲，他们是 **全双工的**。
2. 一个套接字由一个 `IP` 地址和一个 `端口` 组成
3. **一个连接是由两端的套接字地址唯一确定的**。

## 11.4 套接字接口

>
>		客户端					服务端
>
>		getaddrinfo				getaddrinfo
>		socket					socket
>								bind
>								listen
>
>		connect		------>		accept
>		write		------>		read
>		read		<------		write
>		close  -- 发送EOF -->	read
>								close

## 总结

1. **socket 就是一个打开的文件**，我们可以看到 socket 在构造的时候，是不需要 IP 地址和端口的；
2. 当我们通过 `socket` 构造了一个套接字之后，我们相当于构造了一个文件来抽象 I/O。但是此时，我们还不知道这个文件要和谁进行通信；
3. 对于服务端，我们通过 bind 服务器地址和 fd 绑定起来；并且由于内核创建的套接字默认是接受连接的套接字，我们需要通过 listen 告诉内核这是一个服务端套接字
4. 对于客户端，我们需要通过 connect 来请求与服务端建立一个连接。

### 11.4.1 套接字地址结构

1. 从 linux 程序的角度来讲，**套接字就是一个有相应描述符的打开文件**

```c
struct sockaddr_in {
	uint16_t sin_family;					// 2 bytes
	uint16_t sin_port;						// 2 bytes
	struct in_addr sin_addr;				// 4 bytes
	unsigned char sin_zero[8];				// 使得 sockaddr_in 和 sockaddr 一样大
};

struct sockaddr {
	uint16_t sa_family;
	char sa_data[14];						// 0-1 bytes 为 port,2-5 bytes 为 ip, 6-13 未使用
};
```

### 11.4.2 socket 函数

1. 服务端或者客户端调用 `socket` 来创建一个 **套接字描述符**，对于 linux 来讲，他就是一个普通的文件描述符；
2. **调用 socket 返回的描述符仅仅是 `部分打开` 的，还不能用于读写**。如何完成后续的打开操作依赖于是客户端还是服务端

```c
     #include <sys/socket.h>

     int socket(int domain, int type, int protocol);

	 Socket(AF_INET, SOCK_STREAM, 0);
```

1. The domain parameter specifies a communications domain within which communication will take place; this selects the protocol family which should be used.
2. The socket has the indicated type, which specifies the `semantics of communication`.  Currently defined types are:
	2.1 A `SOCK_STREAM` type provides sequenced, reliable, two-way connection based byte streams.
3. The protocol specifies a particular protocol to be used with the socket.

### 11.4.3 connect 函数

```c
#include <sys/socket.h>

int connect(int clientfd, const struct sockaddr *addr, socklen_t addrlen);
```

The parameter socket is a socket.  If it is of type SOCK_DGRAM, this call specifies the peer with which the socket is to be associated; this address is that to which
     datagrams are to be sent, and the only address from which datagrams are to be received.  If the socket is of type SOCK_STREAM, this call attempts to make a connection
     to another socket.  The other socket is specified by address, which is an address in the communications space of the socket.

### 11.4.4 bind

1. `bind` 告诉内核 将 addr 中的 **服务器套接字地址** 和套接字描述符 sockfd 联系起来；

```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

### 11.4.5 listen

1. 客户端主动向服务端发送连接请求，而服务端则被动的接受客户端的请求
2. 对于 socket 创建的套接字，内核默认它是一个客户端连接，而 listen 函数会内核，描述符是一个服务端连接

```c
#include <sys/socket.h>

int listen(int sockfd, int backlog);
```

### 11.4.6 accept

1. 服务器通过 accept 函数来等待来自客户端的请求
2. accept 函数等待客户端请求来到 listenfd ，然后在 addr 中填上客户端的套接字地址，并返回一个 `已连接描述符`，这个描述符可以被用来和客户端进行通信
3. `监听描述符` 是在调用 listen 时返回的，而 `已连接描述符` 会在每次新的连接时都生成一次。
4. `监听描述符` 是所有客户端和服务端共有的，而 `已连接描述符` 则是某个客户端和服务端私有的


```c
#include <sys/socket.h>

int accept(int listenfd, struct sockaddr *addr, int *addrlen);
```

### simple example

1. 必须对从命令行传递的端口调用 `htons` 将主机序转换为网络序；
2. 必须将 `127.0.0.1` 的地址转换为 uint32_t 的地址
3. 必须将 `sockaddr_in` 转换为 `sockaddr`，他们的大小一样，所以可以完全正常的互相转换；

```c
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "sys/socket.h"
#include "stdio.h"

int main(int argc, char **argv)
{
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0) {
        printf("create socket failed\n");
        return -1;
    }

    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(atoi(argv[2]));
    struct in_addr ip;
    int            iton = inet_pton(AF_INET, argv[1], &ip);
    if (iton < 0) {
        printf("parse ip addr failed\n");
        return -2;
    }
    sa.sin_addr = ip;

    int connectfd = connect(clientfd, (struct sockaddr *)&sa, sizeof(sa));
    if (connectfd == 0) {
        printf("connect successfully\n");
        exit(0);
    }
}
```

### 11.4.7 主机和服务的转换

```c++
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int getaddrinfo(const char *host, const char *service, const struct addrinfo *hints, struct addrinfo **result);

void freeaddrinfo(struct addrinfo *result);

const char *gai_strerror(int errcode);
```

#### getaddrinfo

- `host` can be either a domain name, such as "example.com", an address string, such as "127.0.0.1", or NULL, in which case the address 0.0.0.0 or 127.0.0.1 is assigned depending on the hints flags.
- `service` can be a port number passed as string, such as "80", or a service name, e.g. "echo". In the latter case a typical implementation uses getservbyname() to query the file /etc/services to resolve the service to a port number.
- `hints` can be either NULL or an addrinfo structure with the type of service requested.
- `result` is a pointer that points to a new addrinfo structure with the information requested after successful completion of the function.

1. 在我们调用 getaddrinfo  方法之后， **函数会在内部为我们分配内存存储返回的 addrinfo，因为我们没办法在调用这个函数之前知道结果链表中的元素 个数**，所以我们在最后需要调用 `freeaddrinfo`
2. 在我们调用完毕之后，我们可以在循环中去执行 connect(客户端)或者bind和listen(服务端)直到连接成功
3. 最后一定不能忘记调用 `freeaddrinfo`，否则会有内存泄漏

```c
#include <netdb.h>
#include "stdio.h"
#include "../csapp.hpp"


int main()
{
	struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;

	struct addrinfo addr;
    struct addrinfo *result = &addr;

    int ret = getaddrinfo("127.0.0.1", "8080", hints, &result);
    if (ret < 0)
    {
        unix_error("error getaddrinfo\n");
        exit(0);
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        unix_error("error create socket");
        exit(0);
    }

    int connfd = -1;
    for (struct addrinfo *start = result;
         start != NULL && connfd != 0;
         start = start->ai_next)
    {
        struct sockaddr    *aa = result->ai_addr;
        struct sockaddr_in *sa = (struct sockaddr_in *) aa;
        printf("addr = [%d], port = [%d]\n", sa->sin_addr.s_addr, sa->sin_port);
        connfd = connect(sockfd, aa, sizeof(*aa));
        if (connfd == 0)
        {
            printf("connect successfully\n");
        }
        else
        {
            printf("connect failed, connfd = [%d], errno = [%d]\n", connfd, errno);
        }
    }

    freeaddrinfo(result);
}
```

### getnameinfo 函数

1. `getnameinfo()` converts the internal binary representation of an IP address in the form of a struct sockaddr pointer into text strings consisting of the hostname or, if the address cannot be resolved into a name, a textual IP address representation

```c
#include <sys/socket.h>
#include <netdb.h>

int getnameinfo(const struct sockaddr* sa, socklen_t salen,
                char* host, size_t hostlen,
                char* serv, size_t servlen,
                int flags);
```

```c
#include <netdb.h>
#include "stdio.h"
#include "../csapp.hpp"

int main()
{
    struct addrinfo *addrs;
    int             ret = getaddrinfo("127.0.0.1", "8080", NULL, &addrs);
    if (ret < 0)
    {
        unix_error("error get addr info\n");
        exit(0);
    }

    for (struct addrinfo *start = addrs;
         start != NULL;
         start = start->ai_next)
    {
        char host[20] = {};
        char port[20] = {};
        ret = getnameinfo(start->ai_addr, sizeof(*start), host, 20, port, 20, NI_NUMERICSERV);
        if (ret == 0)
        {
            printf("host = [%s], port = [%s]\n", host, port);
            break;
        }
    }
}
```

## 11.5 Web 服务器


