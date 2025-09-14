

#pragma once
#include<iostream>
using namespace std;
template<class T>
struct LinkQueueNode
{
	T data;
	LinkQueueNode<T>* next;
	LinkQueueNode(T d) :data(d), next(nullptr) {};
};
template<class T>
class LinkQueue
{
private:
	LinkQueueNode<T>* front;
	LinkQueueNode<T>* rear;
	int length;
public:
	LinkQueue()
	{
		this->front = this->rear = nullptr;
		this->length = 0;
	}
	LinkQueue(const T arr[],int size)
	{
		this->front = this->rear = nullptr;
		this->length = 0;
		for (int i = 0; i < size; i++)
		{
			Push(arr[i]);
		}
	}
	~LinkQueue()
	{
		LinkQueueNode<T>* temp = this->front;
		while (this->front != this->rear)
		{

			this->front = this->front->next;
			delete temp;
			temp = this->front;
		}
		delete this->front;//此时两个指针指向同一块内存只需要delete其中一个
	}
	bool IsEmpty()
	{
		if (this->front == nullptr && this->rear == nullptr)return true;
		return false;
	}
	void Push(T value)
	{
		LinkQueueNode<T>* newNode = new LinkQueueNode<T>(value);
		if (IsEmpty())
		{
			this->front = this->rear = newNode;
		}
		else
		{
			this->rear->next = newNode;
			this->rear = newNode;
		}
		this->length++;
	}
	void Pop()
	{
		if (IsEmpty())return;
		LinkQueueNode<T>* temp = this->front;
		this->front = this->front->next;
		delete temp;
	}
	void Print()
	{
		if (IsEmpty())return;
		LinkQueueNode<T>* temp = this->front;
		do
		{
			cout << temp->data << " ";
			temp = temp->next;
		} while (temp != this->rear);
		cout << temp->data << endl;
	}
};
