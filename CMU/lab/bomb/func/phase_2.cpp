//
// Created by 杜航宇 on 2019-08-16.
//

#include "iostream"

void phase_2()
{
    int day = 16, year = 2019, hour = 16;
    char weekday[20], month[20], dtm[100];

    strcpy( dtm, "Saturday March 25 1989 10");
    std::cout << dtm << std::endl;
    std::cout << std::endl;
    int ret = sscanf(dtm, "%s %s %d  %d %d", weekday, month, &day, &year, &hour);

    printf("%s %d, %d = %s\n", month, day, year, weekday );
    std::cout << ret << std::endl;
    std::cout << dtm << std::endl;
}

void bigger_than(int y)
{
    int x = 0;
    if (x > y)
    {

    }
}

void read_six_numbers(const char *s, const char * pattern, int *first, int *second)
{
    sscanf(s, pattern, first, second);
}

int main()
{
    phase_2();
}
