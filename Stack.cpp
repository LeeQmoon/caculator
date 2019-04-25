#include"Stack.h"
#include<iostream>
using namespace std;

Stack::Stack(){
	maxsize = 100;
	head = new char[100];
	size = 0;
}


void Stack::Print(){
	for (int i = 0; i < size; i++)
		cout << head[i] << " ";
	cout << endl;
}


bool Stack::Bottom(){
	if (size == 0)
		return true;
	else
		return false;
}


bool Stack::Top(){
	if (size > maxsize)
		return true;
	else
		return false;
}


bool Stack::Pop(char& ch){
	if (this->Bottom()){
		//cout << "The stack is on the bottom!" << endl;
		return false; 
	}
	else{
		ch = head[--size];
		return true;
	}
}


bool Stack::Push(char ch){
	if (this->Top()){
		//cout << "The size of the stack has reached the maxsize!" << endl;
		return false;
	}
	else{
		head[size++] = ch;
		return true;
	}
}


int Stack::GetSize(){
	return size;
}


Stack::~Stack(){
	delete []head;
}


NumberStack::NumberStack(){
	
}


SignStack::SignStack(){

}


bool SignStack::Compare(char ch){
	if((ch == '+' || ch == '-') && (head[size-1] == '#' || head[size-1] == '('))
		return true;
	else if((ch == '*' && (head[size-1] != '*' && head[size-1] != '/')) ||
	        (ch == '/' && (head[size-1] != '*' && head[size-1] != '/')))
			return true;
			
	return false;
}


