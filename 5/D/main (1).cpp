#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Marker /// структура для маркеров которая содержит строку и значение
{
    string name;
    int num;
};

int main()
{
    ifstream fin("quack.in");
    ofstream fout("quack.out");
    vector <string> a;
    vector <Marker> marker; /// создаём метку
    queue <unsigned short int> Queue; /// очередь
    unsigned short int registers[26]; /// регистр
    for (int i = 0; i < 26; i++)
        registers[i] = 0; /// присваеваем всем буквам регистр ноль
    while (!fin.eof()) /// цикл пока не кончится файл
    {
        string com;
        fin >> com;
        a.push_back(com); /// добавляем команды в строку
        if (com[0] == ':')
        {
            string name = com;
            name.erase(0, 1); /// удаляем первый символ строки (erase)
            marker.push_back({ name, (int)a.size() - 1 }); /// добавляем в очередь
        }
    }
    int i = 0; /// счётчик для while
    while (i < a.size()) /// запускаем цикл пока не пройдёмся по всем командам
    {
        /// берем два верхних элемента очереди, удаляем их, проводим требующиеся операции, результат добавляем в очередь
        if (a[i][0] == '-')
        {
            unsigned short int x = Queue.front(); /// берем первый элемент в очереди
            Queue.pop(); /// удаляем
            unsigned short int y = Queue.front(); /// возвращаем ссылку на первый элемент вектора(front)
            Queue.pop(); /// то же действие провидим со следующим числом
            Queue.push((x - y) % 65536); /// результат опирации добавляем в стек
        }
        else if (a[i][0] == '+')
        {
            unsigned short int x = Queue.front();
            Queue.pop();
            unsigned short int y = Queue.front();
            Queue.pop();
            Queue.push((x + y) % 65536);
        }
        else if (a[i][0] == '*')
        {
            unsigned short int x = Queue.front();
            Queue.pop();
            unsigned short int y = Queue.front();
            Queue.pop();
            Queue.push((x * y) % 65536);
        }
        else if (a[i][0] == '%')
        {
            unsigned short int x = Queue.front();
            Queue.pop();
            unsigned short int y = Queue.front();
            Queue.pop();
            if (y == 0) /// т.к 0 mod 0 = 0
                Queue.push(0); /// добавляем ноль
            else
                Queue.push(x % y); /// иначе добавляем результат операции
        }
        else if (a[i][0] == '/')
        {
            unsigned short int x = Queue.front();
            Queue.pop();
            unsigned short int y = Queue.front();
            Queue.pop();
            if (y == 0) /// рассматриваем случай, когда частное - это ноль
                Queue.push(0);
            else
                Queue.push(x / y);
        }

        else if (a[i][0] == '>')
        {
            unsigned short int x = Queue.front();
            Queue.pop(); /// удаляем элемент из очереди
            registers[(int)a[i][1] - (int)'a'] = x; /// добавляем удалённый элемент в регистр
        }
        else if (a[i][0] == '<') /// берём значение из регистра
            Queue.push(registers[(int)a[i][1] - (int)'a']);
        else if (a[i][0] == 'P')
        {
            if (a[i].size() == 1) /// если после Р единственный символ в строке
            {
                fout << Queue.front() << "\n"; /// выводим элемент который мы в последствии удалим
                Queue.pop();
            }
            else
            {
                fout << registers[(int)a[i][1] - (int)'a'] << "\n"; /// выводим значение из регистра
            }
        }
        else if (a[i][0] == 'C') /// выводит число как символ
        {
            if (a[i].size() == 1)
            {
                fout << (char)(Queue.front() % 256);
                Queue.pop();
            }
            else
            {
                fout << (char)(registers[(int)a[i][1] - (int)'a'] % 256);
            }
        }
        else if (a[i][0] == 'J') /// эта команда осуществляет переход на строку с маркером
        {
            string str = a[i]; /// записываем команду в строку
            str.erase(0, 1); /// обнуляем букву J
            for (int j = 0; j < marker.size(); j++) /// ищем в маркерах нужную
                if (marker[j].name == str)
                {
                    i = marker[j].num; /// как только находим счетчик цикла становиться равен индексу маркера
                    break; /// прекращием поиск
                }
        }
        else if (a[i][0] == 'Z') /// если значение регистра = 0, то выполнение программы продолжается с маркера
        {
            if (registers[(int)a[i][1] - (int)'a'] == 0) /// проверяем равен ли регистр нулю
            {
                string str = a[i]; /// читаем команду
                str.erase(0, 2); /// обнуляем первые два симола
                for (int j = 0; j < marker.size(); j++)
                    if (marker[j].name == str) /// ищем в маркерах нужную
                    {
                        i = marker[j].num; /// как только находим счетчик цикла становиться равен индексу маркера
                        break; /// прекращием поиск
                    }
            }
        }
        else if (a[i][0] == 'E') /// если значение двух регистров равны, то выполнение программы продолжается с маркера
        {
            if (registers[(int)a[i][1] - (int)'a'] == registers[(int)a[i][2] - (int)'a']) /// проверка на равность регистров
            {
                string str = a[i];
                str.erase(0, 3); /// обнуляем три лишних первых символа
                for (int j = 0; j < marker.size(); j++)
                    if (marker[j].name == str) /// ищем в маркерах нужную строку
                    {
                        i = marker[j].num; /// как только находим счетчик цикла становиться равен индексу маркера
                        break; /// прекращием поиск
                    }
            }
        }
        else if (a[i][0] == 'G') /// если значение первого регистра больше значения второго, то выполнение программы продолжается с маркера
        {
            if (registers[(int)a[i][1] - (int)'a'] > registers[(int)a[i][2] - (int)'a']) /// проверка условиия, написанного выше
            {
                string str = a[i];
                str.erase(0, 3); /// обнуляем три лишних первых символа
                for (int j = 0; j < marker.size(); j++)
                    if (marker[j].name == str) /// ищем в маркерах нужную
                    {
                        i = marker[j].num; /// как только находим счетчик цикла становиться равен индексу маркера
                        break; /// прекращием поиск
                    }
            }
        }
        else if (a[i][0] == 'Q') /// прекращает работу программы
            break;
        else if (a[i][0] >= '0' && a[i][0] <= '9') /// если встречаем обычное число
        {
            unsigned short int element = 0;
            for (int j = 0; j < a[i].size(); j++)
                element = element * 10 + (int)a[i][j] - (int)'0';
            Queue.push(element);
        }
        i++; /// добовляем к счётчику + 1 для продолжения чтения команд
    }
    fin.close();
    fout.close();
    return 0;
}
