//队列（Queue）是只允许在一端进行插入，在另一端删除的线性表
//队头：允许删除的一端，对应的元素被称为队头元素
//队尾：允许插入的一端，对应的元素被称为队尾元素
//队列的特点：先进先出First In First Out（FIFO）

//判断队列已满 / 已空
//
//方案1：需要牺牲一个存储空间
//已满的条件：队尾指针的再下一个位置是队头，即(Q.rear + 1) % MaxSize == Q.front
//队空条件：Q.rear == Q.front

//方案2：不需要牺牲一个存储空间
//多声明一个size变量来保存队列元素个数

//方案3：不需要牺牲一个存储空间
//每次删除操作成功时，都令tag = 0；
//每次插入操作成功时，都令tag = 1；
//队满条件：front == rear && tag == 1
//队空条件：front == rear && tag == 0
#pragma once
#include<iostream>
using namespace std;
template<class T>
class SQueue_Loop
{
private:
	static const int MAXSIZE = 10;
	T data[MAXSIZE];
	int front;//队头元素下标
	int rear;//队尾下表的后一个位置
	int size;//元素个数用来判断队列的满/空
	
public:
	SQueue_Loop()
	{
		this->front = this->rear = 0;
		this->size = 0;
	}
	SQueue_Loop(const T arr[],int size)
	{
		this->front = this->rear = 0;
		this->size = 0;
		if (size > MAXSIZE) { cout << "没有足够空间存储数据：" << size << endl; return; }
		for (int i = 0; i < size; i++)
		{
			Push(arr[i]);
			//cout << "this->rear" << this->rear << endl;
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
	void Push(T value)
	{
		if (IsFull())return;
		data[this->rear] = value;
		this->size++;
		this->rear = (this->rear + 1) % this->MAXSIZE;//实现了队列循环
	}
	void Pop()
	{
		if (IsEmpty())return;
		this->front = (this->front + 1) % this->MAXSIZE;
		this->size--;
	}
	void Print()
	{
		if (IsEmpty())return;
		int i = this->front;
		do
		{
			cout << data[i] << " ";
			i = (i + 1) % this->MAXSIZE;
		} while (i != this->rear);
		cout << endl;
	}
};
