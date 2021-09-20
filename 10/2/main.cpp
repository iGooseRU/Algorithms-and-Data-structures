#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

class Graph{
protected:
    std::vector<int> x;
    std::vector<int> y;
    int v_count;

public:
    void addGraph(){
        std::cin >> v_count;

        x.resize(v_count);
        y.resize(v_count);

        for (int i = 0; i < v_count; i++) {
            std::cin >> x[i] >> y[i];
        }
    }

    void Prim(){
        addGraph();

        std::vector<bool> inMST(v_count);
        std::vector<int> dist(v_count, INT_MAX);
        double mst_dist = 0;

        dist[0] = 0;

        for (int i = 0; i < v_count; i++){
            int min_key = -1;

            for (int j = 0; j < v_count; j++)
                // �� � ��� ������ � ��� ����� �� ������� ��� ������ ������������
                if (!inMST[j] && (min_key == -1 || dist[j] < dist[min_key]))
                    min_key = j;

            inMST[min_key] = true;

            for (int j = 0; j < v_count; j++){
                int dx = x[j] - x[min_key]; // ������� ������ �������
                int dy = y[j] - y[min_key];
                int d = dx * dx + dy * dy;
                // ���� ������� � ������� ���� �� � ������ � dist < �������� �
                // ������ �� ��� �����, �� ������ ���������� �� �������
                if (!inMST[j] && d < dist[j] && min_key != j)
                    dist[j] = d;
            }
        }

        for (int u: dist){
            mst_dist += sqrt(u);
        }

        std::cout << std::setprecision(10) << mst_dist;
    }
};

int main()
{
    freopen("spantree.in", "r", stdin);
    freopen("spantree.out", "w", stdout);

    Graph graph;
    graph.Prim();

    return 0;
}