#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;


int fhash(int x) /// функция хеширования
{
    return x = abs(x % 123456);
}

int exists_el(vector< vector<int> >& hash_table, int x) /// функция для проверки есть ли элемент в таблице
{
    int hash = fhash(x);
    for (int i : hash_table[hash]) /// прочесываем массив
    {
        if (i == x)
            return 0; /// в таблице есть число
    }
    return 1; /// в таблице нет числа
}

void insert_el(vector< vector<int> >& hash_table, int x) /// Функция для добавляения элемента
{
    int hash = fhash(x);
    if (exists_el(hash_table, x) == 1) /// добавляем если числа нет в таблице
        hash_table[hash].push_back(x);
}

void delete_el(vector< vector<int> >& hash_table, int x) /// Функция для удаления элемента
{
    int hash = fhash(x);
    for (int i = 0; i < hash_table[hash].size(); i++)
    {
        if (hash_table[hash][i] == x) /// поиск числа
        {
            hash_table[hash].erase(hash_table[hash].begin() + i); /// удаляем число
            break;
        }
    }
}


int main() {
    ifstream fin("set.in");
    ofstream fout("set.out");
    int n = 123456;
    vector < vector<int> > hash_table(n, vector<int>()); // Создаём двумерный вектор, котрый явл. нашей хеш-таблицей
    string cmd;
    int x;
    while (fin)
    {
        fin >> cmd;
        if (!fin.eof())
        {
            if (cmd == "insert")
            {
                fin >> x;
                insert_el(hash_table, x);
            }
            else if (cmd == "delete")
            {
                fin >> x;
                delete_el(hash_table, x);
            }
            else {
                fin >> x;
                if (exists_el(hash_table, x) == 0)
                    fout << "true\n";
                else
                    fout << "false\n";
            }
        }
    }
    return 0;
}
