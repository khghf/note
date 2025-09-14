//
// 
// 
// 
// 
//  
//	
//	
//  
//	
//	  ||							 t8||
//	    *******************************||
//	  ||			t4||			   ||
//		**************||			   ||
//	  ||   t2||		  ||	 t6||	   ||
//	   ******||		  ||*******||	   ||
// 	  ||t1|| ||t3||	  || t5||  ||t7||  ||
//	    1   2||	3	4 || 5	  6||7	  8||
// 
//		
// 
//////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include<vector>
using namespace std;
template<class T>
class BIT
{
private:
	vector<T>tree;
public:
	BIT(int arrsize) { tree.resize(arrsize); }
	BIT(const T arr[], int size, int arrsize = 0) {
		if (arrsize == 0)tree.resize(size);
		else tree.resize(arrsize);
		for (int i = 0; i < size; i++)
		{
			add(arr[i], i);
		}
	}
	void add(const T& value, const int& index)
	{
		for (int i = index; i < tree.size(); i += lowbit(i + 1))
		{
			tree[i] += value;
		}
	}
	void update(const T& value, const int& index)
	{
		T sub = value - tree[index];
		for (int i = index; i < tree.size(); i += lowbit(i + 1))
		{
			tree[i] += sub;
		}
	}
	void increase(const T& value, const int& index)
	{
		for (int i = index; i < tree.size(); i += lowbit(i + 1))
		{
			tree[i] +=value;
		}
	}
	//求前n项和
	T query(int n)
	{
		//if (n > tree.size())n = tree.size();
		T* temp = new T();
		T ret = *temp;
		delete temp;
		if (n == 0)return ret;
		for (int i = n; i > 0; i -= lowbit(i))
		{
			ret += tree[i-1];
		}
		return ret;
	}
	//区间和(l,r]
	T query(int l, int r)
	{
		return query(r) - query(l);
	}
	T get(const int& index)
	{
		return query(index + 1) - query(index);
	}
	int lowbit(int x)
	{
		//计算x二进制下最后一个1对应的值
		//例如：5:0101->1,  4:0100->100->4,  20:0010100->100->4
		return x & (-x);
	}

	void Print()
	{
		for (auto in : tree)
		{
			cout << in << " ";
		}
		cout << endl;
	}
	int InversePairs(vector<int> nums)
	{
		//将nums里的值映射为下标，例如nums=[12,77,8,2,9,0]
		vector<T>temp = nums;
		sort(temp.begin(), temp.end());//排序后temp=[0,2,8,9,12,77]
		for (int i = 0; i < temp.size(); i++)
		{
			//lower_bound返回一个指向不早于val的元素的迭代器
			//在这里将			nums[12,77,8,2,9,0]根据排序后的temp=[0,2,8,9,12,77]
			//映射为			nums[4,5,2,1,3,0]以便树状数组使用
			nums[i] = lower_bound(temp.begin(), temp.end(), nums[i])-temp.begin();
		}
		BIT bit(nums.size());
		int ret = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			//遍历nums[4,5,2,1,3,0]
			//每次遍历会对nums[i]对应的位置及其后面的祖先结点加1
			//例如出现了4，对应的4号位置+1,											0，0，0，1，0，0
			//再次遍历到5先计算:总和-前5项总和=0，然后对5号位置，以及6号位置+1		0，0，0，1，1，1
			//遍历到2：计算:总和-前2项总和=2-0=2，2号，4号位置加1					0，1，0，2，1，1
			//依次类推就能计算出总的逆序对
			// 
			//主要利用了树状数组的前缀和
			//当加入，4，5，后总和变成了2，然后再次遍历到2时，2的位置前面没有任何数，此时总和减去前2项总和就得出了逆序对的数量
			ret+=bit.query(nums.size()) - bit.query(nums[i]);
			bit.increase(1, nums[i]);
		}
		return ret;
	}
};