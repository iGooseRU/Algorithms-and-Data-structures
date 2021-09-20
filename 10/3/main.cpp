#include <iostream>
#include <vector>
#include <algorithm>

struct Edge
{
    int u, v, w;
};


bool comparator(const Edge &left, const Edge &right) {
    return left.w < right.w;
}

class Graph
{
private:
    std::vector<int> p; // массив корней
    std::vector<Edge> edges;
    int v_count = 0;
    int e_count = 0;
public:
    void importGraph()
    {
        std::cin >> v_count >> e_count;
        p.assign(v_count, -1);

        for (int i = 0; i < e_count; i++)
        {
            int u, v, w;
            std::cin >> u >> v >> w;

            edges.push_back(Edge{u, v, w});
        }
    }

    // получаем корень дерева
    int getRoot(int v) {
        if (p[v] < 0) return v;
        else {
            int root = getRoot(p[v]);
            p[v] = root;
            return root;
        }
    }

    // объединение
    bool unite(int u, int v){
        u = getRoot(u),
        v = getRoot(v);

        // если корни равны
        if (u == v)
            return false;

        // переподвешиваем к можеству большой глубины множество меньшей глубины
        if (p[u] < p[v])
        {
            p[u] += p[v];
            p[v] = u;
        }
        else
        {
            p[v] += p[u];
            p[u] = v;
        }

        return true;
    }

    void KruskalAlgorithm()
    {
        importGraph();
        std::sort(edges.begin(), edges.end(), comparator);
        long long mst_count = 0;

        // если объеденение успешно добавляем ребро в мин остов
        for (const Edge &e: edges)
            if (unite(e.u, e.v)) mst_count += e.w;

        std::cout << mst_count;
    }

};

int main()
{
    freopen("spantree3.in", "r", stdin);
    freopen("spantree3.out", "w", stdout);

    Graph graph;
    graph.KruskalAlgorithm();

    return 0;
}