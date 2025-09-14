#pragma once
#include"iostream"
#include"vector"
#include<list>
#include<future>
using namespace std;
namespace sort_algorithm
{
	template<typename T>
	void Print(const vector<T>& arr)
	{
		for (auto in : arr)
		{
			cout << in << " ";
		}
		cout << endl;
	}

	//ѡ������
	//1��iָ���һ��Ԫ��,jָ�����һ��Ԫ��
	//2��j��ǰ�ƶ������ȵ�i��Ԫ��С��Ԫ�ؾͽ�����ֱ��j��i����
	//3���ظ�����Ĳ���ֱ��������ɵ���ʱiҪָ����һ��Ԫ��
	template<typename T>
	void SelectSort(vector<T>& arr,bool raise=true)
	{
		for (int i = 0; i < arr.size(); i++)
		{
			cout << "times:" << i + 1 << endl;
			cout << "before:" <<" ";
			Print(arr);
			for (int j = arr.size() - 1; j > i; j--)
			{
				if (arr[i]>arr[j])
				{
					if (!raise)continue; //�����򲻽�����a>b
				}
				else
				{
					if (raise)continue; //�����򲻽���,a<=b
				}
				T temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			cout << "after :" << " ";
			Print(arr);
		}
		cout << endl;
	}
	//ð������

	template<typename T>
	void BubbleSort(vector<T>& arr, bool raise = true)
	{
		for (int i = 0; i < arr.size(); i++)
		{
			bool bSwap = false;
			cout << "times:" << i + 1 << endl;
			cout << "before:" << " ";
			Print(arr);
			for (int j = 0; j + 1 < arr.size() - i;j++)
			{
				if (raise)
				{
					if (arr[j] > arr[j + 1])
					{
						T temp = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = temp;
						bSwap = true;
					}
				}
				else
				{
					if (arr[j] < arr[j + 1])
					{
						T temp = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = temp;
						bSwap = true;
					}
				}
			}
			cout << "after :" << " ";
			Print(arr);
			if (!bSwap)
			{
				cout << endl;
				return;
			}
		}
		cout << endl;
	}

	//��������
	//1��ѡ������Ԫ�أ��������һ��Ԫ�ؽ���
	//2��leftָ��δ��������ĵڶ���Ԫ�أ�rightָ�����һ��Ԫ��
	//3��left����ѭ�����Ҵ��������Ԫ�أ�right����ѭ������С�������Ԫ��
	//4������left��rightָ���Ԫ��
	//5���ظ���3��ֱ��left>right
	//6����һ��Ԫ����rightָ���Ԫ�ؽ�������ʱ��right�±�Ϊ���Ļ��ֳ���������������
	//7����������������ݹ�ִ����ͬ����ֱ��û������Ϊֹ(�������)
	template<typename T>
	void QuickSort(vector<T>& arr, int left, int right,bool raise)
	{
		if (arr.size() <= 1 || left >= right)return;
		swap(arr[left], arr[rand() % (right - left + 1) + left]);
		T pivot = arr[left];
		int l = left+1, r = right;
		bool bRight = true;
		cout << "before:" << " ";
		Print(arr);
		while (true)
		{
			if (raise)
			{
				//�ұ�����Ԫ�ش��
				while (l <= right && arr[l] < pivot)l++;
				//�ұ�����Ԫ��С��
				while (r >= left+1 && arr[r] > pivot)r--;
				if (l > r)break;
				swap(arr[l], arr[r]);
				l++; r--;
			}
			else
			{
				while (l <= right && arr[l] > pivot)l++;
				while (r >= left+1 && arr[r] < pivot)r--;
				if (l > r)break;
				swap(arr[l], arr[r]);
				l++; r--;
			}
		}
		swap(arr[left], arr[r]);
		cout << "after:" << " ";
		Print(arr);
		QuickSort(arr, left, r - 1, raise);
		QuickSort(arr, r + 1, right, raise);
	}
	template<typename T>
	void QuickSort(vector<T>& arr,bool raise=true)
	{
		QuickSort(arr, 0, arr.size() - 1, raise);
	}
	template<typename T>
	std::list<T> parallel_quick_sort(std::list<T> input)
	{
		if (input.empty())
		{
			return input;
		}
		std::list<T> result;
		//ʹ�� splice �� input �б�ĵ�һ��Ԫ���ƶ��� result �Ŀ�ͷ��
		result.splice(result.begin(), input, input.begin());
		T const& pivot = *result.begin();
		//ʹ�� std::partition �� input �б�ָ�Ϊ�����֣�
		//һ���ְ�������С�� pivot ��Ԫ�ء�
		//��һ���ְ������д��ڻ���� pivot ��Ԫ�ء�
		//divide_point ��һ����������ָ���һ���ֺ͵ڶ����ֵķָ��
		auto divide_point = std::partition(input.begin(), input.end(),
			[&](T const& t) {return t < pivot; });
		//ʹ�� splice �� input ������С�� pivot ��Ԫ���ƶ��� lower_part �С�
		std::list<T> lower_part;
		lower_part.splice(lower_part.end(), input, input.begin(),
			divide_point);
		//ʹ�� std::async ����һ���µ��̣߳��첽�ض� lower_part ���п�������
		std::future<std::list<T>> new_lower(std::async(&parallel_quick_sort<T>, std::move(lower_part)));
		//�ݹ�ض� input ��ʣ���Ԫ�أ������ڻ���� pivot �Ĳ��֣����п�������
		auto new_higher(parallel_quick_sort(std::move(input)));
		//�� new_higher�����ϰ벿���������б��ϲ��� result ��ĩβ��
		result.splice(result.end(), new_higher);
		//ʹ�� new_lower.get() ��ȡ�첽����Ľ����������ϲ��� result �Ŀ�ͷ��
		result.splice(result.begin(), new_lower.get());
		return result;
	}
	//��������
	//1���ӵ�һ��Ԫ�ؿ�ʼ����Ԫ�ؿ�����Ϊ�Ѿ�������
	//2��ȡ����һ��Ԫ�أ����Ѿ������Ԫ�������дӺ���ǰɨ�裻
	//3�������Ԫ�أ������򣩴�����Ԫ�أ�����Ԫ���Ƶ���һλ�ã�
	//4���ظ�����3��ֱ���ҵ��������Ԫ��С�ڻ��ߵ�����Ԫ�ص�λ�ã�
	//5������Ԫ�ز��뵽��λ�ú�
	//�ظ�����2~5��
	template<typename T>
	void InsertionSort(vector<T>&arr,bool raise=true)
	{
		int sortrdcount = 1;
		for (int i = 1; i < arr.size(); i++)
		{
			int index = i;
			cout << "before:" << " ";
			Print(arr);
			for (int j = sortrdcount-1; j >= 0; j--)
			{
				if (raise)
				{
					if (arr[index] > arr[j])break;
					swap(arr[index], arr[j]);
					index--;
				}
				else
				{
					if (arr[index] < arr[j])break;
					swap(arr[index], arr[j]);
					index--;
				}
			}
			sortrdcount++;
			cout << "after:" << " ";
			Print(arr);
		}
	}

	//�ϲ���������
	template<typename T>
	void MergeSort(vector<T>&arr, int l, int mid, int r, vector<T>& temp, bool raise = true)
	{
		int i = l, j = mid+1;
		while (true)
		{
			if (i <= mid && j <= r)
			{
				if (raise)
				{
					if (arr[i] > arr[j])temp.push_back(arr[j++]);
					else temp.push_back(arr[i++]);
				}
				else
				{
					if (arr[i] < arr[j])temp.push_back(arr[j++]);
					else temp.push_back(arr[i++]);
				}
			}
			else if (i <= mid)temp.push_back(arr[i++]);
			else if (j <= r)temp.push_back(arr[j++]);
			else break;
		}
		i = l;
		for (auto in : temp)
		{
			arr[i++] = in;
		}
		temp.clear();
	}
	//�ݹ黮������
	template<typename T>
	void MergeSort(vector<T>&arr, int l,int r, vector<T>&temp,bool raise = true)
	{
		if (l >= r)return;
		int mid = l + (r - l) / 2;
		//����
		MergeSort(arr, l, mid, temp, raise);
		MergeSort(arr, mid + 1, r, temp, raise);
		//�ϲ�
		MergeSort(arr, l, mid, r, temp, raise);
	}
	template<typename T>
	void MergeSort(vector<T>&arr, bool raise = true)
	{
		vector<T>temp;
		temp.reserve(arr.size());
		MergeSort(arr, 0, arr.size() - 1, temp,raise);
		Print(arr);
	}
}