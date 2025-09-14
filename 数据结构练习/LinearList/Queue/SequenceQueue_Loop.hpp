//���У�Queue����ֻ������һ�˽��в��룬����һ��ɾ�������Ա�
//��ͷ������ɾ����һ�ˣ���Ӧ��Ԫ�ر���Ϊ��ͷԪ��
//��β����������һ�ˣ���Ӧ��Ԫ�ر���Ϊ��βԪ��
//���е��ص㣺�Ƚ��ȳ�First In First Out��FIFO��

//�ж϶������� / �ѿ�
//
//����1����Ҫ����һ���洢�ռ�
//��������������βָ�������һ��λ���Ƕ�ͷ����(Q.rear + 1) % MaxSize == Q.front
//�ӿ�������Q.rear == Q.front

//����2������Ҫ����һ���洢�ռ�
//������һ��size�������������Ԫ�ظ���

//����3������Ҫ����һ���洢�ռ�
//ÿ��ɾ�������ɹ�ʱ������tag = 0��
//ÿ�β�������ɹ�ʱ������tag = 1��
//����������front == rear && tag == 1
//�ӿ�������front == rear && tag == 0
#pragma once
#include<iostream>
using namespace std;
template<class T>
class SQueue_Loop
{
private:
	static const int MAXSIZE = 10;
	T data[MAXSIZE];
	int front;//��ͷԪ���±�
	int rear;//��β�±�ĺ�һ��λ��
	int size;//Ԫ�ظ��������ж϶��е���/��
	
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
		if (size > MAXSIZE) { cout << "û���㹻�ռ�洢���ݣ�" << size << endl; return; }
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
		this->rear = (this->rear + 1) % this->MAXSIZE;//ʵ���˶���ѭ��
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
