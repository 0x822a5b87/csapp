//
// Created by 杜航宇 on 2019-09-19.
// 用两个栈实现一个队列
//

#include "iostream"
#include "stack"

namespace offer
{
    // 在我们的队列中我们定义了两个 stack，分别为 filo, fifo。其中 filo 存放的是逆序数据，而 fifo 中存放的是顺序数据
    //
    // 1. 当我们调用 appendTail 来压入数据时，我们将数据压入 filo
    // 2. 当调用 deleteHead 时，
    //      2.1 如果 fifo 不为空，那么我们直接将 fifo 的第一个元素弹出
    //      2.2 如果 fifo 为空，那么我们将所有 filo 中的所有元素弹出并写入到 fifo 中。随后跳转到 <1>
    template <typename T>
    class CQueue
    {
    public:
        CQueue();

        ~CQueue();

        void appendTail(const T &node);

        T deleteHead();

    private:
        std::stack<T> filo;
        std::stack<T> fifo;

        T takeFirst();

        void takeFromFilo();
    };

    template<typename T>
    CQueue<T>::CQueue()
        :filo(), fifo()
    {

    }

    template<typename T>
    CQueue<T>::~CQueue() = default;

    template<typename T>
    void CQueue<T>::appendTail(const T &node)
    {
        filo.push(node);
    }

    template<typename T>
    T CQueue<T>::deleteHead()
    {
        if (!fifo.empty())
        {
            return takeFirst();
        }
        else
        {
            takeFromFilo();
        }

        return takeFirst();
    }

    template<typename T>
    T CQueue<T>::takeFirst()
    {
        T node = fifo.top();
        fifo.pop();
        return node;
    }

    template<typename T>
    void CQueue<T>::takeFromFilo()
    {
        while (!filo.empty())
        {
            T node = filo.top();
            filo.pop();
            fifo.push(node);
        }
    }

    class User
    {
    public:
        User()
        {
            std::cout << "user constructor is running!" << std::endl;
        }

        User(const User &user)
        {
            std::cout << "user copy constructor is running!" << std::endl;
        }

        virtual ~User()
        {
            std::cout << "user destructor is running!" << std::endl;
        }
    };
}

void Test(char actual, char expected)
{
    if(actual == expected)
        printf("Test passed.\n");
    else
        printf("Test failed.\n");
}

void TestMemory()
{
    offer::CQueue<offer::User> queue;
    for (int i = 0; i < 10; ++i)
    {
        offer::User user;
        queue.appendTail(user);
    }

    for (int i = 0; i < 10; ++i)
    {
        queue.deleteHead();
    }
}

int main(int argc, char* argv[])
{
    offer::CQueue<char> queue;

    queue.appendTail('a');
    queue.appendTail('b');
    queue.appendTail('c');

    char head = queue.deleteHead();
    Test(head, 'a');

    head = queue.deleteHead();
    Test(head, 'b');

    queue.appendTail('d');
    head = queue.deleteHead();
    Test(head, 'c');

    queue.appendTail('e');
    head = queue.deleteHead();
    Test(head, 'd');

    head = queue.deleteHead();
    Test(head, 'e');

    TestMemory();

    return 0;
}
