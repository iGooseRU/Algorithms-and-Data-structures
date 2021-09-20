#include <fstream>
#include <vector>

std::vector<std::vector<int>> g;
std::vector<bool> used;
std::vector<int> ans;

/// WHITE - 1 // GRAY - 2 // BLACK - 3 //

void topSort(int top)                               /// топологическая сортировка
{
    used[top] = true;
    for (int i: g[top])
        if (!used[i])
            topSort(i);
    ans.push_back(top);
}

std::vector<int> color;
std::vector<int> cycle;

bool check(int top, int start, int finish)          /// проверка на циклы
{
    color[top] = 2;                                 /// помечаем вершину серой
    int temp;
    for (auto i: g[top])                            /// проходимся по всем связным вершинам
    {
        temp = i;
        if (color[temp] == 1)                       /// если пришли в белую верщину
        {
            cycle[temp] = top;
            if (check(temp, start, finish))         /// проверяем текущию вершину
                return true;
        }
        else if (color[temp] == 2)                  /// если пришли в серую вершину
        {
            start = temp;
            finish = top;
            return true;
        }
    }
    color[top] = 3;                                 /// после прохода по вершине меняем цвет на чёрный
    return false;
}

int main()
{
    std::ifstream fin("topsort.in");
    std::ofstream fout("topsort.out");
    int n, m, v1, v2, start = -1, finish = -1;
    fin >> n >> m;
    g.resize(n);                                    /// заполняем вектора изначальными значениями
    used.assign(n, false);
    color.assign(n, 1);
    cycle.assign(n, -1);
    for (int i = 0; i < m; i++)                     /// считываем данные о вершинах
    {                                               /// и строим список смежности
        fin >> v1 >> v2;
        v1--;
        v2--;
        g[v1].push_back(v2);
    }
    for (int i = 0; i < n; i++)                      /// осуществляем проверку
    {
        if (check(i, start, finish))                 /// если какая то вершина не прошла проверку
        {                                            /// то граф является цикличным
            fout << -1;
            return 0;
        }
    }
    for (int i = 0; i < n; i++)                         /// запускаем для каждой точки топологическую сортировку
        if (!used[i])
            topSort(i);

    std::vector<int>ansReverse(n);                      /// инвертируем вектор

    for (int i = 0; i < n; i++)
        ansReverse[i] = ans[n - 1 - i];
    for (auto i : ansReverse)                           /// выводим результат
        fout << i + 1 << " ";
    return 0;
}