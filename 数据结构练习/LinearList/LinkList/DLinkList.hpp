//双链表比之单链表多了一个指向前一个节点的指针，因此支持逆向检索，但消耗内存比之单链表更大
#pragma once
#include<iostream>
using namespace std;
template<typename T>
struct DNode
{
	T data;
	DNode<T>* prev;
	DNode<T>* next;
	DNode()
	{
		this->data = 0;
		this->prev = nullptr;
		this->next = nullptr;
	}
};
template<class T>
class DLinkList
{
private:
	DNode<T>* head;//头结点
	DNode<T>* tail;//尾结点
	int length;//双链表长度
public:
	DLinkList()
	{
		this->head = new DNode<T>();
		this->tail = new DNode<T>();
		this->head->next = this->tail;
		this->tail->prev = this->head;
		this->length = 0;
	}
	DLinkList(const T arr[], int size,bool TailInsert=true)
	{
		this->head = new DNode<T>();
		this->tail = new DNode<T>();
		this->head->next = this->tail;
		this->tail->prev = this->head;
		this->length = 0;
		DNode<T>* temp = nullptr;
		if (TailInsert)
		{
			//尾插法
			for (int i = 0; i < size; i++)
			{
				temp = new DNode<T>();
				temp->data = arr[i];
				this->length++;
				temp->next = this->tail;
				temp->prev = this->tail->prev;
				this->tail->prev = this->tail->prev->next = temp;
			}
		}
		else
		{
			//头插法
			for (int i = 0; i < size; i++)
			{
				temp = new DNode<T>();
				temp->data = arr[i];
				this->length++;
				temp->prev = head;
				temp->next = head->next;
				head->next = head->next->prev = temp;
			}
		}
		
	}
	~DLinkList()
	{
		DNode<T>* temp = nullptr;
		int DeleteCount = 0;
		while (this->head->next != this->tail)
		{
			temp = this->head->next;
			this->head->next = temp->next;
			delete temp;
			DeleteCount++;
		}
		delete this->head;
		delete this->tail;
		cout << "~DLinkList():";
		cout << "DeleteCount:" << DeleteCount << endl;
		cout << "---------------------------" << endl;
	}
	void ShowList()//输出点链表所有结点的值
	{
		cout << "DLinkList:"<< endl;
		DNode<T>* temp = this->head->next;
		while (temp != this->tail)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << "length:" << this->length << endl;
	}
	void ListInsert(T e, int n)//在链表中插入新结点
	{
		if (n<1 || n>this->length + 1)
		{
			cout << "插入位置越界" << endl;
			return;
		}
		DNode<T>* temp = this->head;
		DNode<T>* new_Node = new DNode<T>();
		new_Node->data = e;
		for (int i = 1; i < n; i++)
		{
			temp = temp->next;
		}
		new_Node->prev = temp;
		new_Node->next = temp->next;
		temp->next = temp->next->prev = new_Node;
		this->length++;
	}
	void ListDelete(int n)//删除单链表中的第n个结点
	{
		if (n<1 || n>this->length)
		{
			cout << "删除位置越界" << endl;
			return;
		}
		DNode<T>* temp = this->head;
		for (int i = 1; i < n; i++)
		{
			temp = temp->next;
		}
		DNode<T>* De_dest = temp->next;
		De_dest->next->prev = temp;
		temp->next = De_dest->next;
		delete De_dest;
		this->length--;
	}
	DNode<T>* LocateElem(T e)//按值查找链表中的结点并返回其指针
	{
		DNode<T>* temp = this->head->next;
		while (temp != this->tail)
		{
			if (temp->data == e)
			{
				cout << temp->data << endl;
				return temp;
			}
			temp = temp->next;
		}
		cout << "单链表中没有" << e << "这个元素" << endl;
		return nullptr;
	}
	int Length()//返回单链表的长度
	{
		return this->length;
	}
	void DestroyList()
	{
		DNode<T>* temp = nullptr;
		if (this->head->next != this->tail)
		{
			while (this->head->next != this->tail)
			{
				temp = this->head->next;
				this->head->next = temp->next;
				delete temp;
				this->length--;
			}
			cout << endl;
		}
		else
		{
			cout << "此表为空表" << endl;
		}
	}
};