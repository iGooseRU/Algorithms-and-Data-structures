#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("isheap.in");
    ofstream fout("isheap.out");
    int n;
    fin >> n;
    int a[n];
    fin >> a[1]; // задали корень
    int k = 1;   // счетчик
    for (int i = 2; i <= n; ++i) {  // цикл проверяющий возрастающая ли пирамида
        fin >> a[i];
        if (i % 2 == 0) {  // если четное
            if (a[i/2] > a[i]) { // проверяем обратное условие
                fout << "NO";
                break; // выход из цикла

            }
        } else {
            if (a[(i - 1)/2] > a[i]) {  // проверка обратного условия если число не четное
                fout << "NO";
                break;
            }
        }
        k++;
    }
    if (k == n) {
        fout << "YES";
    }
    fin.close();
    fout.close();
    return 0;
}