#include <iostream>
#include <vector>

int main()
{
    int count;

    std::cin >> count;

    if (count == 1)
    {
        std::cout << 0;
        exit(0);
    }
    else
    {
        const int module = 1e9;
        std::vector<int> colors(count);
        std::vector<std::vector<int> > dp(count, std::vector<int> (count, 0));

        for (int i = 0; i < count; ++i)
        {
            std::cin >> colors[i];
            dp[i][i] = 1;
        }

        for (int i = 1; i < count; ++i)
        {
            for (int j = 0; i + j < count; ++j)
            {
                if (colors[j] == colors[j + i])
                    dp[j][j + i] = (dp[j + 1][j + i] % module + dp[j][j + i - 1] % module + 1) % module;
                else
                    dp[j][j + i] = (dp[j + 1][j + i] % module + dp[j][j + i - 1] % module - dp[j + 1][j + i - 1] % module) % module;
            }
        }

        std::cout << (dp[0][count - 1] + module) % module;
    }

    return 0;
}