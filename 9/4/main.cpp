#include <iostream>
#include <vector>
#include <stack>

std::vector<std::vector<int> > graph;
std::stack<int>top_sort;
std::vector<int> sorted;
std::vector<int> c_numbers;

enum class DFSColors
{
    WHITE,
    GRAY,
    BLACK
};

std::vector<DFSColors> used;


void TopSort(int top)
{
    used[top] = DFSColors::GRAY;
    for (int neighbour: graph[top])
    {
        if (used[neighbour] == DFSColors::WHITE)
            TopSort(neighbour);
    }
    used[top] = DFSColors::BLACK;
    top_sort.push(top);
}

void Transposition(int top_count)
{
    std::vector<std::vector<int> > T;
    T.resize(top_count);
    for (int v = 0; v < top_count; v++)
    {
        for (int neighbour: graph[v])
        {
            T[neighbour].push_back(v);
        }
    }
    graph.clear();
    graph = T;
}

void DFS(int top, int c_number)
{
    c_numbers[top] = c_number;
    for (int neighbour: graph[top])
        if (c_numbers[neighbour] == 0)
            DFS(neighbour, c_number);
}

int Condensation(int vertex_count)
{
    for (int i = 0; i < vertex_count; i++)
    {
        if (used[i] != DFSColors::BLACK)
            TopSort(i);
    }
    for (int i = 0; i < vertex_count; i++)
    {
        sorted[i] = top_sort.top();
        top_sort.pop();
    }
    Transposition(vertex_count);
    int c_count = 1;
    for (int i = 0; i < vertex_count; i++)
    {
        if (c_numbers[sorted[i]] == 0)
        {
            DFS(sorted[i], c_count);
            c_count++;
        }
    }

    return c_count - 1;
}

int main()
{
    freopen("cond.in", "r", stdin);
    freopen("cond.out", "w", stdout);

    int top_count, edge_count;

    std::cin >> top_count >> edge_count;

    graph.resize(top_count);
    used.resize(top_count);
    sorted.resize(top_count);
    c_numbers.resize(top_count, 0);

    for (int i = 0; i < edge_count; i++)
    {
        int begin, end;
        std::cin >> begin >> end;
        begin--;
        end--;

        graph[begin].push_back(end);
    }

    std::cout << Condensation(top_count) << std::endl;

    for (int u: c_numbers)
        std::cout << u << " ";

    return 0;
}