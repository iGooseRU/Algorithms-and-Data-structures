#include <iostream>
#include <vector>
#include <algorithm>

struct Edge
{
    int u, v, w;
};

const long long INF = std::numeric_limits<long long>::max() / 2;

class CGraph
{
private:
    std::vector<Edge > edges;
    int vertex_c;
public:
    void importGraph()
    {
        std::cin >> vertex_c;

        for (int i = 0; i < vertex_c; ++i)
        {
            for (int j = 0; j < vertex_c; ++j)
            {
                int w;
                std::cin >> w;
                if (w != static_cast<int>(1e9))
                {
                    edges.push_back({i, j, w});
                }
            }
        }
    }

    void cycleByBellmanFord()
    {

        std::vector<long long> dist(vertex_c, INF);
        std::vector<int> prev(vertex_c, -1);
        int x;

        dist[0] = 0;

        // обновление пути
        for (int i = 0; i < vertex_c; ++i)
        {
            x = -1;
            for (auto &e: edges)
            {
                int u = e.u, v = e.v, w = e.w;

                if (dist[u] + w < dist[v])
                {
                    dist[v] = std::max(dist[u] + w, -INF);
                    prev[v] = u;
                    x = v;
                }
            }
        }

        /* У нас есть флаг X, если нет вершин который лежат в цикле отрицательного веса,
         * он также останется -1. Если есть - флаг заменится на номер вершины,
         * которая и лежит на этом цикле */

        if (x == -1) std::cout << "NO" << std::endl;
        else
        {
            int y = x;
            std::vector<int> cycle;

            for (int i = 0; i < vertex_c; ++i)
                y = prev[y];

            for(int cur = y;; cur = prev[cur])
            {
                cycle.push_back(cur);
                if(cur == y && cycle.size() > 1)
                    break;
            }

            std::reverse(cycle.begin(), cycle.end());

            std::cout << "YES" << "\n" << cycle.size() << "\n";
            for (int i = 0; i < cycle.size(); ++i)
            {
                std::cout << cycle[i] + 1;
                if(i != cycle.size()-1)
                {
                    std::cout << ' ';
                }
            }
            std::cout << "\n";
        }
    }
};

int main()
{
    freopen("negcycle.in", "r", stdin);
    freopen("negcycle.out", "w", stdout);

    CGraph graph;
    graph.importGraph();
    graph.cycleByBellmanFord();

    return 0;
}