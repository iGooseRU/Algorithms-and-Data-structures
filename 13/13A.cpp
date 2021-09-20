#include <iostream>
#include <vector>
#include <string>


std::vector<short> naiveStringMatcher (std::string const& text, std::string const& pattern)
{
    int n = text.length();
    int m = pattern.length();

    char buf[10000] = " ";

    std::vector<short> answer;

    for (int i = 0; i <= n - m; ++i)  // проходимся по количеству символов минус кол-во символов в паттерне
    {
        text.copy(buf, m, i);         // копируем подстроку длины m в буфер
        buf[m] = '\0';
        if (buf == pattern)           // если буфер совпал с паттерном то нашли подстроку
            answer.push_back(i + 1);  // кидаем позицию в вектор с ответами
    }

    return answer;
}

int main() {
    freopen("search1.in", "r", stdin);
    freopen("search1.out", "w", stdout);

    std::string text, pattern;

    std::cin >> pattern >> text;

    std::vector<short> matches = naiveStringMatcher(text, pattern); // выгружаем ответ

    std::cout << matches.size() << "\n";                            // вывод кол-ва совпадений

    for (auto const& sym: matches)                                  // вывод ответа
        std::cout << sym << " ";

    return 0;
}
