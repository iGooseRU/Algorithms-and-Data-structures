#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct node {
    int key, height, balance, num;
    node *l, *r;

    node() {
        key = -1;
        height = 1;
        num = balance = 0;
        l = r = nullptr;
    }
};

int getSize(node *p) {
    if (!p) {
        return 0;
    } else {
        return p->height;
    }
}

void correctHeight(node *p) {
    int hl = getSize(p->l);
    int hr = getSize(p->r);
    p->height = max(hl, hr) + 1;
}

node *rotateRight(node *p) {
    node *q = p->l;
    p->l = q->r;
    q->r = p;
    correctHeight(p);
    correctHeight(q);
    return q;
}

node *rotateLeft(node *p) {
    node *q = p->r;
    p->r = q->l;
    q->l = p;
    correctHeight(p);
    correctHeight(q);
    return q;
}

int balance(node *p) {
    if (p->r->balance < 0) {
        p->r = rotateRight(p->r);
    }
    p = rotateLeft(p);
    return p->num;
}

int main() {

    ifstream fin("rotation.in");
    ofstream fout("rotation.out");
    int n;
    fin >> n;
    fout << n << "\n";
    vector<node> nodes(n);

    for (int i = 0; i < n; i++) {
        int key, left_child, right_child;
        fin >> key >> left_child >> right_child;
        nodes[i].key = key;
        nodes[i].num = i + 1;
        if (left_child) {
            nodes[i].l = &nodes[left_child - 1];
        }
        if (right_child) {
            nodes[i].r = &nodes[right_child - 1];
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        int h = 0;
        if (nodes[i].r) {
            nodes[i].balance += nodes[i].r->height;
            h = max(h, nodes[i].r->height);
        }
        if (nodes[i].l) {
            nodes[i].balance -= nodes[i].l->height;
            h = max(h, nodes[i].l->height);
        }
        nodes[i].height = h + 1;
    }

    queue<int> q;
    int beginner = balance(&nodes[0]);
    q.push(beginner);
    int counter = 2;
    while (!q.empty()) {
        int cur = q.front() - 1;
        q.pop();
        fout << nodes[cur].key << " ";
        if (nodes[cur].l) {
            q.push(nodes[cur].l->num);
            fout << counter << " ";
            counter++;
        } else {
            fout << "0 ";
        }
        if (nodes[cur].r) {
            q.push(nodes[cur].r->num);
            fout << counter << "\n";
            counter++;
        } else {
            fout << "0\n";
        }
    }
}