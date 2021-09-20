#include <iostream>
#include <vector>
#include <queue>
#include <limits>

const int INF = std::numeric_limits<int>::max();

typedef std::pair<int, int> edge;

class CGraph
{
private:
    std::vector<std::vector<edge > > graph;
    std::vector<int> ans;
    int v_count, e_count;

public:
    void importGraph()
    {
        scanf("%d %d", &v_count, &e_count);

        graph.resize(v_count);
        ans.resize(v_count, INF);

        for (int i = 0; i < e_count; ++i)
        {
            int s, f, w;

            scanf("%d %d %d", &s, &f, &w);

            s--;
            f--;

            graph[s].push_back({w, f});
        }
    }

    void dijkstra()
    {
        for (int i = 0; i < v_count; ++i) {
            ans[i] = 0;

            std::priority_queue<edge, std::vector<edge>, std::greater<> > q;

            q.push({0, i});

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

            for (int &u: ans)
                printf("%d ", u);


            ans.assign(v_count, INF);
        }
    }
};

int main() {
    freopen("pathsg.in", "r", stdin);
    freopen("pathsg.out", "w", stdout);

    CGraph graph;
    graph.importGraph();
    graph.dijkstra();

    return 0;
}