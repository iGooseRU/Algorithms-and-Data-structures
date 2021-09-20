#include <fstream>

#define SIZE 1000000

using namespace std;
struct AVLTree {
    int value = 0;
    int l = 0;
    int r = 0;
    int balance = 0;
} *AVL[SIZE];

class AVLTreeClass {
public:
    static void MakeAVL(int value, int left, int right, int index) {
        AVL[index + 1] = new AVLTree;
        AVL[index + 1]->l = left;
        AVL[index + 1]->r = right;
        AVL[index + 1]->value = value;
    }

    int getBalance(int i) {
        int HLeft, HRight; /// Высота левого / правого поддерева
        if (AVL[i] == nullptr || i == 0) {
            return 0;
        }
        HLeft = getBalance(AVL[i]->l);
        HRight = getBalance(AVL[i]->r);
        AVL[i]->balance = HRight - HLeft;
        return (max(HLeft, HRight) + 1);
    }
};


int main() {

    ifstream fin("balance.in");
    ofstream fout("balance.out");

    ios_base::sync_with_stdio(false); fin.tie(nullptr);
    AVLTreeClass avl;

    int i, n, left, right, value = 0;
    string cmd;
    fin >> n;
    for (i = 0; i < n; i++) {
        fin >> value >> left >> right;
        avl.MakeAVL(value, left, right, i);
    }
    avl.getBalance(1);
    for (i = 1; i <= n; i++) {
        fout << AVL[i]->balance << "\n";
    }
    fin.close();
    fout.close();

    return 0;
}
