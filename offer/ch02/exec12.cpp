//
// Created by 杜航宇 on 2019-09-20.
//
// 矩阵中的路径
// 设计一个函数，判断在一个矩阵中是否存在一条包含某字符串的所有字符的路径
// 路径可以从矩阵中的任意一格开始，每一步可以在矩阵中朝上下左右移动一格，如果经过了矩阵的某一格子，那么路径将不能再次进入该格子

#include "iostream"

// 思路是使用回溯法，我们首先在整个矩阵中遍历，直到找到某一个节点等于字符串的第一个字符
// 当我们找到第一个字符的时候，我们需要开始在上下左右开始进行搜索

// 最早我函数的声明如下，但是一直无法正常工作。因为在递归的过程中我们可能会修改 visited
// 而在回溯算法中，每次回溯都需要回退所有的状态
// bool doSearch(bool *visited, const char *matrix, const char *str, int rows, int cols, int curRow, int curCol)

void copy_array(const bool *src, bool *dest, int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            dest[i * cols + j] = src[i * cols + j];
        }
    }
}

bool doSearch(const bool *c_visited, const char *matrix, const char *str, int rows, int cols, int curRow, int curCol)
{
    if (*str == '\0')
    {
        return true;
    }

    // 超过界限
    if (curRow >= rows || curCol >= cols || curRow < 0 || curCol < 0)
    {
        return false;
    }

    int curIndex = curRow * cols + curCol;

    // 不相等
    if (matrix[curIndex] != *str || c_visited[curIndex])
    {
        return false;
    }

    bool visited[rows * cols];
    copy_array(c_visited, visited, rows, cols);
    visited[curIndex] = true;

    const int up   = curRow - 1, down = curRow + 1,
              left = curCol - 1, right = curCol + 1;

    bool upRet    = doSearch(visited, matrix, str + 1, rows, cols, up, curCol);
    bool downRet  = doSearch(visited, matrix, str + 1, rows, cols, down, curCol);
    bool leftRet  = doSearch(visited, matrix, str + 1, rows, cols, curRow, left);
    bool rightRet = doSearch(visited, matrix, str + 1, rows, cols, curRow, right);
    bool ret      = upRet || downRet || leftRet || rightRet;

    return ret;
}

bool hasPath(const char *matrix, int rows, int cols, const char *str)
{
    if (matrix == nullptr || str == nullptr || rows < 0 || cols < 0)
    {
        return false;
    }

    for (int curRow = 0; curRow < rows; ++curRow)
    {
        for (int curCol = 0; curCol < cols; ++curCol)
        {
            int curIndex = curRow * cols + curCol;
            if (matrix[curIndex] != *str)
            {
                continue;
            }

            // 这里只是做了
            bool visited[cols * rows];

            for (int i   = 0; i < cols * rows; ++i)
            {
                visited[i] = false;
            }
            bool     ret = doSearch(visited, matrix, str, rows, cols, curRow, curCol);
            if (ret)
            {
                return ret;
            }
        }
    }

    return false;
}

// ====================测试代码====================
void Test(const char *testName, const char *matrix, int rows, int cols, const char *str, bool expected)
{
    if (testName != nullptr)
        printf("%s begins: ", testName);

    if (hasPath(matrix, rows, cols, str) == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

//ABTG
//CFCS
//JDEH

//BFCE
void Test1()
{
    const char *matrix = "ABTGCFCSJDEH";
    const char *str    = "BFCE";

    Test("Test1", (const char *) matrix, 3, 4, str, true);
}

//ABCE
//SFCS
//ADEE

//SEE
void Test2()
{
    const char *matrix = "ABCESFCSADEE";
    const char *str    = "SEE";

    Test("Test2", (const char *) matrix, 3, 4, str, true);
}

//ABTG
//CFCS
//JDEH

//ABFB
void Test3()
{
    const char *matrix = "ABTGCFCSJDEH";
    const char *str    = "ABFB";

    Test("Test3", (const char *) matrix, 3, 4, str, false);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SLHECCEIDEJFGGFIE
void Test4()
{
    const char *matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
    const char *str    = "SLHECCEIDEJFGGFIE";

    Test("Test4", (const char *) matrix, 5, 8, str, true);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SGGFIECVAASABCEHJIGQEM
void Test5()
{
    const char *matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
    const char *str    = "SGGFIECVAASABCEHJIGQEM";

    Test("Test5", (const char *) matrix, 5, 8, str, true);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SGGFIECVAASABCEEJIGOEM
void Test6()
{
    const char *matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
    const char *str    = "SGGFIECVAASABCEEJIGOEM";

    Test("Test6", (const char *) matrix, 5, 8, str, false);
}

//ABCEHJIG
//SFCSLOPQ
//ADEEMNOE
//ADIDEJFM
//VCEIFGGS

//SGGFIECVAASABCEHJIGQEMS
void Test7()
{
    const char *matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS";
    const char *str    = "SGGFIECVAASABCEHJIGQEMS";

    Test("Test7", (const char *) matrix, 5, 8, str, false);
}

//AAAA
//AAAA
//AAAA

//AAAAAAAAAAAA
void Test8()
{
    const char *matrix = "AAAAAAAAAAAA";
    const char *str    = "AAAAAAAAAAAA";

    Test("Test8", (const char *) matrix, 3, 4, str, true);
}

//AAAA
//AAAA
//AAAA

//AAAAAAAAAAAAA
void Test9()
{
    const char *matrix = "AAAAAAAAAAAA";
    const char *str    = "AAAAAAAAAAAAA";

    Test("Test9", (const char *) matrix, 3, 4, str, false);
}

//A

//A
void Test10()
{
    const char *matrix = "A";
    const char *str    = "A";

    Test("Test10", (const char *) matrix, 1, 1, str, true);
}

//A

//B
void Test11()
{
    const char *matrix = "A";
    const char *str    = "B";

    Test("Test11", (const char *) matrix, 1, 1, str, false);
}

void Test12()
{
    Test("Test12", nullptr, 0, 0, nullptr, false);
}

int main(int argc, char *argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    Test8();
    Test9();
    Test10();
    Test11();
    Test12();

    return 0;
}