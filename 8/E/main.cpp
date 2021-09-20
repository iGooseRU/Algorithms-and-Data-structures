#include <iostream>
#include <queue>
#include <vector>

std::vector <int> graph[100000];         /// ������ ���������
int dist[100000] = {0};                  /// ���������� �� ������
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
    queue.push(0);                            /// �������� � 1 �������
    used_tops[0] = true;

    while (!queue.empty())                       /// ���� ������� �� �����
    {
        int cur = queue.front();                 /// ����� ������� ������� ������� � ������� ���
        queue.pop();

        for (int neighbour: graph[cur])
        {
            if (!used_tops[neighbour])           /// ���� ����� ��� �� ����������
            {
                queue.push(neighbour);           /// ��������� � �������
                used_tops[neighbour] = true;     /// �������� ��� ��� ���������� �������
                dist[neighbour] = dist[cur] + 1; /// ���� ��� ����������
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