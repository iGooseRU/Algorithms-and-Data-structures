#include <iostream>
#include <fstream>


int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int top, edge, i, j;
    int matrix[100][100] = {0};
    bool out = false;

    fin >> top >> edge;

    for (int k = 0; k < edge; k++){
        fin >> i >> j;
       if (matrix[i - 1][j - 1] == 0){
           matrix[i - 1][j - 1] += 1;
           matrix[j - 1][i - 1] += 1;
       } else {
           out = true;
           break;
       }
    }
    (out) ? fout << "YES" : fout << "NO";

    return 0;
}