#include <iostream>
#include <vector>
#include <queue>
#include <limits>

typedef std::pair<long long, int> edge;

const long long INF = std::numeric_limits<long long>::max();

class CGraph
{
private:
    std::vector<std::vector<edge > > graph;
    std::vector<long long> ans;
    int n, s, f;
public:
    void importGraph()
    {
        scanf("%d %d %d", &n, &s, &f);

        s--;
        f--;

        ans.resize(n, INF);
        graph.resize(n);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                int weight = 0;
                scanf("%d", &weight);

                if (i == j || weight == -1)
                    continue;

                graph[i].push_back({weight, j});
            }
        }
    }

    long long dijkstra()
    {
        ans[s] = 0;

        std::priority_queue<edge, std::vector<edge>, std::greater<> > q;

        q.push({0, s});

        while (!q.empty())
        {
            edge v = q.top();
            q.pop();

            long long dst = v.first;
            int v_num = v.second;

            if (ans[v_num] < dst)
                continue;

            for (edge &u: graph[v_num])
            {
                int u_dst = u.first, u_num = u.second;

                long long n_dst = dst + u_dst;
                if (n_dst < ans[u_num])
                {
                    ans[u_num] = n_dst;
                    q.push({n_dst, u_num});
                }
            }
        }

        return ans[f] == INF ? -1 : ans[f];
    }
};

int main() {
    freopen("pathmgep.in", "r", stdin);
    freopen("pathmgep.out", "w", stdout);

    CGraph graph;
    graph.importGraph();

    printf("%lld", graph.dijkstra());

    return 0;
}