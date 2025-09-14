#pragma once
#include<iostream>
#include"DLinkList.hpp"
using namespace std;
template<class T>
class DLinkList_Loop
{
private:
	DNode<T>* head;
	DNode<T>* tail;
	int length;
public:
	DLinkList_Loop()
	{
		this->head = new DNode<T>();
		this->tail = new DNode<T>();
		this->head->prev = this->tail;
		this->head->next = this->tail;
		this->tail->prev = this->head;
		this->tail->next = this->head;
		this->length = 0;
	}
	DLinkList_Loop(const T arr[], int size)
	{
		this->head = new DNode<T>();
		this->tail = new DNode<T>();
		this->head->prev = this->tail;
		this->head->next = this->tail;
		this->tail->prev = this->head;
		this->tail->next = this->head;
		this->length = 0;

		int i = 0;
		while (i < size)
		{
			DNode<T>*temp = new DNode<T>();
			temp->data = arr[i++];
			temp->next = this->tail;
			temp->prev = this->tail->prev;
			this->tail->prev->next = temp;
			this->tail->prev = temp;
		}
		length = i;
	}
	~DLinkList_Loop()
	{
		DNode<T>*temp= this->head->next;
		int DeleteCount = 0;
		while (temp!=this->tail)
		{
			this->head->next = temp->next;
			delete temp;
			temp = this->head->next;
			DeleteCount++;
		}
		cout << "~DLinkList_Loop():";
		cout << "DeleteCount:" << DeleteCount << endl;
		cout << "---------------------------" << endl;
	}
	void ShowListN()
	{
		cout << "后驱输出：";
		DNode<T>* temp = this->head->next;
		while (temp!=this->tail)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << "length:" << this->length << endl;
	}
	void ShowListP()
	{
		cout << "前驱输出：";
		DNode<T>* temp = this->tail->prev;
		while (temp != this->head)
		{
			cout << temp->data << " ";
			temp = temp->prev;
		}
		cout << "length:" << this->length << endl;
	}
	void Insert(int index, T value)
	{
		if (index<1 || index>this->length)
		{
			cout << "超出插入范围" << endl;
			return;
		}
		int i = 0;
		DNode<T>* temp = this->head;
		while (i < index )
		{
			temp = temp->next;
			i++;
		}
		DNode<T>* newNode = new DNode<T>();
		newNode->data = value;
		newNode->prev = temp->prev;
		newNode->next = temp;
		temp->prev = temp->prev->next=newNode;
		this->length++;
	}
};