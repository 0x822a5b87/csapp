#include "iostream"

const char *ReverseLetter = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";

const char *Output[] =
                   {
                           "-- is not a palindrome.",
                           "-- is a regular palindrome",
                           "-- is a mirrored string",
                           "-- is a mirrored palindrome"
                   };

constexpr size_t NotPalindrome      = 0;
constexpr size_t RegularPalindrome  = 1;
constexpr size_t MirroredString     = 2;
constexpr size_t MirroredPalindrome = 3;

char rev(char ch)
{
    if (isalpha(ch))
        return ReverseLetter[ch - 'A'];
    else
        return ReverseLetter[ch - '0' + 25];
}

size_t find_word_type(const char *word)
{
    if (word == nullptr)
        return NotPalindrome;

    size_t len = strlen(word);
    const char *start = word;
    const char *end = word + len - 1;

    bool isPalindrome = true, isMirrored = true;
    while (start < end)
    {
        if (isPalindrome)
        {
            if (*start != *end)
                isPalindrome = false;
        }

        if (isMirrored)
        {
            if (*start != rev(*end))
                isMirrored = false;
        }

        start++;
        end--;
    }

    if (isPalindrome && isMirrored)
        return MirroredPalindrome;
    else if (isPalindrome)
        return RegularPalindrome;
    else if (isMirrored)
        return MirroredString;
    else
        return NotPalindrome;
}

int main(int argc, char **argv)
{
    char line[1024];
    while (std::cin.getline(line, 1024))
    {
        std::cout << line << " " << Output[find_word_type(line)] << std::endl;
    }
}