#include <iostream>
#include <queue>
#include <fstream>

struct point_           /// »нформаци€ о точке
{
    int x;
    int y;
    std::string way;                 /// ѕуть от старта до текущей точки
    bool access;                     /// можно или нельз€ пройти в эту точку
};

/// ѕодсчЄт кротчайшего рассто€ни€ до точки выхода из лабиринта
void count_shortest_way(point_ **arr, point_ start)
{
    std::queue<point_> queue;          /// »нициализируем очередь
    queue.push(start);                 /// ƒобавл€ем стартовую точку
    while (!queue.empty())             /// ѕока очередь !пуста
    {
        point_ p = queue.front();      /// берЄм первый элемент
        queue.pop();

        /// если в точку можно пройти и в ней мы ещЄ не были -> помещаем еЄ в очередь
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

    /// »нициализируем двумерный рассширенный массив дл€ хранени€ исходных данных и границ
    point_ **arr = new point_ *[n + 2];

    for (int i = 0; i < n + 2; i++)
    {
        arr[i] = new point_[m + 2];
    }

    /// »нициализируем точки дл€ начала и конца лабиринта
    point_ start, finish;
    for (int i = 0; i < n + 2; i++)
    {
        for (int j = 0; j < m + 2; j++)
        {
            arr[i][j].x = i;                  /// заполн€ем координаты точек индексами матрицы
            arr[i][j].y = j;
        }
    }

    for (int i = 1; i < n + 1; i++)           /// считываем данные из файла и заполн€ем матрицу
    {
        for (int j = 1; j < m + 1; j++)
        {
            char point;
            fin >> point;
            if (point == '#')                  /// # как не пройденна€
                arr[i][j].access = false;
            else
                arr[i][j].access = true;

            if (point == 'S')                  /// «аполн€ем пол€ точки старта дл€ начальной точки
            {
                start.x = i;
                start.y = j;
            }
            else if (point == 'T')             /// «аполн€ем пол€ точки старта дл€ конечной точки
            {
                finish.x = i;
                finish.y = j;
            }
            arr[i][j].way = "";                /// «аполн€ем путь дл€ каждой точки
        }
    }

    for (int i = 0; i < n + 2; i++)            /// заполн€ем вертикальные границы
    {
        arr[i][0].access = false;
        arr[i][m + 1].access = false;
    }
    for (int i = 0; i < m + 2; i++)            /// заполн€ем гооризонтальные границы
    {
        arr[0][i].access = false;
        arr[n + 1][i].access = false;
    }

    count_shortest_way(arr, start);

    if (arr[finish.x][finish.y].way == "")      /// если у конечной точки путь пустой
        fout << "-1" << std::endl;                   /// то до неЄ нельз€ добратьс€
    else
        /// else выводим путь дл€ конечной точки
        fout << arr[finish.x][finish.y].way.length() << std::endl << arr[finish.x][finish.y].way;
    return 0;
}
