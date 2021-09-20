#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int top, edge, i, j, k;
    int matrix[100][100] = {0};

    fin >> top >> edge;

    /// вписываем ребра
    for (k = 0; k < edge; k++){
        fin >> i >> j;
        matrix[i - 1][j - 1] = 1;
    }

    /// вывод
    for (i = 0; i < top; i++){
        for (j = 0; j < top; j++){
            fout << matrix[i][j] << ' ';
        }
      fout << endl;
    }
    fin.close();
    fout.close();
    return 0;
}
