#include <iostream>
#include <vector>
#include <queue>
#include <limits>

const long long INF = std::numeric_limits<long long>::max();

typedef std::pair<long long, int> edge;

class CGraph
{
private:
    std::vector<std::vector<edge > > graph;
    std::vector<long long> ans;
    int vertex_c, edges_c;

public:
    void importGraph()
    {
        scanf("%d %d", &vertex_c, &edges_c);

        graph.resize(vertex_c);
        ans.resize(vertex_c, INF);

        for (int i = 0; i < edges_c; ++i)
        {
            int s, f, w;

            scanf("%d %d %d", &s, &f, &w);
            s--;
            f--;

            graph[s].push_back({w, f});
            graph[f].push_back({w, s});
        }
    }

    void dijkstra()
    {
        ans[0] = 0;

        std::priority_queue<edge, std::vector<edge>, std::greater<> > q;

        q.push({0, 0});

        while (!q.empty()) {
            edge v = q.top();
            q.pop();

            int dst = v.first, v_num = v.second;

            if (ans[v_num] < dst)
                continue;

            for (edge &u: graph[v_num]) {
                int u_dst = u.first, u_num = u.second;

                int n_dst = dst + u_dst;

                if (n_dst < ans[u_num]) {
                    ans[u_num] = n_dst;
                    q.push({n_dst, u_num});
                }
            }
        }

        for (long long &u: ans)
            printf("%lld ", u);
        printf("\n");
    }
};

int main() {
    freopen("pathbgep.in", "r", stdin);
    freopen("pathbgep.out", "w", stdout);

    CGraph graph;
    graph.importGraph();
    graph.dijkstra();

    return 0;
}