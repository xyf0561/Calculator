
#include "pch.h"
#include <iostream>
#include<cstdio>  
#include<string>  
#include<stack>  
#include<map>
using namespace std;

bool toPostfix();
void postfixValue();
bool dealWithExpree(const string& a);
bool appearAssignmentExpression(const string& a);
bool dealWithInput(string& InfixStr, string& PostfixStr);

stack<string> s;
stack<double> numStack;

map<char, string> map_table;

int len1, len2, len, i, j;
string InfixStr;
string PostfixStr;
string tempInfixStr;

int first = 0, now = 0;

int main()
{
	while (true) {
		if (!toPostfix())
			continue;
		postfixValue();

		cout << "Result:" << numStack.top() << endl << endl;
	}
	system("pause");
}

bool toPostfix() {
	getline(cin, InfixStr);
	if (InfixStr.length() == 0)
		return false;
	if (InfixStr == "$$")
		return 0;

	if (appearAssignmentExpression(InfixStr))
	{
		if (dealWithExpree(InfixStr))
			return false;
		else
			cout << "不合法，请输入正确语句";
	}
	tempInfixStr = InfixStr;
	InfixStr.clear();
	dealWithInput(tempInfixStr, InfixStr);

	len1 = InfixStr.length();

	PostfixStr.clear();
	for (i = 0; i < len1; i++) {
		while (true)
		{
			if (InfixStr[i] != ' ' || InfixStr[i] == NULL)
			{

				break;
			}
			else
				i++;
		}
		first = i;
		if (InfixStr[i] >= '0' && InfixStr[i] <= '9')
		{
			while (true)
			{
				i++;
				if (InfixStr[i] == NULL)
					break;
				if (InfixStr[i] == ' ')
					break;
			}
			PostfixStr.append(InfixStr, first, i - first);
			PostfixStr.append(" ");
		}
		else {
			if (s.size() == 0 || InfixStr[i] == '(')
				s.push(string(InfixStr, i, 1));
			else {
				string tmp1 = s.top();
				if (InfixStr[i] == ')') {
					len = s.size();
					while (len) {
						string tmp = s.top();
						s.pop();
						if (tmp == "(")
							break;
						else
						{
							PostfixStr.append(tmp);
							PostfixStr.append(" ");
						}
						len--;
					}
				}
				else {
					if (tmp1 == "*" || tmp1 == "/") {
						if (InfixStr[i] == '*' || InfixStr[i] == '/')
							s.push(string(InfixStr, i, 1));
						else {
							len = s.size();
							while (len) {
								string tmp = s.top();
								PostfixStr.append(tmp);
								PostfixStr.append(" ");
								s.pop();
								len--;
							}
							s.push(string(InfixStr, i, 1));
						}
					}
					else {
						s.push(string(InfixStr, i, 1));
					}
				}
			}
		}
	}
	if (s.size() != 0) {
		len = s.size();
		while (len) {
			string tmp = s.top();
			PostfixStr.append(tmp);
			PostfixStr.append(" ");
			s.pop();
			len--;
		}
	}
	return true;
}

void postfixValue() {
	double temp1, temp2, temp3;
	len2 = PostfixStr.length();
	first = 0;
	for (i = 0; i < len2 - 1; i++) {
		while (true)
		{
			if (PostfixStr[i] != ' ' || PostfixStr[i] == NULL)
			{

				break;
			}
			else
				i++;
		}
		first = i;
		if (PostfixStr[i] >= '0' && PostfixStr[i] <= '9') {
			{
				while (true)
				{
					i++;
					if (PostfixStr[i] == NULL)
						break;
					if (PostfixStr[i] == ' ')
						break;
				}
			}
			string temp;
			temp.append(PostfixStr, first, i - first);
			double t = atof(temp.c_str());
			numStack.push(t);
		}
		else {
			temp1 = numStack.top();
			numStack.pop();
			temp2 = numStack.top();
			numStack.pop();
			if (PostfixStr[i] == '+') {
				temp3 = temp2 + temp1;
			}
			else if (PostfixStr[i] == '-') {
				temp3 = temp2 - temp1;
			}
			else if (PostfixStr[i] == '*') {
				temp3 = temp2 * temp1;
			}
			else if (PostfixStr[i] == '/') {
				temp3 = temp2 / temp1;
			}
			numStack.push(temp3);
		}
	}
}


bool dealWithInput(string& InfixStr, string& PostfixStr)
{
	int first = 0, now = 0, i = 0;

	for (; i < InfixStr.length(); i++)
	{
		if (InfixStr[i] == '(')
		{
			first = i + 1;
			PostfixStr.append(InfixStr, i, 1);
			PostfixStr.append(" ");
			continue;
		}
		if (InfixStr[i] == ')'  && i != InfixStr.length() - 1)
		{
			if ((InfixStr[first] <= 'z' && InfixStr[first] >= 'a') || (InfixStr[first] >= 'A' && InfixStr[first] <= 'Z'))
			{
				char a = InfixStr[first];
				map<char, string>::iterator iter;
				iter = map_table.find(a);
				if (iter == map_table.end())
					return false; 
				else
				{
					PostfixStr.append(iter->second);
					PostfixStr.append(" ");
				}
			}
			else
			{
				PostfixStr.append(InfixStr, first, i - first);
				PostfixStr.append(" ");

			}

			PostfixStr.append(InfixStr, i, 1);
			first = i + 1;
			continue;
		}

		if ((InfixStr[i] == '*') || (InfixStr[i] == '+') || (InfixStr[i] == '/') || InfixStr[i] == '-')
		{
			if ((InfixStr[first] <= 'z' && InfixStr[first] >= 'a') || (InfixStr[first] >= 'A' && InfixStr[first] <= 'Z')) 
			{
				char a = InfixStr[first];
				map<char, string>::iterator iter;
				iter = map_table.find(a);
				if (iter == map_table.end())
					return false; 
				else
				{
					PostfixStr.append(iter->second);
					PostfixStr.append(" ");

					PostfixStr.append(InfixStr, i, 1); 
					PostfixStr.append(" ");
					first = i + 1;
				}


			}
			else
			{
				PostfixStr.append(InfixStr, first, (i - first));
				PostfixStr.append(" ");
				PostfixStr.append(InfixStr, i, 1);
				PostfixStr.append(" ");
				first = i + 1;
			}

		}
	}

	if (((InfixStr[first] <= 'z' && InfixStr[first] >= 'a') || (InfixStr[first] >= 'A' && InfixStr[first] <= 'Z')) && 
		InfixStr[InfixStr.length() - 1] == ')')  
	{
		char a = InfixStr[first];
		map<char, string>::iterator iter;
		iter = map_table.find(a);
		if (iter == map_table.end())
			return false;  
		else
		{
			PostfixStr.append(iter->second);
			PostfixStr.append(" ");
			PostfixStr.append(")");
		}
	}
	else if ((InfixStr[first] <= 'z' && InfixStr[first] >= 'a') || (InfixStr[first] >= 'A' && InfixStr[first] <= 'Z'))
	{
		char a = InfixStr[first];
		map<char, string>::iterator iter;
		iter = map_table.find(a);
		if (iter == map_table.end())
			return false;
		else
		{
			PostfixStr.append(iter->second);
		}
	}
	else if (InfixStr[InfixStr.length() - 1] == ')')
	{
		PostfixStr.append(InfixStr, first, InfixStr.length() - first - 1);
		PostfixStr.append(" ");
		PostfixStr.append(")");

	}
	else
	{
		PostfixStr.append(InfixStr, first, InfixStr.length() - first);
	}

	return true;

}

bool  appearAssignmentExpression(const string& a)
{
	int i = 0;
	for (; i < a.length(); i++)
	{
		if ((a[i] <= 'z' && a[i] >= 'a') || (a[i] >= 'A' && a[i] <= 'Z'))
		{
			break;
		}
	}

	if (i == a.length() || i + 1 == a.length())
		return false;
	if ((a[i + 1] == '=') || (a[i + 2] == '=')) 
		return true;
	else
		return false;
}


bool dealWithExpree(const string& a)  
{
	int i = 0;
	char x;
	string num;
	for (; i < a.length(); i++)
	{
		if ((a[i] <= 'z' && a[i] >= 'a') || (a[i] >= 'A' && a[i] <= 'Z'))
		{
			x = a[i];
			i++;
			for (; i < a.length(); i++)
			{
				if (a[i] == ' ')
					continue;
				if (a[i] == '=')
				{
					if (i + 1 < a.length())
					{
						num.append(a, i + 1, (a.length() - (i + 1)));
						break;
					}
					else
						return false;
				}
				else
					return false;

			}
			if (i == (a.length() + 1))
				return false;
			else
			{
				map_table[x] = num;
				return true;
			}

		}

	}
}
