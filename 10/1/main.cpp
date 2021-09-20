#include <iostream>
#include <vector>

class Graph
{
protected:
    std::vector<int> count;
    int v_count, e_count;

public:
    Graph()
    : v_count(0)
    , e_count(0) {}

    ~Graph()= default;

    void addGraph(){
        std::cin >> v_count >> e_count;

        count.assign(v_count, 0);

        for (int i = 0; i < e_count; i++){
            int first, last;
            std::cin >> first >> last;

            count[first - 1] += 1;
            count[last - 1] += 1;
        }
    }

    void PrintDegree(){
        for (auto u: count)
            std::cout << u << " ";
        std::cout << std::endl;
    }
};

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    Graph graph;

    graph.addGraph();
    graph.PrintDegree();

    return 0;
}