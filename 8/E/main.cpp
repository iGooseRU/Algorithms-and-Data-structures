#include <iostream>
#include <queue>
#include <vector>

std::vector <int> graph[100000];         /// список смежности
int dist[100000] = {0};                  /// расстояние до вершин
bool used_tops[100000];

void AddGraph (int edges_count) {
    for (int i = 0; i < edges_count; i++)
    {
        int begin, end;
           std::cin >> begin >> end;
           begin--;
           end--;
           graph[begin].push_back(end);
           graph[end].push_back(begin);
    }
}

void BFS ()
{
    std::queue<int> queue;
    queue.push(0);                            /// начинаем с 1 вершины
    used_tops[0] = true;

    while (!queue.empty())                       /// пока очередь не пуста
    {
        int cur = queue.front();                 /// берем текущий элемент очереди и удаляем его
        queue.pop();

        for (int neighbour: graph[cur])
        {
            if (!used_tops[neighbour])           /// если сосед еще не проходился
            {
                queue.push(neighbour);           /// добавляем в очередь
                used_tops[neighbour] = true;     /// помечаем его как пройденную вершину
                dist[neighbour] = dist[cur] + 1; /// даем ему расстояние
            }
        }
    }
}

int main()
{
    freopen("pathbge1.in", "r", stdin);
    freopen("pathbge1.out", "w", stdout);

    int top_count, edge_count;

    std::cin >> top_count >> edge_count;

    AddGraph(edge_count);

    BFS();

    for (int i = 0; i < top_count; i++) {
        std::cout << dist[i] << " ";
    }

    return 0;
}