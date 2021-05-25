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

vector<int> splitToInt(string s)
{
	vector<string> curr = split(s);
	vector<int> result;
	for (string s : curr)
		result.push_back(atoi(s.c_str()));
	return result;
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
	for (Node* it1 = polinom.begin(); it1 != nullptr;)
	{
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
		//cout << "!" << it1->data << ' ' << it1->next->data << endl;
		if (it1->data.pows == it1->next->data.pows)
		{
			it1->data.k += it1->next->data.k;
			it1 = polinom.erase(it1->next);
		}
		else it1 = it1->next;
	}

	deleteEmpty(polinom);
}

void merge(List& l1, List& l2)
{
	for (Node* it1 = l2.begin(); it1 != nullptr; it1 = it1->next)
	{
		l1.push(it1->data);
	}

	check(l1);
}


void add(List& l1, List& l2, List& result)
{
	for (Node* it = l1.begin(); it != nullptr; it = it->next)
		result.push(it->data);

	for (Node* it = l2.begin(); it != nullptr; it = it->next)
		result.push(it->data);

	check(result);
}

bool checkKoeff(int k)
{
	return k > 0 && k < 10;
}

void input(List& l)
{
	while (true)
	{
		Monom m;
		cout << "Введите коэффицент: ";
		cin >> m.k;
		if (!m.k)
			return;
		int x, y, z;

		do {
			cout << "Введите степень при x: ";
			cin >> x;
		} while (!checkKoeff(x));
		
		do {
			cout << "Введите степень при y: ";
			cin >> y;
		} while (!checkKoeff(y));

		do {
			cout << "Введите степень при z: ";
			cin >> z;
		} while (!checkKoeff(z));
		
		m.pows = x * 100 + y * 10 + z;
		l.push(m);
		cout << endl;
	}

	cout << l << endl;
}

int main()
{
	setlocale(LC_ALL, "RUS");

	List p1, p2;

	cout << "1:" << endl;
	input(p1);
	cout << endl << "2:" << endl;
	input(p2);

	cout << endl << endl;

	cout << "Сложение в 3-й полином: " << endl;
	List p3;
	add(p1, p2, p3);
	cout << p1 << " + "<< p2 << " = "<<  p3 << endl;

	cout << endl << endl << "Сложение добавлением в 1-й полином: " << endl;

	merge(p1, p2);

	cout << "1: " << p1 << endl << "2: " << p2 << endl;
	
    return 0;
}
