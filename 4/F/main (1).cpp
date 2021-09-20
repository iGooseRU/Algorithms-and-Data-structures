#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

double h(vector<double> &a, double &b) {
    int count = 0, o = 0;
    a[1] = b;
    for (int i = 2; i < a.size(); i++) {
        a[i] = (2 + 2 * a[i - 1] - a[i - 2]);
        if (a[i] == 0)
            count++;
        if (a[i] < 0)
            o++;
    }
    if (o > 0 || count >= 2)
        return -1;
    else
        return a[a.size() - 1];
}

double bin_search(vector<double> &a) {
    double m, min, count = 0;
    double l = 0;
    double r = a[0];
    while (l < r -0.000001) {
        m = (l + r) / 2;
        if (h(a, m) >-1) {
            if (count == 0) {
                min = h(a, m);
                count++;
            } else if (h(a, m) <min)
                min = h(a, m);
            r = m;
        } else
            l = m;
    }
    return min;
}

int main() {
    freopen("garland.in","r", stdin);
    freopen("garland.out","w", stdout);
    int n;
    cin >> n;
    vector<double> a(n);
    cin >> a[0];
    cout << fixed << setprecision(2)<< bin_search(a);
    return 0;
}