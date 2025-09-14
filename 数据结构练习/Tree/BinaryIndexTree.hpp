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
	//��ǰn���
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
	//�����(l,r]
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
		//����x�����������һ��1��Ӧ��ֵ
		//���磺5:0101->1,  4:0100->100->4,  20:0010100->100->4
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
		//��nums���ֵӳ��Ϊ�±꣬����nums=[12,77,8,2,9,0]
		vector<T>temp = nums;
		sort(temp.begin(), temp.end());//�����temp=[0,2,8,9,12,77]
		for (int i = 0; i < temp.size(); i++)
		{
			//lower_bound����һ��ָ������val��Ԫ�صĵ�����
			//�����ｫ			nums[12,77,8,2,9,0]����������temp=[0,2,8,9,12,77]
			//ӳ��Ϊ			nums[4,5,2,1,3,0]�Ա���״����ʹ��
			nums[i] = lower_bound(temp.begin(), temp.end(), nums[i])-temp.begin();
		}
		BIT bit(nums.size());
		int ret = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			//����nums[4,5,2,1,3,0]
			//ÿ�α������nums[i]��Ӧ��λ�ü����������Ƚ���1
			//���������4����Ӧ��4��λ��+1,											0��0��0��1��0��0
			//�ٴα�����5�ȼ���:�ܺ�-ǰ5���ܺ�=0��Ȼ���5��λ�ã��Լ�6��λ��+1		0��0��0��1��1��1
			//������2������:�ܺ�-ǰ2���ܺ�=2-0=2��2�ţ�4��λ�ü�1					0��1��0��2��1��1
			//�������ƾ��ܼ�����ܵ������
			// 
			//��Ҫ��������״�����ǰ׺��
			//�����룬4��5�����ܺͱ����2��Ȼ���ٴα�����2ʱ��2��λ��ǰ��û���κ�������ʱ�ܺͼ�ȥǰ2���ܺ;͵ó�������Ե�����
			ret+=bit.query(nums.size()) - bit.query(nums[i]);
			bit.increase(1, nums[i]);
		}
		return ret;
	}
};