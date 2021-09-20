#include <fstream>
#include <vector>

std::vector<std::vector<int>> g;
std::vector<bool> used;
std::vector<int> ans;

/// WHITE - 1 // GRAY - 2 // BLACK - 3 //

void topSort(int top)                               /// �������������� ����������
{
    used[top] = true;
    for (int i: g[top])
        if (!used[i])
            topSort(i);
    ans.push_back(top);
}

std::vector<int> color;
std::vector<int> cycle;

bool check(int top, int start, int finish)          /// �������� �� �����
{
    color[top] = 2;                                 /// �������� ������� �����
    int temp;
    for (auto i: g[top])                            /// ���������� �� ���� ������� ��������
    {
        temp = i;
        if (color[temp] == 1)                       /// ���� ������ � ����� �������
        {
            cycle[temp] = top;
            if (check(temp, start, finish))         /// ��������� ������� �������
                return true;
        }
        else if (color[temp] == 2)                  /// ���� ������ � ����� �������
        {
            start = temp;
            finish = top;
            return true;
        }
    }
    color[top] = 3;                                 /// ����� ������� �� ������� ������ ���� �� ������
    return false;
}

int main()
{
    std::ifstream fin("topsort.in");
    std::ofstream fout("topsort.out");
    int n, m, v1, v2, start = -1, finish = -1;
    fin >> n >> m;
    g.resize(n);                                    /// ��������� ������� ������������ ����������
    used.assign(n, false);
    color.assign(n, 1);
    cycle.assign(n, -1);
    for (int i = 0; i < m; i++)                     /// ��������� ������ � ��������
    {                                               /// � ������ ������ ���������
        fin >> v1 >> v2;
        v1--;
        v2--;
        g[v1].push_back(v2);
    }
    for (int i = 0; i < n; i++)                      /// ������������ ��������
    {
        if (check(i, start, finish))                 /// ���� ����� �� ������� �� ������ ��������
        {                                            /// �� ���� �������� ���������
            fout << -1;
            return 0;
        }
    }
    for (int i = 0; i < n; i++)                         /// ��������� ��� ������ ����� �������������� ����������
        if (!used[i])
            topSort(i);

    std::vector<int>ansReverse(n);                      /// ����������� ������

    for (int i = 0; i < n; i++)
        ansReverse[i] = ans[n - 1 - i];
    for (auto i : ansReverse)                           /// ������� ���������
        fout << i + 1 << " ";
    return 0;
}