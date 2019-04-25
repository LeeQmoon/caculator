#pragma once
#include<iostream>
#include<string>
using namespace std;

class Stack {

protected:
	char *head;//the head pointer
	int maxsize;//the maxsize of stack
	int size;//the real size of stack

public:
	Stack();
	int GetSize();
	bool Top();
	bool Bottom();//
	bool Pop(char&);//pop out of the stack
	bool Push(char);//push into the stack
	~Stack();

};


class NumberStack :public Stack {

public:
	NumberStack();
};


class SignStack :public Stack {

public:
	SignStack();
	bool Compare(char);//compare the sign with the prio
};
