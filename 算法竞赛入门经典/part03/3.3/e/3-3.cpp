#include "iostream"

int main(int argc, char **argv)
{
    int n, k;
    std::cin >> n >> k;
    if (n <= 0 || k <= 0)
        exit(0);

    bool lights[n];
    memset(lights, 0, sizeof(lights));

    for (int i = 0; i < k; ++i)
    {
        int interval = i + 1;
        for (int j = interval - 1; j < n; j += interval)
        {
            lights[j] = !lights[j];
        }
    }

    for (int i = 0; i < n; ++i)
    {
        if (lights[i])
        {
            printf("%d ", (i + 1));
        }
    }
    printf("\n");

    exit(0);
}