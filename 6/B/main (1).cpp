#include <fstream>
#include <vector>

using namespace std;

ifstream fin("map.in");
ofstream fout("map.out");

struct key /// структурa для хранения даннных ассоциативного массива
{
    string x;
    string y;
};

int fhash(const string& word) /// хеширование элементов
{
    int hash = 0;
    int k = 5;
    for (int i = 0; i < word.size(); i++)
    {
        int s = 0;
        if (word[i] - 'a' >= 0 && word[i] - 'a' <= 9)
            s = word[i] - 'a';
        else
            s = word[i] - 'A';
        hash = (hash + ((s + 1) * k) % 1234) % 12345;
        k = (k * 5) % 12345;
    }
    return hash;
}

void put_el(vector<vector<key>>& hash_table, const string& key, const string& word) /// Функция добовления элемента в хеш-таблицу
{
    int hash = fhash(key);
    for (auto& i : hash_table[hash])
    {
        if (i.x == key) /// поверяем есть ли ключ в таблице
        {
            i.y = word;
            return;
        }
    }
    hash_table[hash].push_back({ key, word }); /// заряжаем ключ и значение для нужного хеша
}
void get_el(vector<vector<key>>& hash_table, const string& key) /// Функция для поиска значения
{
    int hash = fhash(key);
    for (auto& i : hash_table[hash]) /// ищем значение и выводм его елси находим
    {
        if (i.x == key)
        {
            fout << i.y << endl;
            return;
        }
    }
    fout << "none" << endl; /// если не находим, выводим none
}
void delete_el(vector<vector<key>>& hash_table, const string& key) /// Функция удаления элемента
{
    int hash = fhash(key);
    for (int i = 0; i < hash_table[hash].size(); i++)
    {
        if (hash_table[hash][i].x == key) /// Ищем нужный ключ
        {
            hash_table[hash].erase(hash_table[hash].begin() + i); /// удаляем его
            return;
        }
    }
}
int main()
{
    vector<vector<key>> hash_table(65764, vector<key>());
    string cmd;
    while (fin)
    {
        fin >> cmd;
        if (!fin.eof())
        {
            if (cmd == "put")
            {
                string key, word;
                fin >> key >> word;
                put_el(hash_table, key, word);
            }
            else if (cmd == "get")
            {
                string key;
                fin >> key;
                get_el(hash_table, key);
            }
            else
            {
                string key;
                fin >> key;
                delete_el(hash_table, key);
            }
        }
    }
    return 0;
}