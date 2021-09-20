#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

int multimap_size = 1000000;
int set_size = 10000;

struct Set
{
    string key;
    vector < vector <string>> values; // множество значений
    Set()
    {
        values.resize(set_size);
    }
};
struct MultiMap // Создаём множество
{
    vector< vector<Set> > set;
    MultiMap()
    {
        set.resize(multimap_size); // задаём размер множеству
    }
};
// ---------------
MultiMap multimap; // инициализируем множество
// ---------------

int fhash(string key, int vector_size) // для хеширование элементов
{
    const int k = 10;
    int hash_code = 0;
    for (int i = 0; i < key.length(); i++)
    {
        hash_code = hash_code * k % vector_size;
        hash_code += (key[i] - 'A' + 1);
        hash_code %= vector_size;
    }
    return hash_code;
}

void put_el(const string& key, const string& value) // Процедура добовление элементов в множество
{
    int hash_key = fhash(key, multimap_size); // хешируем ключ
    for (auto& i : multimap.set[hash_key])
    {
        if (i.key == key) // поиск по хешу ключа
        {
            int hash_value = fhash(value, set_size); // хешируем значение элемента
            for (const auto& j : i.values[hash_value])
                if (j == value)						// Если такое ключ-значение уже есть в нашем множестве
                    return;
            i.values[hash_value].push_back(value);
            return;									// Если данный ключ уже есть в множестве, но данного значения в нём нет
        }
    }
    // Блок: если данного ключ-значения нет в нашем множестве
    Set* new_set = new Set; // создаём множество ключ-значений
    new_set->key = key;	// записываем ключ
    new_set->values[fhash(value, set_size)].push_back(value); // заряжаем значение
    multimap.set[hash_key].push_back(*new_set); // заряжаем получившиеся мн. в мейн_мн.
    delete new_set; // после того как мы зарядили наше мн. удаляем структуру
}

void delete_el(const string& key, const string& value) // Процедура удаления значения для данного ключа
{
    int hash_key = fhash(key, multimap_size); // хешируем ключ
    for (auto& i : multimap.set[hash_key])
    {
        if (i.key == key)
        {
            int hash_value = fhash(value, set_size);            // Поиск удаляемого значения
            for (int j = 0; j < i.values[hash_value].size(); j++)
            {
                if (i.values[hash_value][j] == value)
                {
                    i.values[hash_value].erase(i.values[hash_value].begin() + j); // удаление значения
                    return;
                }
            }
        }
    }
}

void deleteAll_el(const string& key) // Процедура удаления всех значений для данного ключа
{
    int hash_key = fhash(key, multimap_size); // хешируем ключ
    for (auto& i : multimap.set[hash_key])
    {
        if (i.key == key) // ищем ключ
        {
            for (auto& j : i.values) // запускаем цикл для множества значений ключа
            {
                while (!j.empty()) // пока множество не пусто
                    j.pop_back(); // удаляем последнее значение
            }
            return;
        }
    }
}

vector<string> serach_el(const string& key) // Функция поиска всех значений для данного ключа
{
    vector<string> answer; // создаём пустое мн. значений для данного ключа, в который вернём как ответ
    int hash_key = fhash(key, multimap_size); // хешируем ключ
    for (auto& i : multimap.set[hash_key])
    {
        if (i.key == key) // ищем данный ключ
        {
            for (auto& j : i.values) // запускаем цикл для множества значений ключа
                for (const auto& k : j) // запускаем цикл для значений
                    answer.push_back(k); // записываем все значения в ответ
            return answer; // возвращаем ответ
        }
    }
    return answer; // возвращаем ответ
}

int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("multimap.in");
    fout.open("multimap.out");
    while (!fin.eof())
    {
        string cmd;
        fin >> cmd;
        if (cmd == "put")
        {
            string key, value;
            fin >> key >> value;
            put_el(key, value);
        }
        else if (cmd == "delete")
        {
            string key, value;
            fin >> key >> value;
            delete_el(key, value);
        }
        else if (cmd == "deleteall")
        {
            string key;
            fin >> key;
            deleteAll_el(key);
        }
        else if (cmd == "get")
        {
            string key;
            fin >> key;
            vector<string> anw = serach_el(key);
            fout << anw.size() << ' ';
            for (const string& i : anw)
                fout << i << ' ';
            fout << "\n";
        }
    }
    fin.close();
    fin.close();
    return 0;
}