#include <iostream>
#include <vector>

enum class Statements
{
    NOT_VISITED,
    FIRST_PART,
    SECOND_PART
};

std::vector<std::vector<int> > graph;
std::vector<Statements> v_states;

Statements reverseStatement (Statements s)
{
    return s == Statements::FIRST_PART ? Statements::SECOND_PART : Statements::FIRST_PART;
}

void DFS (int v, Statements st)
{
    v_states[v] = st;

    for (int neighbour: graph[v])
    {
        if (v_states[neighbour] == Statements::NOT_VISITED)
             DFS(neighbour, reverseStatement(st));
        else if (v_states[neighbour] == st)
        {
            std::cout << "NO" << std::endl;
            exit(0);
        }
    }
}

int main()
{
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);

    int v_count, e_count;

    std::cin >> v_count >> e_count;

    v_states.resize(v_count + 1, Statements::NOT_VISITED);
    graph.resize(v_count + 1);

    for (int i = 0; i < e_count; i++)
    {
        int begin, end;
        std::cin >> begin >> end;
                                                /// тк неориент
        graph[begin - 1].push_back(end - 1);
        graph[end - 1].push_back(begin -1);
    }

    for (int i = 0; i < v_count; i++)
    {
        if (v_states[i] == Statements::NOT_VISITED)
            DFS(i, Statements::FIRST_PART);
    }

    std::cout << "YES";
    return 0;
}