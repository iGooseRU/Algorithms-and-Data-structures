#include <fstream>

using namespace std;

int main()
{
    int h, w;
    ifstream fin("turtle.in");
    ofstream fout("turtle.out");

    fin >> h >> w; // считывание h,w

    int** a = new int*[h+1]; //создаем двумерный динамический массив
    a[0] = new int[w]; // чтобы не выйти за границу массива
    for (int i = 1; i < h+2; i++)
    {
        a[i] = new int[w];
    }
    for (int i = 0; i < w + 1; i++)
    {
        a[0][i] = 0; // чтобы не выйти за границы массива по вертикали
    }
    for(int i = 1; i < h + 1; i++) {
        for (int j = 0; j < w; j++)
        {
            fin >> a[i][j]; // считывание очков с матрицы, заполняем массив
        }
        a[i][w] = 0; // чтобы не выйти за границы массива по горизонтали
    }

    fin.close();


    for (int x = w - 1; x >= 0; x--) { // проходим справа налево от главной диагонали
        for (int y = 1; y <= h; y++) { // проходим вниз от главной диагонали
            if (a[y - 1][x] > a[y][x + 1])
            {
                a[y][x] += a[y - 1][x];
            } else {
                a[y][x] += a[y][x + 1]; // ищем где больше очков после кадого шага
            }
        }
    }

    fout << a[h][0];
    fout.close();
    return 0;
}
