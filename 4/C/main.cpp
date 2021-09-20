#include <fstream>
using namespace std;

struct stack_node
{
	int data;
	stack_node* next;
};

class Stack
{
public:
	stack_node* top;
	Stack()
	{
		top = NULL;
	}
	void push(int a)
	{
		stack_node* node = new stack_node();
		node->next = top;
		node->data = a;
		top = node;
	}
	void poop()
	{
		if (!Empty())
		{
			stack_node* del = top;
			top = top->next;
			delete del;
		}
	}
	char getTop()
	{
		return top->data;
	}
	bool Empty()
	{
		if (top == NULL)
		{
			return true;
		}
		return false;
	}

};

string answ(string str1)
{
	Stack stack;
	for (int i = 0; str1[i] != '\0'; i++)
	{
		if (str1[i] == '(' || str1[i] == '[')
		{
			stack.push(str1[i]);
		}
		else
		{
			if (stack.Empty() == false && ((stack.getTop() == '[' && str1[i] == ']') || (stack.getTop() == '(' && str1[i] == ')')))
			{
				stack.poop();
			}
			else
			{
				return "NO";
			}

		}
	}
	if (stack.Empty())
	{
		return "YES";
	}
	else
	{
		return "NO";
	}
}

int main()
{
	ifstream fin("brackets.in");
	ofstream fout("brackets.out");
	string str;
	while (fin >> str)
	{
		fout << answ(str) << endl;
	}
	fin.close();
	fout.close();
	return 0;
}