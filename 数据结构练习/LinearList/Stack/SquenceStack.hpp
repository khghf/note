//�����˳���ֻ������һ�˽��в����ɾ�����������Ա�
//��������
//ջ������������ɾ����һ�ˣ���ӦԪ�ر���Ϊջ��Ԫ��
//ջ�ף�����������ɾ����һ�ˣ���ӦԪ�ر���Ϊջ��Ԫ��
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
			cout << "ջ���޷���ջ" << endl;
			return;
		}
		top++;
		data[top] = value;
	}
	void Pop()
	{
		if (IsEmpty())
		{
			cout << "ջ���޷���ջ" << endl;
			return;
		}
		top--;
	}
	void Print()
	{
		if (top == -1)
		{
			cout << "ջ��";
		}
		int i = top;
		while (i > -1)
		{
			cout << data[i--] << " ";
		}
		cout << endl;
	}
};
