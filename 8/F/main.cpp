#include <iostream>
#include <queue>
#include <fstream>

struct point_           /// ���������� � �����
{
    int x;
    int y;
    std::string way;                 /// ���� �� ������ �� ������� �����
    bool access;                     /// ����� ��� ������ ������ � ��� �����
};

/// ������� ����������� ���������� �� ����� ������ �� ���������
void count_shortest_way(point_ **arr, point_ start)
{
    std::queue<point_> queue;          /// �������������� �������
    queue.push(start);                 /// ��������� ��������� �����
    while (!queue.empty())             /// ���� ������� !�����
    {
        point_ p = queue.front();      /// ���� ������ �������
        queue.pop();

        /// ���� � ����� ����� ������ � � ��� �� ��� �� ���� -> �������� � � �������
        if (arr[p.x + 1][p.y].access && arr[p.x + 1][p.y].way == "")

        {
            arr[p.x + 1][p.y].way = p.way + "D";
            queue.push(arr[p.x + 1][p.y]);
        }

        if (arr[p.x - 1][p.y].access && arr[p.x - 1][p.y].way == "")
        {
            arr[p.x - 1][p.y].way = p.way + "U";
            queue.push(arr[p.x - 1][p.y]);
        }

        if (arr[p.x][p.y + 1].access && arr[p.x][p.y + 1].way == "")
        {
            arr[p.x][p.y + 1].way = p.way + "R";
            queue.push(arr[p.x][p.y + 1]);
        }

        if (arr[p.x][p.y - 1].access && arr[p.x][p.y - 1].way == "")
        {
            arr[p.x][p.y - 1].way = p.way + "L";
            queue.push(arr[p.x][p.y - 1]);
        }
    }
}

int main()
{
    std::ifstream fin("input.txt");
    std:: ofstream fout("output.txt");
    int n, m;
    fin >> n >> m;

    /// �������������� ��������� ������������ ������ ��� �������� �������� ������ � ������
    point_ **arr = new point_ *[n + 2];

    for (int i = 0; i < n + 2; i++)
    {
        arr[i] = new point_[m + 2];
    }

    /// �������������� ����� ��� ������ � ����� ���������
    point_ start, finish;
    for (int i = 0; i < n + 2; i++)
    {
        for (int j = 0; j < m + 2; j++)
        {
            arr[i][j].x = i;                  /// ��������� ���������� ����� ��������� �������
            arr[i][j].y = j;
        }
    }

    for (int i = 1; i < n + 1; i++)           /// ��������� ������ �� ����� � ��������� �������
    {
        for (int j = 1; j < m + 1; j++)
        {
            char point;
            fin >> point;
            if (point == '#')                  /// # ��� �� ����������
                arr[i][j].access = false;
            else
                arr[i][j].access = true;

            if (point == 'S')                  /// ��������� ���� ����� ������ ��� ��������� �����
            {
                start.x = i;
                start.y = j;
            }
            else if (point == 'T')             /// ��������� ���� ����� ������ ��� �������� �����
            {
                finish.x = i;
                finish.y = j;
            }
            arr[i][j].way = "";                /// ��������� ���� ��� ������ �����
        }
    }

    for (int i = 0; i < n + 2; i++)            /// ��������� ������������ �������
    {
        arr[i][0].access = false;
        arr[i][m + 1].access = false;
    }
    for (int i = 0; i < m + 2; i++)            /// ��������� ��������������� �������
    {
        arr[0][i].access = false;
        arr[n + 1][i].access = false;
    }

    count_shortest_way(arr, start);

    if (arr[finish.x][finish.y].way == "")      /// ���� � �������� ����� ���� ������
        fout << "-1" << std::endl;                   /// �� �� �� ������ ���������
    else
        /// else ������� ���� ��� �������� �����
        fout << arr[finish.x][finish.y].way.length() << std::endl << arr[finish.x][finish.y].way;
    return 0;
}
