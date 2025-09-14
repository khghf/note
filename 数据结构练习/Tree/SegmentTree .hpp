#pragma once
#include<iostream>
#include<vector>
using namespace std;
struct SegNode
{
	int minvalue;
	int maxvalue;
	int sum;
	int layze;
	bool bEmpty;
	SegNode():minvalue(0), maxvalue(0), sum(0),layze(0), bEmpty(true){}
	SegNode(int value) :minvalue(value), maxvalue(value), sum(value), layze(0), bEmpty(false){}
};
class SegmentTree
{
private:
	vector<SegNode>tree;
	int n;//�߶���ӵ�еĽ��Ԫ��������
	int size;//���������߶���������Ĵ�С
public:
	SegmentTree():n(0) {}
	SegmentTree(vector<int>arr)
	{
		tree.resize(4*arr.size());
		size = arr.size();
		Build(arr, 0, 0, arr.size()-1);
	}
	void PrintMin()
	{
		cout << "Min:";
		int count = 0;
		for (int i = 0; i < tree.size(); i++)
		{
			if (!tree[i].bEmpty)
			{
				PushDown(i);//���������
				cout << tree[i].minvalue << " ";
				count++;
			}
			if (count >= n)break;
		}
		cout << endl;
	}
	void PrintMax()
	{
		cout << "Max:";
		int count = 0;
		for (int i = 0; i < tree.size(); i++)
		{
			if (!tree[i].bEmpty)
			{
				PushDown(i);//���������
				cout << tree[i].maxvalue << " ";
				count++;
			}
			if (count >= n)break;
		}
		cout << endl;
	}
	void PrintSum()
	{
		cout << "Sum:";
		int count = 0;
		for (int i = 0; i < tree.size(); i++)
		{
			if (!tree[i].bEmpty)
			{
				PushDown(i);//���������
				cout << tree[i].sum << " ";
				count++;
			}
			if (count >= n)break;
		}
		cout << endl;
	}
	int QueryMin(int l, int r)
	{
		l = max(0, l);
		r = min(size - 1, r);
		if (l > r)swap(l,r);
		return Query(l, r, 0, size - 1, 0,true);
	}
	int QueryMax(int l, int r)
	{
		l = max(0, l);
		r = min(size - 1, r);
		if (l > r)swap(l, r);
		return Query(l, r, 0, size - 1, 0, false);
	}
	void UpdataPoint(const int& value,const int&arrindex)
	{
		UpdataPoint(value, 0, arrindex, arrindex,0,size - 1);
	}
	void UpdataRangle(const int& IncreaseValue, int l, int r)
	{
		l = max(0, l);
		r = min(size - 1, r);
		UpdataRangle(IncreaseValue, l, r, 0, size - 1, 0);
	}
protected:
	void Build(const vector<int>&arr,int index,int l,int r)
	{
		//��������һ����ȫ��������ÿ�����Ԫ�ش洢���������ֵ
		//1�����������εݹ黮��Ϊ�����������䣬ֱ��������ֻ��һ��Ԫ��
		//2���Ը�Ԫ�ع���������tree������
		//3�����ظ��ڵ㣬������ֵΪmax(���ӵ�ֵ���к��ӵ�ֵ)
		if (l == r)tree[index] = SegNode(arr[l]);
		else
		{
			int mid = (l + r) / 2;
			Build(arr, index * 2 + 1, l, mid);
			Build(arr, index * 2 + 2, mid+1, r);
			tree[index] = Merge(tree[index * 2 + 1], tree[index * 2 + 2]);
		}
		n++;
	}
	SegNode Merge(const SegNode& node1, const SegNode& node2)
	{
		SegNode ret;
		ret.bEmpty = false;
		if (node1.maxvalue > node2.maxvalue)ret.maxvalue = node1.maxvalue;
		else ret.maxvalue = node2.maxvalue;
		if (node1.minvalue < node2.minvalue)ret.minvalue = node1.minvalue;
		else ret.minvalue = node2.minvalue;
		ret.sum = node1.sum + node2.sum;
		return ret;
	}
	int Query(int l, int r, int cl, int cr, int index,bool bMin)
	{
		int mid = (cl + cr) / 2;
		if (l == cl && r == cr)return bMin?tree[index].minvalue: tree[index].maxvalue;
		else if (r <= mid)Query(l, r, cl, mid, index * 2 + 1, bMin);//����������
		else if (l > mid)Query(l, r, mid + 1, cr, index * 2 + 2, bMin);//����������
		else if (l<=mid && r>mid)//�����������
		{//���ѣ������߶���ʱmid��Ӧ��Ԫ�ر����ֵ����

			if (bMin)
			{
				return min(Query(l, mid, cl, mid, index * 2 + 1, bMin), Query(mid + 1, r, mid + 1, cr, index * 2 + 2, bMin));
			}
			else
			{
				return max(Query(l, mid, cl, mid, index * 2 + 1, bMin), Query(mid + 1, r, mid + 1, cr, index * 2 + 2, bMin));
			}
			
		}
	}
	void UpdataPoint(const int& value, const int& treenodeindex, int l,  int r, int cl, int cr)
	{
		int mid = (cl + cr) / 2;
		if (l == cl && r == cr)
		{
			tree[treenodeindex].minvalue = value;
			tree[treenodeindex].maxvalue = value;
			tree[treenodeindex].sum = value;
			return;
		}
		else if (r <= mid)UpdataPoint(value, treenodeindex * 2 + 1,l, r, cl, mid);//����������
		else if (l > mid)UpdataPoint(value, treenodeindex * 2 + 2, l, r, mid+1, cr);//����������
		else if (l <= mid && r > mid)//�����������
		{//���ѣ������߶���ʱmid��Ӧ��Ԫ�ر����ֵ����
			UpdataPoint(value, treenodeindex * 2 + 1, l, r, cl, mid);
			UpdataPoint(value, treenodeindex * 2 + 2, l, r, mid + 1, cr);
		}
		int layze = tree[treenodeindex].layze;
		tree[treenodeindex] = Merge(tree[treenodeindex * 2 + 1], tree[treenodeindex * 2 + 2]);
		tree[treenodeindex].layze = layze;
	}
	void UpdataRangle(const int& IncreaseValue, int l, int r, int cl, int cr, int index)
	{
		int mid = (cl + cr) / 2;
		if (l == cl && r == cr)
		{
			tree[index].minvalue += IncreaseValue;
			tree[index].maxvalue += IncreaseValue;
			tree[index].sum += IncreaseValue;
			tree[index].layze += IncreaseValue;
			return;
		}
		else if (r <= mid)
		{
			if (tree[index].layze > 0)PushDown(index);
			UpdataRangle(IncreaseValue, l, r, cl, mid, index * 2 + 1);//����������
		}
		else if (l > mid)
		{
			if (tree[index].layze > 0)PushDown(index);
			UpdataRangle(IncreaseValue, l, r, mid + 1, cr, index * 2 + 2);//����������
		}
		else if (l <= mid && r > mid)//�����������
		{//���ѣ������߶���ʱmid��Ӧ��Ԫ�ر����ֵ����
			if (tree[index].layze > 0)PushDown(index);
			UpdataRangle(IncreaseValue, l, mid, cl, mid, index * 2 + 1);
			UpdataRangle(IncreaseValue, mid + 1, r, mid + 1, cr, index * 2 + 2);
		}
	}
	void PushDown(int index)
	{//���·ַ������
		if (index > tree.size() - 1)return;
		if (tree[index].layze > 0)
		{
			SegNode& node = tree[index];
			if (index * 2 + 1 < tree.size())
			{
				SegNode& leftnode = tree[index * 2 + 1];
				if (!leftnode.bEmpty)
				{
					leftnode.minvalue += node.layze;
					leftnode.maxvalue += node.layze;
					leftnode.sum += node.layze;
					leftnode.layze += node.layze;
				}
			}
			if (index * 2 + 2 < tree.size())
			{
				SegNode& rightnode = tree[index * 2 + 2];
				if (!rightnode.bEmpty)
				{
					rightnode.minvalue += node.layze;
					rightnode.maxvalue += node.layze;
					rightnode.sum += node.layze;
					rightnode.layze += node.layze;
				}
			}
			node.layze = 0;
		}
	}
};