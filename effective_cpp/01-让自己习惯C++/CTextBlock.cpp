#include "iostream"

class CTextBlock
{
public:
    std::size_t length() const;

private:
    char *pText;
    std::size_t textLength;
    bool lengthIsValid;
};

std::size_t CTextBlock::length() const
{
    if (!lengthIsValid)
    {
        textLength = std::strlen(pText);
        lengthIsValid = true;
        // 这段代码无法通过编译，因为C++的编译器是 bitwise constness 的
    }

    return textLength;
}
