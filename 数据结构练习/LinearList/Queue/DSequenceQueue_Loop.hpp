//比之顺序循环队列，可以在两端插入/删除
#pragma once
#include<iostream>
using namespace std;
template<class T>
class DQueue_Loop
{
private:
	int front;
	int rear;
	static const int MAXSIZE = 10;
	T data[MAXSIZE];
	int size;
public:
	DQueue_Loop()
	{
		this->front = this->rear = 0;
		this->size = 0;
	}
	DQueue_Loop(const T arr[],int size)
	{
		this->front = this->rear = 0;
		this->size = 0;
		if (size > MAXSIZE) { cout << "没有足够空间存储数据：" << size << endl; return; }
		for (int i = 0; i < size; i++)
		{
			Push_back(arr[i]);
		}
	}
	bool IsEmpty()
	{
		if (this->size == 0)return true;
		return false;
	}
	bool IsFull()
	{
		if (this->size == this->MAXSIZE)return true;
		return false;
	}
	void Push_front(T value)
	{
		if (IsFull())return;
		this->front = (this->front - 1 + this->MAXSIZE) % this->MAXSIZE;
		data[this->front] = value;
		this->size++;
	}
	void Push_back(T value)
	{
		if (IsFull())return;
		data[this->rear] = value;
		this->rear = (this->rear + 1) % this->MAXSIZE;
		this->size++;
	}
	void Pop_front()
	{
		if (IsEmpty())return;
		this->front = (this->front + 1) % this->MAXSIZE;
		this->size--;
	}
	void Pop_back()
	{
		if (IsEmpty())return;
		this->rear = (this->rear - 1 + this->MAXSIZE) % this->MAXSIZE;
		this->size--;
	}
	void Print()
	{
		if (IsEmpty())return;
		int temp = this->front;
		do
		{
			cout << data[temp] << " ";
			temp = (temp + 1) % this->MAXSIZE;
		} while (temp != this->rear);
		cout << endl;
	}
};
