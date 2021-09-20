#include <iostream>
#include <vector>

enum class Colors
{
    WHITE,
    BLACK
};

enum class Players
{
    SECOND,
    FIRST
};

std::vector<std::vector<int> > graph;
std::vector<Colors> used;
std::vector<Players> position;

void DFS(int top)
{
    used[top] = Colors::BLACK;
    for (int neighbour: graph[top])
    {
        if (used[neighbour] == Colors::WHITE)
            DFS(neighbour);
        if (position[neighbour] == Players::SECOND)   /// если след вершина проигр, то эта выигрышная
            position[top] = Players::FIRST;
    }
}

std::string Game(int start)
{
    for (int i = 0; i < graph.size(); i++)
    {
        if (used[i] != Colors::BLACK)
        {
            DFS(start - 1);
        }
    }

    if (position[start - 1] == Players::FIRST)
        return "First player wins";
    else
        return "Second player wins";
}

int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);

    int v_count, e_count, start;

    std::cin >> v_count >> e_count >> start;

    graph.resize(v_count + 1);
    used.resize(v_count + 1);
    position.resize(v_count + 1);

    for (int i = 0; i < e_count; i++)
    {
        int begin, end;
        std::cin >> begin >> end;

        graph[begin - 1].push_back(end - 1);
    }

    std::cout << Game(start);

    return 0;
}