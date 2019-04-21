#include<iostream>
#include<sstream>
#include<cmath>
#include"Stack.cpp"
#include<string.h>
using namespace std;


double Result(NumberStack& number, SignStack& sign, bool flag)
{
	double temp[5] = {0, 0, 0, 0, 0};//have to initialize
	bool check[3] = {false, false, false};
	int count;
	int k;
	char ch;
	for(int i = 0; i < 2; i++)
	{
		count = 0;
		k = 1;
		
		while((number.Pop(ch)) && (ch != '#'))
		{
			if(ch == '.')
				check[i] = true;
			if(!check[i])
				count++;
			temp[i] += (ch - '0')*k;
			k *= 10;
		}
	}

	for(int i = 0; i < 2; i++)
		if(check[i])
			temp[i] /= pow(10, count);
	
	double result;
	sign.Pop(ch);
	switch(ch)
	{
		case '+':
			result = temp[1] + temp[0];
			break;
		case '-':
			result = temp[1] - temp[0];
			break;
	}
	if(flag)
		return result;
	else
	{
		stringstream ss;
		string transform;
		ss << result;
		ss >> transform;
		for(int i = 0; i < transform.length(); i++)
			number.Push(transform[i]);
		cout << transform << endl;

		return result;
	}
}


int main()
{
	NumberStack number;
	SignStack sign;
	string str = "";
	cin >> str;
	sign.Push('#');
	int num = 0;

	while(num != str.length())
	{
		char ch = str[num];
		if((ch >= '0' && ch <= '9') || ch == '.')
		{
			number.Push(ch);
			num++;
			if(num == str.length())
			{
				cout << Result(number, sign, true);
				system("pause");
				return 0;
			}
		}
		else if(ch == '+' || ch == '-')
		{
			if(sign.Compare(ch))
			{
				sign.Push(ch);
				num++;
				number.Push('#');
			}
			else
			{
				Result(number, sign, false);
			}
		}
	}

	system("pause");
	return 0;
}