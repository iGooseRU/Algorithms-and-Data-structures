#include <fstream>
using namespace std;
int n,r[300000],a[300000];
void mergeSort(int left, int right){
    if (left < right){
        int mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        int i = 0, j = 0;
        while (left + i <= mid && mid + 1 + j <= right) {
            if (a[left + i] > a[mid + 1 + j]) {
                r[i + j] = a[mid + 1 + j];
                j++;
            } else {
                r[i + j] = a[left + i];
                i++;
            }
        }
        while (left + i <= mid){
            r[i + j] = a[left + i];
            i++;
        }

        while (mid + 1 + j <= right){
            r[i + j] = a[mid + 1 + j];
            j++;
        }

        for (i = 0; i < right - left + 1; i++)
            a[left + i] = r[i];
    }
}

int main() {
    ifstream fin; fin.open("sort.in");
    fin >> n;
    for (int i = 0; i < n; i++)
        fin >> a[i];
    fin.close();
    mergeSort(0, n - 1);
    ofstream fout; fout.open("sort.out");
    for (int i = 0; i < n; i++)
        fout << a[i] << ' ';
    fout.close();
    return 0;
}