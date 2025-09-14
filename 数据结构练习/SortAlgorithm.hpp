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

	//选择排序
	//1、i指向第一个元素,j指向最后一个元素
	//2、j向前移动遇到比第i个元素小的元素就交换，直到j与i相遇
	//3、重复上面的步骤直到排序完成但此时i要指向下一个元素
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
					if (!raise)continue; //降序则不交换，a>b
				}
				else
				{
					if (raise)continue; //升序则不交换,a<=b
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
	//冒泡排序

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

	//快速排序
	//1、选择枢轴元素，将其与第一个元素交换
	//2、left指向未排序数组的第二个元素，right指向最后一个元素
	//3、left向右循环查找大于枢轴的元素，right向左循环查找小于枢轴的元素
	//4、交换left和right指向的元素
	//5、重复第3步直到left>right
	//6、第一个元素与right指向的元素交换，此时以right下标为中心划分出了左右两个区间
	//7、对左右两个区间递归执行相同操作直到没有区间为止(排序完成)
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
				//找比枢轴元素大的
				while (l <= right && arr[l] < pivot)l++;
				//找比枢轴元素小的
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
		//使用 splice 将 input 列表的第一个元素移动到 result 的开头。
		result.splice(result.begin(), input, input.begin());
		T const& pivot = *result.begin();
		//使用 std::partition 将 input 列表分割为两部分：
		//一部分包含所有小于 pivot 的元素。
		//另一部分包含所有大于或等于 pivot 的元素。
		//divide_point 是一个迭代器，指向第一部分和第二部分的分割点
		auto divide_point = std::partition(input.begin(), input.end(),
			[&](T const& t) {return t < pivot; });
		//使用 splice 将 input 中所有小于 pivot 的元素移动到 lower_part 中。
		std::list<T> lower_part;
		lower_part.splice(lower_part.end(), input, input.begin(),
			divide_point);
		//使用 std::async 启动一个新的线程，异步地对 lower_part 进行快速排序
		std::future<std::list<T>> new_lower(std::async(&parallel_quick_sort<T>, std::move(lower_part)));
		//递归地对 input 中剩余的元素（即大于或等于 pivot 的部分）进行快速排序。
		auto new_higher(parallel_quick_sort(std::move(input)));
		//将 new_higher（即上半部分排序后的列表）合并到 result 的末尾。
		result.splice(result.end(), new_higher);
		//使用 new_lower.get() 获取异步排序的结果，并将其合并到 result 的开头。
		result.splice(result.begin(), new_lower.get());
		return result;
	}
	//插入排序
	//1、从第一个元素开始，该元素可以认为已经被排序；
	//2、取出下一个元素，在已经排序的元素序列中从后向前扫描；
	//3、如果该元素（已排序）大于新元素，将该元素移到下一位置；
	//4、重复步骤3，直到找到已排序的元素小于或者等于新元素的位置；
	//5、将新元素插入到该位置后；
	//重复步骤2~5。
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

	//合并有序区间
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
	//递归划分区间
	template<typename T>
	void MergeSort(vector<T>&arr, int l,int r, vector<T>&temp,bool raise = true)
	{
		if (l >= r)return;
		int mid = l + (r - l) / 2;
		//划分
		MergeSort(arr, l, mid, temp, raise);
		MergeSort(arr, mid + 1, r, temp, raise);
		//合并
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