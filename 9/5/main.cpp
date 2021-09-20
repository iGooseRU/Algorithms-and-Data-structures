#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

enum class Colors
{
    WHITE,
    GRAY,
    BLACK
};

std::vector<std::vector<int> > graph;
std::vector<Colors> used;
std::stack<int> topological;

void TopSort(int top)
{
    used[top] = Colors::GRAY;

    for (int neighbour: graph[top])
        if (used[neighbour] == Colors::WHITE)
            TopSort(neighbour);

    used[top] = Colors::BLACK;
    topological.push(top);
}

std::string HamiltonianWaySearch(int v_count)
{
    std::vector<int> sorted;
    for (int i = 0; i < v_count; i++)
        if (used[i] != Colors::BLACK)
            TopSort(i);

    while (!topological.empty())
    {
        sorted.push_back(topological.top());
        topological.pop();
    }

    for (int i = 1; i < sorted.size(); i++)
    {
        if (std::find(graph[sorted[i - 1]].begin(),
                                  graph[sorted[i - 1]].end(),
                                                         sorted[i]) == graph[sorted[i - 1]].end())
            return "NO";
    }

    return "YES";
}

int main()
{
    freopen("hamiltonian.in", "r", stdin);
    freopen("hamiltonian.out", "w", stdout);

    int v_count, e_count;

    std::cin >> v_count >> e_count;

    graph.resize(v_count);
    used.resize(v_count);

    for (int i = 0; i < e_count; i++)
    {
        int begin, end;
        std::cin >> begin >> end;

        graph[begin - 1].push_back(end - 1);
    }

    std::cout << HamiltonianWaySearch(v_count);

    return 0;
}