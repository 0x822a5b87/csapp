// 3-2 UVa 1586
#include "iostream"
#include "iomanip"

inline double calculate(double mass, std::string::iterator &it)
{
    if (!std::isdigit(*it))
    {
        return mass;
    }

    unsigned int molecular_cnt = 0;
    while (std::isdigit(*it))
    {
        molecular_cnt = 10 * molecular_cnt + (*it++ - '0');
    }
    return mass * molecular_cnt;
}

int main(int argc, char **argv)
{
    int cnt;
    std::cin >> cnt;
    std::string formula;
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(3);
    for (size_t i = 0; i < cnt; ++i)
    {
        std::cin >> formula;
        double    molar_mass = 0;
        for (auto molecular  = formula.begin(); molecular != formula.end();)
        {
            char &element = *molecular;
            if (element == 'C')
            {
                ++molecular;
                molar_mass += calculate(12.01, molecular);
            }
            else if (element == 'H')
            {
                ++molecular;
                molar_mass += calculate(1.008, molecular);
            }
            else if (element == 'O')
            {
                ++molecular;
                molar_mass += calculate(16.00, molecular);
            }
            else if (element == 'N')
            {
                ++molecular;
                molar_mass += calculate(14.01, molecular);
            }
        }
        std::cout << molar_mass << std::endl;
        // C
        // C6H5OH
        // NH2CH2COOH
        // C12H22O11

        // 12.010
        // 94.108
        // 75.070
        // 342.296
    }
}