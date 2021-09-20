#include <iostream>
#include <vector>
#include <algorithm>

// Алгоритм Кнута Морриса-Прата

/* Префикс-функция от строки s равна массиву π,
где π[i] обозначает длину максимального префикса строки s[0..i],
совпадающего с её суффиксом. */

void prefix_function(std::string const& string){
    int n = string.length();
    std::vector<int> pi(n);

    // след значение префикс функции <= пред. -1

    // пробегаемся по всему тексту
    for (int i = 1; i < n; ++i){
        int j = pi[i - 1];                          // используем пред. длину префикса для вычисления след.

        while (j > 0 && string[i] != string[j])     // пока не можем продолжить текущий префикс
            j = pi[j - 1];                          // уменьшаем длину до след возможной

            // теперь у нас j max длина префикса который мы можем позволить
            // либо 0 если такого не существует

        if (string[i] == string[j])
            ++j;

        pi[i] = j;  // только если j = 0
    }

    for (auto const& res: pi){
        std::cout << res << " ";
    }
}

int main()
{
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);

    std::string text;

    std::cin >> text;

    prefix_function(text);

    return 0;
}