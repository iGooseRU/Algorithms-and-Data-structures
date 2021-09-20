#include <fstream>
using namespace std;

struct Element
{
    int data;
    Element* prev;
    Element* next;
};

class Queue
{
private:
    Element* start;
    Element* last;
public:
    Queue()
    {
        start = NULL;
        last = NULL;
    }
    void unqueue(int a)
    {
        Element* point = new Element();
        if (start != NULL)
            start->next = point;
        else
            last = point;
        point->data = a;
        point->prev = start;
        point->next = NULL;
        start = point;
    }
    int dequeue()
    {
        int result = last->data;
        Element* del = last;
        last = last->next;
        if (last == NULL)
        {
            start = NULL;
        }
        delete del;
        return result;
    }
};

int main()
{
    Queue q;
    ifstream fin("queue.in");
    ofstream fout("queue.out");
    int n;
    fin >> n;
    char command;
    for (int i = 0; i < n; i++)
    {
        fin >> command;
        if (command == '+')
        {
            int num;
            fin >> num;
            q.unqueue(num);
        }
        else
            fout << q.dequeue() << endl;
    }
    return 0;
}