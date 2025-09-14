//��һ���������ȫ������������һ������ֵ������(�����)��С��(С����)���ӽ���ֵ
// ��ȫ������
//�������һ���⣬ÿһ�㶼����ȫ�������������һ��Ľ��Ϊ�����������������У�
//�������£��������Ҹ�ÿ�������ʱ����������������Ӧ
//	���ԣ�	
//		�������1 ��ʼ��ţ����i ������Ϊ2i���Һ���Ϊ2i + 1�����i �ĸ����Ϊ i / 2 ������еĻ���
//		�������0 ��ʼ��ţ����i ������Ϊ2i+1���Һ���Ϊ2i + 2�����i �ĸ����: ����(�±�Ϊ����)Ϊ��i / 2 �ҽ��(�±�Ϊż��)Ϊ��i / 2-1 ������еĻ���
//		
//	i�� n / 2 Ϊ��֧��㣬 i > n / 2 ΪҶ�ӽ��
//�������
//	һ����������
//	�����븸���Ƚ����������/С�Ѷ������������߽���
//	���������ڵ��Ϊ���������丸�ڵ�Ƚϣ�ֱ��������Ҫ���н�������û�и��ڵ�Ϊֹ
// ��һ�ַ���:ֱ�Ӷ�������в����������һ����Ҷ�ӽ�㿪ʼ��ǰִ���³�����ֱ��ִ����������³�����,��ÿ���³�һ�����Ҫ�Ա������Ľ��Ҳ���еݹ��³�
//ɾ������
//һ��������ĩβ��Ԫ�ش���Ѷ�Ԫ��
//�����Ӹ���㿪ʼ�����Һ��ӽ��Ƚ����������/С�Ѷ��������򽻻���ֱ������Ҫ�����û�к��ӽ��Ϊֹ
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
			//С����
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
			//�����
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
			//С����
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
			//�����
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
			//С����
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
			//�����
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