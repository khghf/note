//堆一颗特殊的完全二叉树其任意一个结点的值都大于(大根堆)或小于(小根堆)其子结点的值
// 完全二叉树
//除了最后一层外，每一层都被完全填满，并且最后一层的结点为从左向右连续的排列，
//从上至下，从左至右给每个结点编号时都能与满二叉树对应
//	特性：	
//		按层序从1 开始编号，结点i 的左孩子为2i，右孩子为2i + 1；结点i 的父结点为 i / 2 （如果有的话）
//		按层序从0 开始编号，结点i 的左孩子为2i+1，右孩子为2i + 2；结点i 的父结点: 左结点(下标为奇数)为：i / 2 右结点(下表为偶数)为：i / 2-1 （如果有的话）
//		
//	i≤ n / 2 为分支结点， i > n / 2 为叶子结点
//插入操作
//	一、插入数组
//	二、与父结点比较若不满足大/小堆顶的性质则将两者交换
//	三、将父节点变为插入结点与其父节点比较，直到不在需要进行交换或者没有父节点为止
// 另一种方法:直接对数组进行操作，从最后一个非叶子结点开始向前执行下沉操作直到执行完根结点的下沉操作,且每次下沉一个结点要对被交换的结点也进行递归下沉
//删除操作
//一、拿数组末尾的元素代替堆顶元素
//二、从根结点开始和左右孩子结点比较若不满足大/小堆顶的性质则交换，直至满足要求或者没有孩子结点为止
#pragma once
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
template<class T>
class Heap
{
private:
	bool bMinHeap;
protected:
	vector<T>data;
	const int reservrSize = 50;
public:
	Heap(bool bMinHeap=true):bMinHeap(bMinHeap){
		data.reserve(reservrSize);
	}
	Heap(const T arr[], int size, bool bMinHeap = true) :bMinHeap(bMinHeap)
	{
		data.reserve(reservrSize);
		for (int i = 0; i < size; i++)
		{
			//Insert(arr[i]);
			data.push_back(arr[i]);
		}
		int curindex = data.size() - 1;
		if (curindex % 2 == 0)curindex = curindex / 2 - 1;
		else curindex = curindex / 2;
		while (curindex >= 0)
		{
			SiftDown(curindex);
			curindex--;
		}
	}
	void Insert(const T& value)
	{
		data.push_back(value);
		int selfIndex = data.size() - 1;
		SiftUp(selfIndex);
		return true;
	}
	void Pop()
	{
		if (data.size() == 0)return;
		if (data.size() == 1) { data.pop_back(); return; }
		const T tailvalue = *(data.end() - 1);
		data[0] = tailvalue;
		data.pop_back();
		SiftDown(0);
	}
	void Print()
	{
		for (auto in : data)
		{
			cout << in << " ";
		}
		cout << endl;
	}
	void Sort()
	{
		int size = data.size();
		for (int i = 0; i < size; i++)
		{
			T value = data[0];
			const T tailvalue = data[size - i - 1];
			data[0] = tailvalue;
			AdjustForSort(0, size - i-1);
			data.push_back(value);
		}
		data.erase(data.begin(), data.begin() + data.size() / 2);
	}
protected:
	void SiftUp(const int& index)
	{
		if (index == 0)return;
		int parentIndex =0;
		if (index % 2 == 0) parentIndex = index / 2 - 1;
		else parentIndex = index / 2;
		if (bMinHeap)
		{
			//小根推
			if (data[parentIndex] > data[index])
			{
				T temp = data[parentIndex];
				data[parentIndex] = data[index];
				data[index] = temp;
				SiftUp(parentIndex);
			}
		}
		else
		{
			//大根堆
			if (data[parentIndex] < data[index])
			{
				T temp = data[parentIndex];
				data[parentIndex] = data[index];
				data[index] = temp;
				SiftUp(parentIndex);
			}
		}
	}
	void SiftDown(const int& index)
	{
		if (index > data.size())return;
		int leftindex = index * 2 + 1;
		int rightindex = index * 2 + 2;
		if (bMinHeap)
		{
			//小根堆
			if (leftindex < data.size())
			{
				if (rightindex < data.size())
				{
					if (data[leftindex] < data[rightindex])
					{
						if (data[index] > data[leftindex])
						{
							T temp = data[index];
							data[index] = data[leftindex];
							data[leftindex] = temp;
							SiftDown(leftindex);
						}
					}
					else
					{
						if (data[index] > data[rightindex])
						{
							T temp = data[index];
							data[index] = data[rightindex];
							data[rightindex] = temp;
							SiftDown(rightindex);
						}
					}
				}
				else
				{
					if (data[index] > data[leftindex])
					{
						T temp = data[index];
						data[index] = data[leftindex];
						data[leftindex] = temp;
						SiftDown(leftindex);
					}
				}
			}
		}
		else
		{
			//大根堆
			if (leftindex < data.size())
			{
				if (rightindex < data.size())
				{
					if (data[leftindex] > data[rightindex])
					{
						if (data[index] < data[leftindex])
						{
							T temp = data[index];
							data[index] = data[leftindex];
							data[leftindex] = temp;
							SiftDown(leftindex);
						}
					}
					else
					{
						if (data[index] < data[rightindex])
						{
							T temp = data[index];
							data[index] = data[rightindex];
							data[rightindex] = temp;
							SiftDown(rightindex);
						}
					}
				}
				else
				{
					if (data[index] < data[leftindex])
					{
						T temp = data[index];
						data[index] = data[leftindex];
						data[leftindex] = temp;
						SiftDown(leftindex);
					}
				}
			}
		}

	}
	void AdjustForSort(const int& index, int size)
	{
		int leftindex = index * 2 + 1;
		int rightindex = index * 2 + 2;
		if (bMinHeap)
		{
			//小根堆
			if (leftindex < size)
			{
				if (rightindex < size)
				{
					if (data[leftindex] < data[rightindex])
					{
						if (data[index] > data[leftindex])
						{
							T temp = data[index];
							data[index] = data[leftindex];
							data[leftindex] = temp;
							AdjustForSort(leftindex, size);
							return;
						}
					}
					else
					{
						if (data[index] > data[rightindex])
						{
							T temp = data[index];
							data[index] = data[rightindex];
							data[rightindex] = temp;
							AdjustForSort(rightindex, size);
							return;
						}
					}
				}
				else
				{
					if (data[index] > data[leftindex])
					{
						T temp = data[index];
						data[index] = data[leftindex];
						data[leftindex] = temp;
						AdjustForSort(leftindex, size);
						return;
					}
				}
			}
		}
		else
		{
			//大根堆
			if (leftindex < size)
			{
				if (rightindex < size)
				{
					if (data[leftindex] > data[rightindex])
					{
						if (data[index] < data[leftindex])
						{
							T temp = data[index];
							data[index] = data[leftindex];
							data[leftindex] = temp;
							AdjustForSort(leftindex, size);
							return;
						}
					}
					else
					{
						if (data[index] < data[rightindex])
						{
							T temp = data[index];
							data[index] = data[rightindex];
							data[rightindex] = temp;
							AdjustForSort(rightindex, size);
							return;
						}
					}
				}
				else
				{
					if (data[index] < data[leftindex])
					{
						T temp = data[index];
						data[index] = data[leftindex];
						data[leftindex] = temp;
						AdjustForSort(leftindex, size);
						return;
					}
				}
			}
		}
	}
};