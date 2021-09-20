#include <fstream>
#include <iostream>

using namespace std;

string a[1000], res[1000];
long n, len, k;

void Sort(int pos) {  // функция сортировки по разрядам
    char help = 'a';  // вспомогательный элемент
    int j = 0;
    for (int i = 0; i < 26; i++) {  // цикл для сравнения
        for (int g = 0; g < n; g++) { // цикл сравнения со след буквой
            if (a[g][pos]==help) {  // сравнение с вспомогательным элементом
                res[j] = a[g];
                j++;
            }
        }
        help++; // увеличиваем вспомогательный элемент
    }
    for (int i = 0; i < n; i++)
        a[i]=res[i];
}

int main() {
    ifstream fin("radixsort.in");
    ofstream fout("radixsort.out");
    fin >> n >> len >> k;
    for (int i = 0; i < n; i++)
        fin >> a[i];
    for (int i = len-1; i >= len-k; i--)
        Sort(i);


    for (int i = 0; i < n; i++)
        fout << a[i] << '\n';
    return 0;
}