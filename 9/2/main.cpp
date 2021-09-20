#include <iostream>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<int> colors;
std::vector<int> traversal;

bool flag;
int v_count, e_count;

enum Colors
{
    WHITE,
    GRAY,
    BLACK
};

void DFS (int v) {
    if (flag) return;
    else
    {
        colors[v] = GRAY;
        traversal.push_back(v);
        for (int neighbour: graph[v])
        {
            if (colors[neighbour] == GRAY)
            {
                traversal.push_back(neighbour);
                flag = true;
                return;
            }
            else if (colors[neighbour] == WHITE)
            {
                DFS(neighbour);
            }
            if (flag) return;
        }
        colors[v] = BLACK;
        traversal.pop_back();
    }
}

void cycleSearch()
{
    for (int i = 1; i <= v_count; i++)
    {
        if (colors[i] == WHITE)
        {
            DFS(i);
            if (flag) return;
        }
    }
}

int main()
{
    freopen("cycle.in", "r", stdin);
    freopen("cycle.out", "w", stdout);

    std::cin >> v_count >> e_count;

    graph.resize(v_count + 1);
    colors.resize(v_count + 1, 0);

    for (int i = 1; i <= e_count; i++)               /// «аполн€ем список смежности
    {
        int begin, end;
        std::cin >> begin >> end;

        graph[begin].push_back(end);
    }

    cycleSearch();

    if (flag)
    {
        std::cout << "YES" << std::endl;
        int i = static_cast<int>(traversal.size()) - 2;
        int cycled = traversal.back();

        while (traversal[i] != cycled)          /// ѕока не встретили цикл вершину возвращаемс€ нахад
            i--;
        while (i < traversal.size() - 1)
        {
            std::cout << traversal[i] << " ";
            i++;
        }
    } else
        std::cout << "NO";

    return 0;
}