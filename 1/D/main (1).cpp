#include <iostream>
#include <vector>
using namespace std;

int main () {

    int n, i, j;
    freopen("smallsort.in", "r", stdin);
    freopen("smallsort.out", "w", stdout);

    cin >> n;
    vector<long> mass(n, 0);

    for (i = 0; i < n; i++)
        cin >> mass[i];

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (mass[i] > mass[j])
            {

                int k = mass[i];
                mass[i] = mass[j];
                mass[j] = k;

            }
    for (i = n - 1; i >= 0; i--)
        cout << mass[i] << "\n";

    return 0;


}
