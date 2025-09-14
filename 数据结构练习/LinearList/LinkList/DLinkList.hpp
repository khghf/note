//˫�����֮���������һ��ָ��ǰһ���ڵ��ָ�룬���֧������������������ڴ��֮���������
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
	DNode<T>* head;//ͷ���
	DNode<T>* tail;//β���
	int length;//˫������
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
			//β�巨
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
			//ͷ�巨
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
	void ShowList()//������������н���ֵ
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
	void ListInsert(T e, int n)//�������в����½��
	{
		if (n<1 || n>this->length + 1)
		{
			cout << "����λ��Խ��" << endl;
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
	void ListDelete(int n)//ɾ���������еĵ�n�����
	{
		if (n<1 || n>this->length)
		{
			cout << "ɾ��λ��Խ��" << endl;
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
	DNode<T>* LocateElem(T e)//��ֵ���������еĽ�㲢������ָ��
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
		cout << "��������û��" << e << "���Ԫ��" << endl;
		return nullptr;
	}
	int Length()//���ص�����ĳ���
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
			cout << "�˱�Ϊ�ձ�" << endl;
		}
	}
};