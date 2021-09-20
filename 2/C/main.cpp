#include <fstream>
using namespace std;
long long n,r[300000],a[300000],ans;
void mergeSort(long left, long right){
    if (left < right){
        long mid = (left + right) / 2,invLeft = mid - left +1;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        long i = 0, j = 0;
        while (left + i <= mid && mid + 1 + j <= right) {
            if (a[left + i] > a[mid + 1 + j]) {
                r[i + j] = a[mid + 1 + j];
                ans += invLeft - i; // считает колво инверсий
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
            ans += invLeft - i; // считает колво инверсий
            j++;
        }

        for (i = 0; i < right - left + 1; i++)
            a[left + i] = r[i];
    }
}

int main() {
    ifstream fin("inversions.in");
    ofstream fout("inversions.out");
    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> a[i];
    }
    mergeSort(0, n - 1);
    fout << ans;
    fin.close();
    fout.close();
}