//����ĵ�����ֻ������һ�˽��в����ɾ�������ĵ�����
//��������
//ջ������������ɾ����һ�ˣ���ӦԪ�ر���Ϊջ��Ԫ��
//ջ�ף�����������ɾ����һ�ˣ���ӦԪ�ر���Ϊջ��Ԫ��
#pragma once
#include<iostream>
using namespace std;
template<class T>
struct LinkStackNode
{
	T data;
	LinkStackNode<T>* next;
	LinkStackNode()
	{
		this->next = nullptr;
	}
};
template<class T>
class LinkStack
{
private:
	LinkStackNode<T>* top;
public:
	LinkStack()
	{
		this->top = nullptr;
	}
	LinkStack(const T arr[], int size)
	{
		this->top = nullptr;
		for (int i = 0; i < size; i++)
		{
			Push(arr[i]);
		}
	}
	~LinkStack()
	{
		LinkStackNode<T>* temp = this->top;
		while (this->top!=nullptr)
		{
			this->top = this->top->next;
			delete temp;
			temp = this->top;
		}
	}
	bool IsEmpty()
	{
		if (this->top == nullptr)return true;
		return false;
	}
	void Push(T value)
	{
		LinkStackNode<T>* temp = new LinkStackNode<T>();
		temp->data = value;
		temp->next = this->top;
		this->top = temp;
	}
	void Pop()
	{
		if (IsEmpty())return ;
		LinkStackNode<T>* temp = this->top;
		this->top = this->top->next;
		delete temp;
	}
	void Print()
	{
		LinkStackNode<T>* temp = this->top;
		while (temp != nullptr)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
};
