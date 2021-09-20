#include <fstream>
#include <string>

using namespace std;

struct element /// стуктура для элементов бин дерева поиска
{
    int value; /// число
    element* par; /// указатель на родителя
    element* l; /// указатель на левого потомка
    element* r; /// указатель на правого потомка
};

class search_tree /// создание класса
{
private:
    element* base = nullptr; /// корень равен пустоте
public:

    element* search(int x) /// поиск элемента в бин дереве поиска
    {
        element* current_el = base; /// текущий элемент равен корню
        while (current_el != nullptr && x != current_el->value) /// запускаем цикл пока не найдём значение нужного элемента или выясним, что такого элемента нет
        {
            if (x < current_el->value)
                current_el = current_el->l;  /// поиск нужного значения в левом или в правом поддереве
            else
                current_el = current_el->r;
        }
        return current_el; /// возвращаем найденное значение
    }

    void add_el(int x) /// фунция которая добавляет элементы
    {
        if (check_el(x)) /// проверка сущетвует ли конкретно этот элемент
            return;
        element* new_el = new element; /// создание новой ветки дереве
        new_el->value = x;
        new_el->par = nullptr;         ///  заполнение стуктуры
        new_el->l = nullptr;
        new_el->r = nullptr;
        element* current_el = base; /// структура для добавляемого элемента
        /// поиск места для элемента
        while (current_el != nullptr)  /// если текущий больше добавляемого то ищем каким будет текущий элемент(правым или левым потомком)
        {
            new_el->par = current_el;
            if (new_el->value < current_el->value)
                current_el = current_el->l;
            else
                current_el = current_el->r;
        }
        if (new_el->par == nullptr) /// если дерево пустое, добавляемый элемент будет корнем
            base = new_el;
        else
        {
            if (new_el->value < new_el->par->value) /// если текущий меньше добавляемого то ищем каким будет добавляемый элемет(правым или левым потомком)
                new_el->par->l = new_el;
            else
                new_el->par->r = new_el;
        }
    }

    void del(int x) /// функция для удаления элемента
    {
        element* del_el = search(x); /// поиск нужного элемент
        if (del_el == nullptr) /// если нужного элемента нет
        {
            return;
        }
        element* previous_el; /// структура для предыдущего элемента
        element* hepl_el; /// структура для вспомогательного элемента
        if (del_el->l == nullptr || del_el->r == nullptr) /// если у удаляемого элемента нет потомков
            previous_el = del_el; /// то предыдущий становиться равен удаляемому
        else
            previous_el = next(x); /// иначе ищем минимальный больший > x
        if (previous_el->l != nullptr) /// если предыдущий элемент != пустоте
            hepl_el = previous_el->l;
        else
            hepl_el = previous_el->r;
        if (hepl_el != nullptr) /// если вспомогательный элемент != пустоте
            hepl_el->par = previous_el->par;
        if (previous_el->par == nullptr) /// если родитель равен пустоте
            base = hepl_el;
        else
        {
            if (previous_el == previous_el->par->l)
                previous_el->par->l = hepl_el;
            else
                previous_el->par->r = hepl_el;
        }
        if (previous_el != del_el) /// если предыдущий элемент != удаляемому
            del_el->value = previous_el->value; /// удаляемый становиться предыдущим
        delete previous_el; /// удаляем предыдущий элемент
    }

    bool check_el(int x) /// проверяем равен ли нужный нам элемент пустоте
    {
        return search(x) != nullptr;
    }

    element* next(int x) /// Функция возвращает минимальный элемент больший x или null, если такого элемента нет
    {
        element* current_el = base;   /// текущий элемент равен корню
        element* successor_el = nullptr; /// следующий - пустоте
        while (current_el != nullptr)
        {
            if (current_el->value > x) /// условие
            {
                successor_el = current_el;
                current_el = current_el->l;
            }
            else
                current_el = current_el->r;
        }
        return successor_el; /// возвращаем значение
    }

    element* Previous(int x) /// Функция возвращает максимальный элемент меньший x или null, если такого элемента нет
    {
        element* current_el = base; /// текущий элемент равен корню
        element* previous_el = nullptr; /// предыдущий - пустоте
        while (current_el != nullptr)
        {
            if (current_el->value < x) /// условие
            {
                previous_el = current_el;
                current_el = current_el->r;
            }
            else
                current_el = current_el->l;
        }
        return previous_el;
    }
};

int main()
{
    ifstream fin("bstsimple.in");
    ofstream fout("bstsimple.out");
    search_tree tree;
    string cmd;
    int key;
    while (fin >> cmd >> key)
    {
        if (cmd == "insert")
            tree.add_el(key);
        if (cmd == "delete")
            tree.del(key);
        if (cmd == "exists")
        {
            if (tree.search(key))
                fout << "true\n";
            else
                fout << "false\n";
        }
        if (cmd == "next")
        {
            element* res = tree.next(key);
            if (res == nullptr)
                fout << "none\n";
            else
                fout << res->value << "\n";
        }
        if (cmd == "prev")
        {
            element* res = tree.Previous(key);
            if (res == nullptr)
                fout << "none\n";
            else
                fout << res->value << "\n";
        }
    }
    fin.close();
    fout.close();
    return 0;
}
