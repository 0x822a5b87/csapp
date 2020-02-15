// 输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。
// 为简单起见，标点符号和普通字母一样处理。例如输入字符串"I am a student. "，则输出"student. a am I"。
#include <iostream>
#include "vector"

void ReverseWord(std::string &word, size_t head, size_t tail)
{
    while (head < tail && tail < word.size())
    {
        std::swap(word[head++], word[tail--]);
    }
}

std::string ReverseSentence(std::string sentence)
{
    if (sentence.empty())
    {
        return sentence;
    }
    ReverseWord(sentence, 0, sentence.size() - 1);
    size_t head = 0, tail = 0;
    for (; tail < sentence.size(); ++tail)
    {
        if (sentence[tail] != ' ')
        {
            continue;
        }
        ReverseWord(sentence, head, tail - 1);
        head = tail + 1;
    }

    std::cout << sentence << std::endl;
    ReverseWord(sentence, head, tail - 1);
    return sentence;
}

int main(int argc, char **argv)
{
    std::string       sentence("Hello World!! This is SENTENCE");
    const std::string &ret = ReverseSentence(sentence);
    std::cout << ret << std::endl;

    sentence = "Hello";
    std::cout << ReverseSentence(sentence) << std::endl;

    sentence = "";
    std::cout << ReverseSentence(sentence) << std::endl;

    sentence = "Hello ";
    std::cout << ReverseSentence(sentence) << std::endl;
}
