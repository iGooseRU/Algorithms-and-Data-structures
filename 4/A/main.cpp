#include <fstream>
using namespace std;

struct stack_node // задание структуры для одного элемента
{
    int info;
    stack_node* next; // указатель на следующий элемент массива
};

class Stack
{
private:
    stack_node* last; // указатель на верхний элемент стека
public:
    Stack() // конструктор чтоб инициализировать переменную для всех ф-ий этого класса
    {
        last = NULL; // задаем ноль
    }
    void push(int a)  // функция для заполнения стека элементами
    {
        stack_node* node = new stack_node(); // сдвиг адресов и внесение нового элемента
        node->next = last;
        node->info = a;
        last = node;
    }
    int poop()  //функция удаление элемента, возвращает его значение
    {
        int res = last->info;
        stack_node* del = last;
        last = last->next;
        delete del;
        return res;
    }
};

int main()
{
    Stack stack;
    ifstream fin("stack.in");
    ofstream fout("stack.out");
    int n;
    fin >> n;
    char cmd; // строка команд
    for (int i = 0; i < n; i++)
    {
        fin >> cmd;
        if (cmd == '+') // если +, заносим в стек
        {
            int num;
            fin >> num;
            stack.push(num);
        }
        else
            fout << stack.poop() << endl;
    }
}