#include <iostream>
#include <vector>

std::vector<int> graph[100000];   /// массив для хранения списка смежности
bool used_tops[100000];           /// для проверки на пройденность i-й вершины
int component_nums[100000];       /// номер компоненты для i-й вершины

void AddGraph(int top_count, int edge_count)    /// Заполняем список смежности
{
    for (int i = 0; i < edge_count; i++)
    {
        int begin, end;
        std::cin >> begin >> end;
        begin--;
        end--;

        graph[begin].push_back(end);
        graph[end].push_back(begin);
    }
}


void DFS(int top, int component_num)        /// DFS
{
    used_tops[top] = true;
    component_nums[top] = component_num;

    for (int neighbour: graph[top])
    {
        if (!used_tops[neighbour])
        {
            DFS(neighbour, component_num);
        }
    }
}

int SearchComponents (int top_count, int component_num)
{
    for (int i = 0; i < top_count; ++i)
    {
        if (!used_tops[i])
        {
            DFS(i, component_num);
            component_num = component_num + 1;
        }
    }

    return component_num - 1;
}

int main() {
    freopen("components.in", "r", stdin);
    freopen("components.out", "w", stdout);

    int top_count, edge_count;

    int component_number = 1; /// начинаем отсчет компонент связности с 1

    std::cin >> top_count >> edge_count;

    AddGraph(top_count, edge_count);

    std::cout << SearchComponents(top_count, component_number) << std::endl;

    for (int i = 0; i < top_count; i++)
    {
        std::cout << component_nums[i] << " ";
    }

    return 0;
}