#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct node {
    int key, height, balance, num;
    node *l, *r, *par;

    node() {
        key = -1;
        height = 1;
        num = balance = 0;
        l = r = par = nullptr;
    }
};

int getSize(node *p) {
    if (!p) {
        return 0;
    } else {
        return p->height;
    }
}

int bfactor(node *p){
    return getSize(p->r) - getSize(p->l);
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
    if(!p->par) {
        q->par = nullptr;
    } else {
        q->par = p->par;
        if(q->r == q->par->l) {
            p->par->l = q;
        }
        if(q->r == q->par->r){
            p->par->r = q;
        }
    }
    correctHeight(p);
    correctHeight(q);
    q->balance = bfactor(q);
    return q;
}

node *rotateLeft(node *p) {
    node *q = p->r;
    p->r = q->l;
    q->l = p;
    if(!p->par) {
        q->par = nullptr;
    } else {
        q->par = p->par;
        if(q->l == q->par->l) {
            p->par->l = q;
        }
        if(q->l == q->par->r){
            p->par->r = q;
        }
    }
    correctHeight(p);
    correctHeight(q);
    q->balance = bfactor(q);
    return q;
}

node *balance(node *p) {
    correctHeight(p);
    p->balance = bfactor(p);
    if(p->balance == 2) {
        if (p->r->balance < 0) {
            p->r = rotateRight(p->r);
        }
        p = rotateLeft(p);
    }
    if(p->balance == -2) {
        if (p->l->balance > 0) {
            p->l = rotateLeft(p->l);
        }
        p = rotateRight(p);
    }
    if(p->par == nullptr){
        return p;
    }
    balance(p->par);
}

void connection(node *p, int x, vector<node> &n) {
    if(p->key < x){
        if(p->r){
            connection(p->r, x, n);
        } else {
            p->r = &n[n.size() - 1];
            n[n.size() - 1].par = p;
        }
    }
    if(p->key > x){
        if(p->l){
            connection(p->l, x, n);
        } else {
            p->l = &n[n.size() - 1];
            n[n.size() - 1].par = p;
        }
    }
}

int main() {
    ifstream in("addition.in");
    ofstream out("addition.out");
    int n;
    in >> n;
    out << n + 1 << "\n";
    vector<node> nodes(n + 1);

    for (int i = 0; i < n; i++) {
        int key, left_child, right_child;
        in >> key >> left_child >> right_child;
        nodes[i].key = key;
        nodes[i].num = i + 1;
        if (left_child) {
            nodes[i].l = &nodes[left_child - 1];
            nodes[left_child - 1].par = &nodes[i];
        }
        if (right_child) {
            nodes[i].r = &nodes[right_child - 1];
            nodes[right_child - 1].par = &nodes[i];
        }
    }

    int x;
    in >> x;
    nodes[n].key = x;
    nodes[n].num = n + 1;
    connection(&nodes[0], x, nodes);

    for (int i = n; i >= 0; i--) {
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
    int beginner;
    if(nodes.size() != 1) {
        beginner = balance(nodes[n].par)->num;
    } else {
        beginner = 1;
    }
    q.push(beginner);
    int counter = 2;
    while (!q.empty()) {
        int cur = q.front() - 1;
        q.pop();
        out << nodes[cur].key << " ";
        if (nodes[cur].l) {
            q.push(nodes[cur].l->num);
            out << counter << " ";
            counter++;
        } else {
            out << "0 ";
        }
        if (nodes[cur].r ){
            q.push(nodes[cur].r->num);
            out << counter << "\n";
            counter++;
        } else {
            out << "0\n";
        }
    }
}