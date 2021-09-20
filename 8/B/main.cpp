#include <iostream>
#include <fstream>


int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int top, i, j;
    int matrix[100][100];
    fin >> top;

    /// ��������� ������� � ��������� �� �����
    for (i = 0; i < top; i++){
        for (j = 0; j < top; j++){
            fin >> matrix[i][j];
            if (i == j && matrix[i][j] == 1){
                fout << "NO";
                return 0;
            }
        }
    }

    /// �������� �� �������������� ������������ ������� ���������
    for (i = 0; i < top; i++){
        for (j = 0; j < top; j++) {
           if (matrix[i][j] != matrix[j][i]){
               fout << "NO";
               return 0;
           }
        }
    }
    fout << "YES";

    fin.close();
    fout.close();

    return 0;
}


