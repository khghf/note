//特殊的顺序表：只允许在一端进行插入或删除操作的线性表
//特殊名词
//栈顶：允许插入和删除的一端，对应元素被称为栈顶元素
//栈底：不允许插入和删除的一端，对应元素被称为栈底元素
#pragma once
#include<iostream>
using namespace std;
template<class T>
class SeqStack
{
private:
	static const int MAXSIZE = 10;
	T data[MAXSIZE];
	int top;
public:
	SeqStack()
	{
		this->top = -1;
	}
	SeqStack(const T arr[],int size)
	{
		this->top = -1;
		for (int i = 0; i < size; i++)
		{
			Push(arr[i]);
		}
	}
	bool IsEmpty()
	{
		if (top == -1)return true;
		return false;
	}
	bool IsFull()
	{
		if (top == this->MAXSIZE - 1)return true;
		return false;
	}
	void Push(T value)
	{
		if (IsFull())
		{
			cout << "栈满无法入栈" << endl;
			return;
		}
		top++;
		data[top] = value;
	}
	void Pop()
	{
		if (IsEmpty())
		{
			cout << "栈空无法出栈" << endl;
			return;
		}
		top--;
	}
	void Print()
	{
		if (top == -1)
		{
			cout << "栈空";
		}
		int i = top;
		while (i > -1)
		{
			cout << data[i--] << " ";
		}
		cout << endl;
	}
};
