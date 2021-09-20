#include <iostream>
#include <fstream>

using namespace std;

void SiftDown(int a[], int n, int i) // функция создания дерева
{
    int largest = i;  // корень
    int l = 2*i+1; // левый потомок
    int r = 2*i+2;  // правый потомок
        if (l < n && a[l] > a[largest])  // если левый потомок больше корня, делаем чтобы потомок стал корнем
           largest = l;
        if (r < n && a[r] > a[largest])  // если правый потомок больше корня, делаем чтобы потомок стал корнем
           largest = r;
        if (largest != i)
        {
           swap (a[i], a[largest]); // если больший элемент не корень, меняем с корнем чтобы элемент стал корнем
           SiftDown (a, n, largest); // запуск рекурсии
        }
}

void HeapSort(int a[], int n) // сортировка
{
    for (int i = n/2 - 1; i >= 0; i--) // для создания дерева
        SiftDown(a, n, i);
    for (int i = n - 1; i >= 0; i--)
    {
        swap(a[0], a[i]); // свап самого большого элемента с последним
        SiftDown(a, i, 0); // восстановление дерева
    }
}

int main() {
    int n;
    ifstream fin("sort.in");
    ofstream fout("sort.out");
    fin >> n;
    int a[n];
    for (int i = 0; i < n; i++) // создание массива
    {
        fin >> a[i];
    }
    HeapSort(a, n); // использование фунцкии сортировки
    for (int i = 0; i < n; i++)
    {
        fout << a[i]<< " "; 
    }
    fin.close();
    fout.close();
    return 0;
}
