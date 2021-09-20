#include <fstream>
#include <vector>
using namespace std;

/// Суть програмы заключается в том, чтобы проверить выполняется ли для двоичного дерева свойства двоичного дерева поиска
/// Мы рекурсивно спускаемся по дереву, записывая вершины дерева в нужном порядке. После чего мы запускаем функцию проверки
/// этого вектора на отсортированность. Если вектор отсортирован, то дерево корректно.

struct element
{
    int l; /// индекс левый потомок
    int r; /// индекс правый потомок
    int value; /// значение элемента
};

bool checking(vector <int>& peak) /// рекурсивная функция проверки корректности условия
{
    for(int i = 1; i < peak.size(); i++)
    {
        if (peak[i] <= peak[i-1]) /// если текущий элемент меньше либо равен предыдущему
            return false; /// условие не выполнено, проверка не пройдена
    }
    return true; /// условие выполнено, проверка пройдена
}

void func_peak(element *tree, vector <int>& peak, int a) /// рекурсивная функция записи вершин в вектор
{
if (a != -1) /// если нет потомка, дальше не идем
     {
        func_peak(tree, peak, tree[a].l); /// рекурсивный запуск для левого потомка
        peak.push_back(tree[a].value);       /// добавлям корень в векторный массив
        func_peak(tree, peak, tree[a].r); /// рекурсивный запуск для правого потомка
     }
}
bool vec(element* tree, int a) /// функция создания вектора и запуска функций проверки условия
{
    vector <int> peak;               /// создание векторного массива для хранения вершин
    func_peak(tree, peak, 0);  /// записываем вершины в нужном порядке
    return checking(peak);        /// возврат результата корректности
}

int main()
{
    ifstream fin("check.in");
    ofstream fout("check.out");
    int n;
      fin >> n;
      element* tree = new element[n]; /// массив для хранения дерева
    for (int i = 0; i < n; i++)
    {
        fin >> tree[i].value >> tree[i].l >> tree[i].r;
        tree[i].l--;
        tree[i].r--;
    }
    if (n == 0 || vec(tree, 0) == true)   /// если дерево пустое или проверка корректности выполнена
        fout << "YES";
    else
        fout << "NO";
    fin.close();
    fout.close();
return 0;
}