//静态链表，使用数组的方式实现链表的功能，由于是用数组实现的改变其
//容量需要涉及拷贝，当容量很大时会消耗很多的系统资源
//头节点不放数据，一般只有不支持指针的语言才会使用静态链表来代替指针链表
#pragma once
using namespace std;
template<typename T>
struct StaticNode
{
	T data;
	int next;
	StaticNode(int Next=-2):next(Next){}//-1表示为尾节点，-2表示该节点空闲
};
#define InitSize_StaticLinkList 10
template<class T>
class StaticLinkList
{
public:
	StaticNode<T>Data[InitSize_StaticLinkList];
	int length;
	StaticLinkList():length(0){}
	StaticLinkList(const T arr[], const int& size)
	{
		for (int i = 0; i < InitSize_StaticLinkList; i++)
		{
			this->Data[i].data = 0;//初始化数据为零
			this->Data[i].next = -2;
		}
		length = 0;
		if (size == 0)return;
		this->Data[0].next = 1;//头节点不放数据
		if (size > InitSize_StaticLinkList - 1)
		{
			cout << "可存储数据空间为：" << InitSize_StaticLinkList - 1 << endl;
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				this->Data[i + 1].data = arr[i];
				this->Data[i + 1].next = i+2;
				length++;

			}
			this->Data[size].next =-1;//最后一个元素标识为尾部
		}
	}
	~StaticLinkList()
	{
		
	}
	void ShowList()
	{
		cout << "StaticLinkList:\n";
		if (length <= 0) { cout << "空表" << endl; return; }
		int index = 0;
		while (Data[index].next != -1)
		{  
			index = Data[index].next;
			cout << "index:" << index << " ";
			cout << "data:" << Data[index].data << " ";
			cout << "next:" << Data[index].next << endl;
		}
		cout << Data[index+1].data << " ";
		cout << endl;
	}
	void ShowAllNode()
	{
		int i = 0;
		while (i<InitSize_StaticLinkList)
		{
			
			cout << "index:" << i << " ";
			cout << "data:" << Data[i].data << " ";
			cout << "next:" << Data[i].next << endl;
			i++;
		}
	}
	void Insert(const int& Location, const T& Value)
	{
		if (length >= InitSize_StaticLinkList-1) { cout << "表已满无法插入" << endl; return; }
		int index = 0;//最终值为要插入位置的前一个位置索引，注意是链表结构
		for (int i = 0; i < Location-1; i++)
		{
			index = Data[index].next;
		}
		int EmptyIndex = FindEmptyIndex();
		if (EmptyIndex != -1)
		{
			Data[EmptyIndex].data = Value;
			Data[EmptyIndex].next = Data[index].next;
			Data[index].next = EmptyIndex;
		}
	}
	int FindEmptyIndex()
	{
		for (int i = 1; i < InitSize_StaticLinkList; i++)
		{
			if (this->Data[i].next == -2)return i;
		}
		return -1;
	}
};

