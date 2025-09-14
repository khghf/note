//SequenceList:顺序表
//顺序表(SequenceList)的基本概念
//概念：用一组地址连续的存储单元依次存储线性表的数据元素，这种存储结构的线性表称为顺序表。
//
//特点：逻辑上相邻的数据元素，物理次序也是相邻的。
//只要确定好了存储线性表的起始位置，线性表中任一数据元素都可以随机存取，所以线性表的顺序存储结构是一种随机存取的储存结构，
//因为高级语言中的数组类型也是有随机存取的特性，所以通常我们都使用数组来描述数据结构中的顺序储存结构，用动态分配的一维数组表示线性表。

#pragma once
#include<iostream>
using namespace std;
#define InitSize 10//初始长度
template<class T>
class SqList
{
private:
	T* data;
	int length;
	int MaxSize;//顺序表的最大容量
public:
	//构造函数，分配静态空间
	SqList()
	{
		this->MaxSize = InitSize;
		this->data = new T[InitSize];
		this->length = 0;
		for (int i = 0; i < MaxSize; i++)
		{
			this->data[i] = 0;
		}
	}
	SqList(const T arr[], int size)
	{
		this->MaxSize = InitSize;
		this->data = new T[InitSize];
		this->length = 0;
		for (int i = 0; i < MaxSize; i++)
		{
			this->data[i] = 0;
		}
		if (size > MaxSize)
		{
			T* temp = this->data;
			this->data = new T[size];
			delete temp;
			MaxSize = size;
		}
		for (int i = 0; i < size; i++)
		{
			this->data[i] = arr[i];
			this->length++;
		}
	}
	~SqList()
	{
		delete[]this->data;
	}
	//插入元素，插入范围：头元素至尾元素后一个位置
	void Insert(T n, int dest)
	{
		if (dest<1 || dest>this->length + 1)
		{
			cout << "插入位置越界" << endl;
			return;
		}
		if (length >= MaxSize)
		{
			T* temp = this->data;
			this->data = new T[this->length + 1];
			MaxSize = this->length + 1;
			for (int i = 0; i < this->length; i++)
			{
				this->data[i] = temp[i];
			}
			delete temp;
		}
		int i = this->length;
		while (i >= dest)
		{
			this->data[i] = this->data[i - 1];
			i--;
		}
		this->data[dest - 1] = n;
		this->length++;
	}
	//查找给定元素是否存在，并返回位置
	int LocateElem(T e)
	{
		cin >> e;
		for (int i = 0; i < this->length; i++)
		{
			if (data[i] == e)
			{
				cout << "存在元素" << e << "，其位置为：" << i + 1 << " 下标为：" << i << endl;
				return i + 1;
			}
		}
		//cout << "不存在" << e << "这个元素" << endl;
		return 0;
	}
	//删除表中对应位置的元素元素
	void ListDelete(int dest)
	{
		if (dest<1 || dest>this->length)
		{
			//cout <<"删除位置越界或表为空表" << endl;
			return;
		}
		for (int i = dest; i <= this->length; i++)
		{
			data[i - 1] = data[i];
		}
		this->length--;
	}
	//判断表是否为空
	bool Empty()
	{
		if (this->length == 0)
		{
			//cout << "空" << endl;
			return true;
		}
		else
		{
			cout << "非空" << endl;
			return false;
		}
	}
	//销毁表
	void DestroyList()
	{
		delete[]this->data;
	}
	//输出顺序表
	void ShowList()
	{
		for (int i = 0; i < this->length; i++)
		{
			cout << this->data[i] << " ";
		}
		cout << "length" << this->length << endl;
	}
};
//int main()
//{
//	int arr[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
//	char arr1[] = { 'c','b','d','f' };
//	int size_arr = sizeof(arr) / sizeof(arr[0]);
//	int size_arr1= sizeof(arr1) / sizeof(arr1[0]);
//	SqList<int>L1;
//	SqList<char>L2;
//	L1.CreateList(arr,size_arr);
//	L2.CreateList(arr1, size_arr1);
//	L1.ShowList();
//	L2.ShowList();
//	char data=NULL; int dest;
//	char e='0';
//	while (1)
//	{
//		cin >> dest;
//		L1.ListDelete(dest);
//		L1.ShowList();
//		L1.Empty();
//	}
//}