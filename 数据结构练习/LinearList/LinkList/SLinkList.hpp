//SLinkList:单链表
//单链表由一个个节点组成，节点里面包含了数据和指向下一个节点的指针，所以单链表的数据之间是不相邻的，这意味着单链表的查找比顺序表慢，
//因为顺序表可以直接通过目标元素下标、第一个元素地址、数据类型大小(字节)计算出指定下标元素的地址：
//目标元素地址=第一个元素地址+数据类型大小*目标元素下标	
//而单链表无法这样做，因为单链表的数据不在一块连续的内存中，并且单链表的节点还要额外存储一个指针需要的空间更多
//但是删除，插入比顺序表快
// 
//对比
//顺序表：
//每个结点中只存放数据元素
//优点：可随机存取，存储密度高
//缺点：要求大片连续空间，改变容量不方便
// 
//单链表：
//每个结点除了存放数据元素外，还要存储指向下一个结点的指针
//优点：不要求大片连续空间，改变容量方便
//缺点：不可随机存取，要耗费一定空间存放指针
#pragma once
#include<iostream>
using namespace std;
template<typename T>
struct SNode
{
	T data;
	SNode<T>* next;
	SNode()
	{
		this->data = 0;
		this->next = nullptr;
	}
};
template<class T>
class SLinkList
{
protected:
	SNode<T>* head;//头结点
	int length;//单链表长度
public:
	SLinkList()
	{
		this->head = new SNode<T>();
		this->length = 0;
	}
	SLinkList(const T arr[], int size,bool TailInsert=true)
	{
		//int size = ;
		this->head = new SNode<T>();
		this->length = 0;
		SNode<T>* temp = this->head;
		if (TailInsert)
		{
			//尾插法
			for (int i = 0; i < size; i++)
			{
				temp->next = new SNode<T>();
				this->length++;
				temp->next->data = arr[i];
				temp = temp->next;
			}
		}
		else
		{
			//头插法
			for (int i = 0; i < size; i++)
			{
				temp = new SNode<T>();
				this->length++;
				temp->data = arr[i];
				temp->next = head->next;
				head->next = temp;
			}
		}
	}
	~SLinkList()
	{
		SNode<T>* temp = nullptr;
		int DeleteCount = 0;
		while (this->head->next != nullptr)
		{
			temp = this->head->next;
			this->head->next = temp->next;
			delete temp;
			DeleteCount++;
		}
		delete this->head;
		cout << "~SLinkList():";
		cout << "DeleteCount:" << DeleteCount << endl;
		cout << "---------------------------" << endl;

	}
	void ShowList()//输出点链表所有结点的值
	{
		cout << "SLinkList:" << endl;
		SNode<T>* temp = this->head->next;
		while (temp != nullptr)
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
		SNode<T>* temp = this->head;
		SNode<T>* new_SNode = new SNode<T>();
		new_SNode->data = e;
		for (int i = 1; i < n; i++)
		{
			temp = temp->next;
		}
		new_SNode->next = temp->next;
		temp->next = new_SNode;
		this->length++;
	}
	void ListDelete(int n)//删除单链表中的第n个结点
	{
		if (n<1 || n>this->length)
		{
			cout << "删除位置越界" << endl;
			return;
		}
		SNode<T>* temp = this->head;
		for (int i = 1; i < n; i++)
		{
			temp = temp->next;
		}
		SNode<T>* De_dest = temp->next;
		temp->next = De_dest->next;
		delete De_dest;
		this->length--;
	}
	SNode<T>* LocateElem(T e)//按值查找链表中的结点并返回其指针
	{
		SNode<T>* temp = this->head->next;
		while (temp != nullptr)
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
		SNode<T>* temp = nullptr;
		if (this->head->next != nullptr)
		{
			while (this->head->next != nullptr)
			{
				temp = this->head->next;
				this->head->next = temp->next;
				delete temp;
				this->length--;
			}
		}
		else
		{
			cout << "q" << endl;
		}
	}
};
//int main()
//{
//	int arr[] = { 1,2,3,4,5,6,7,8,9,0 };
//	int size_arr = sizeof(arr) / sizeof(arr[0]);
//	LinkList<int>LA;
//	LA.CreateList(arr, size_arr);
//	LA.ShowList();
//	int data, dest;
//	LA.DestroyList();
//	LA.DestroyList();
//	return 0;
//}