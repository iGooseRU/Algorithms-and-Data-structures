#include <iostream>
#include <vector>
#include <limits>

const long long INF = std::numeric_limits<long long>::max();

struct Edge
{
    int to;
    long long dst;
};

class CGraph
{
private:
    std::vector<std::vector<Edge> > edgeList;
    std::vector<bool> used;
    int vertex_c, edges_c, start;

public:
    void importGraph()
    {
        scanf("%d %d %d", &vertex_c, &edges_c, &start);
        start--;

        edgeList.resize(vertex_c);
        used.resize(vertex_c);

        for (int i = 0; i < edges_c; ++i)
        {
            int from, to;
            long long dst;

            scanf("%d %d %lld", &from, &to, &dst);

            from--;
            to--;

            edgeList[from].push_back({to, dst});
        }
    }

    void dfs(int v)
    {
        used[v] = true;
        for (auto &e: edgeList[v])
        {
            int to = e.to;
            if (!used[to]) dfs(to);
        }
    }

    void bellmanFord()
    {
        std::vector<long long> dist(vertex_c, INF);

        dist[start] = 0;

        /* здесь происходит подсчет нового ребра до вершины to
         * если путь до from + текущее ребро в to дешевле, чем
         * имеющийся путь в to - меняем */

        for (int i = 0; i < vertex_c - 1; ++i)
        {
            for (int u = 0; u < vertex_c; ++u)
            {
                for (auto &e: edgeList[u]) // проход по соседям
                {
                    int to = e.to;
                    long long dst = e.dst;

                    if ((dist[u] + dst < dist[to]) && (dist[u] < INF))
                        dist[to] = std::max(-INF, dist[u] + dst);
                }
            }
        }

        /* в случае, если мы попытались сверх прохода по всем вершинам еще что-то уменьшить
         * то мы попали на вершину, находящуюся в цикле отрицательного веса,
         * следовательно, до нее нет кратчайшего пути и нужно найти такие же (которые
         * лежат на цикле отрицательного веса) с помощь поиска в глубину
         * когда нашли - помечаем их булевыми метками в used*/

        for (int u = 0; u < vertex_c; ++u)
        {
            for (auto &e: edgeList[u])
            {
                int to = e.to;
                long long dst = e.dst;

                if ((dist[u] + dst < dist[to]) && (dist[u] < INF) && (!used[to]))
                    dfs(to);
            }
        }


        /* нет пути (расстояние осталось бесконечным) - *, если вершина на цикле (used[i] = true
         * или же расстояние до этой вершины у нас уменьшилось очень намного ( меньше
         * чем (-long long / 2) - печатаем -, если все ок - печатаем кратчайший путь*/

        for (int i = 0; i < vertex_c; ++i)
        {
            if (dist[i] == INF)
                printf("*\n");
            else if (used[i] || dist[i] < -5e18)
                printf("-\n");
            else
                printf("%lld\n", dist[i]);
        }
    }
};

int main()
{
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);

    CGraph graph;
    graph.importGraph();
    graph.bellmanFord();

    return 0;
}