#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "List.h"
#include <algorithm>

using namespace std;

vector<string> split(string str)
{
	vector<string> vec;
	for (int beg = 0, end = 0; end != str.size(); end++)
	{
		if (str[end] == ' ')
		{
			vec.push_back(str.substr(beg, end - beg).c_str());
			beg = ++end;
		}

		if (end == str.size() - 1)
		{
			vec.push_back(str.substr(beg, end - beg + 1).c_str());
			break;
		}

	}

	return vec;

}



void stringToPolinom(string s, List& result)
{
	vector<string> monoms = split(s);
	bool isMinus = false;
	for (string str : monoms)
	{
		if (str == "+")
		{
			isMinus = false;
			continue;
		}
		if (str == "-")
		{
			isMinus = true;
			continue;
		}

		Monom m;
		vector<int> pows;
		m.k = atoi(str.c_str());
		if (m.k == 0)
			continue;
		for (auto it = str.rbegin(); it != str.rend(); it++)
		{
			if (isdigit(*it))
			{
				pows.push_back(*it - '0');
			}
			if (pows.size() == 3)
				break;
		}

		m.pows = pows[0] + 10 * pows[1] + 100 * pows[2];
		if (isMinus)
			m.k = -m.k;
		result.push(m);

	}
}

void deleteEmpty(List& polinom)
{
	cout << "DE" << endl;
	for (Node* it1 = polinom.begin(); it1 != nullptr;)
	{
		cout << "Size " << polinom.getSize() << endl;
		cout << polinom << endl;
		cout << "Curr: " << it1->data << endl;
		if (it1->data.k == 0)
		{
			it1 = polinom.erase(it1);
		}
		else it1 = it1->next;
		
	}
}

void check(List& polinom)
{
	for (Node* it1 = polinom.begin(); it1->next != nullptr;)
	{
		cout << "!" << it1->data << ' ' << it1->next->data << endl;
		if (it1->data.pows == it1->next->data.pows)
		{
			it1->data.k += it1->next->data.k;
			it1 = polinom.erase(it1->next);
		}
		else it1 = it1->next;
	}

	cout << "CE";
	deleteEmpty(polinom);
}

void merge(List& l1, List& l2)
{
	for (Node* it1 = l2.begin(); it1 != nullptr; it1 = it1->next)
	{
		l1.push(it1->data);
	}

	check(l1);
	cout << endl << "END";
}

int main()
{
	setlocale(LC_ALL, "RUS");

	List p1, p2;

	string str;

	cout << "1: " << endl;
	getline(cin, str);
	stringToPolinom(str, p1);

	cout << "2: " << endl;
	getline(cin, str);
	stringToPolinom(str, p2);

	cout << endl << "Before merge" << endl;

	merge(p1, p2);

	cout << endl << endl << "Result: " << endl << p1;
	
    return 0;
}
