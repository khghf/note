#pragma once
#include"BaseGraph.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;
//�����
struct ENode
{
	int tailvex;//��β������(�±�)
	int headvex;//��ͷ������(�±�)
	int weight;//Ȩֵ
	ENode* hlink;//ָ��ͷ��ͬ����һ����
	ENode* tlink;//ָ��β��ͬ����һ����
	ENode() :weight(0), hlink(nullptr), tlink(nullptr), tailvex(-1), headvex(-1) {}
	ENode(int weight,int hv,int tv):weight(weight),hlink(nullptr),tlink(nullptr),tailvex(tv),headvex(hv){}
};
//������
struct VNode
{
	string data;//��������
	ENode* firstin;//�Ըö�����Ϊ��ͷ�ĵ�һ�����������ö���ΪA.A<-B,��ָ��ָ����ǻ����<-
	ENode* firstout;//�Ըö�����Ϊ��β�ĵ�һ�����������ö���ΪA.A->C,��ָ��ָ����ǻ����->
	VNode() :data(""), firstin(nullptr), firstout(nullptr) {}
	VNode(string data):data(data),firstin(nullptr),firstout(nullptr){}
};
class CrossLinkedList /*:public BaseGraph<ENode, VNode>*/
{
protected:
	vector<VNode*>vnodes;
public:
	CrossLinkedList(string description) {
		string name;
		bool bName = true;
		map<int, pair<string,string>>vnode_enode;
		map<string, int>vnode_index;
		for (auto in : description)
		{
			if (in == ':')
			{
				bName = false;
				vnodes.emplace_back(new VNode(name));
				vnode_enode.emplace(vnode_enode.size(), make_pair(name, ""));
				vnode_index.emplace(name,vnode_index.size());
				name.clear();
			}
			else if (in == '#')
			{
				bName = true;
				vnode_enode[vnode_enode.size() - 1].second = name;
				name.clear();
			}
			else
			{
				name += in;
			}
		}
		ENode* temp = nullptr;
		ENode** vh = nullptr;
		map<int, vector<ENode*>>hlinks;//�����±꽫��ͷ��ͬ�Ļ�����洢
		for (int i = 0; i < vnode_enode.size(); i++)
		{
			vh = &vnodes[i]->firstout;
			for (int j = 0; j < vnode_enode[i].second.size(); j++)
			{
				string vname; 
				vname += vnode_enode[i].second[j];
				//Ȩ�ء���ͷ����β
				temp = new ENode(0, vnode_index[vname], i);
				//ָ��β��ͬ����һ����
				*vh = temp;
				vh = &temp->tlink;
				//�����±꽫��ͷ��ͬ�Ļ�����洢
				hlinks[vnode_index[vname]].push_back(temp);
				if (vnodes[vnode_index[vname]]->firstin == nullptr)
				{
					//j����ĵ�һ�����
					vnodes[vnode_index[vname]]->firstin = temp;
				}
			}
		}
		for (auto in : hlinks)
		{
			int cur = 0;
			for (; cur + 1 < in.second.size(); cur++)
			{
				//ָ��ͷ��ͬ����һ����(��·�յ���ͬ)
				ENode* cure = in.second[cur];
				ENode* nexte = in.second[cur + 1];
				cure->hlink = nexte;
			}
		}
	}
	CrossLinkedList(vector<vector<int>>data)
	{
		//ʮ�������л����(��·)�Ͷ�����(����)���
		//�����(��·)��:
		//		��β���(��·���ĳ���)����ͷ���(��·�յ�ĳ���),Ȩֵ(��·����)
		//		ָ��ͷ��ͬ����һ����(��·�յ���ͬ)
		//		ָ��β��ͬ����һ����(��·�����ͬ)
		//������(����)��:
		//		��������(��������)
		//		ָ��ö���ĵ�һ���ߵ�ָ��(��·�յ�Ϊ�ó��еĵ�·����һ������)
		//		�ö���ָ��ĵ�һ���ߵ�ָ��(��·���Ϊ�ó��еĵ�·����һ������)
		int n = data.size();
		for (int i = 0; i < n; i++)
		{
			vnodes.emplace_back(new VNode());
		}
		ENode* temp = nullptr;
		ENode** vh = nullptr;
		map<int, vector<ENode*>>hlinks;//�����±꽫��ͷ��ͬ�Ļ�����洢
		for (int i = 0; i < n; i++)
		{
			vnodes[i]->data = to_string(i);
			vh = &vnodes[i]->firstout;
			for (int j = 0; j < n; j++)
			{
				if (data[i][j] > 0)
				{
					//Ȩ�ء���ͷ����β
					temp = new ENode(data[i][j], j, i);
					//ָ��β��ͬ����һ����
					*vh = temp;
					vh = &temp->tlink;
					//�����±꽫��ͷ��ͬ�Ļ�����洢
					hlinks[j].push_back(temp);
					if (vnodes[j]->firstin == nullptr)
					{
						//j����ĵ�һ�����
						vnodes[j]->firstin = temp;
					}
				}
			}
		}

		for (auto in : hlinks)
		{
			int cur = 0;
			for (; cur + 1 < in.second.size(); cur++)
			{
				//ָ��ͷ��ͬ����һ����(��·�յ���ͬ)
				ENode* cure = in.second[cur];
				ENode* nexte = in.second[cur + 1];
				cure->hlink = nexte;
			}
		}
	}
	~CrossLinkedList()
	{
		for (auto in : vnodes)
		{
			ENode* next = in->firstout;
			while (next!=nullptr)
			{
				in->firstout = in->firstout->tlink;
				delete next; next = nullptr;
			}
			delete in; in = nullptr;
		}
	}
	void Print()
	{
		for (auto in : vnodes)
		{
			cout << in->data << ":";
			ENode* temp = in->firstout;
			while (temp != nullptr)
			{
				cout << vnodes[temp->headvex]->data << " ";
				temp = temp->tlink;
			}
			cout << endl;
		}
	}
	void PrintInDegrre(const int& index)
	{
		if (index < vnodes.size())
		{
			cout << vnodes[index]->data<<"�����:";
			ENode* next = vnodes[index]->firstin;
			while (next != nullptr)
			{
				cout << vnodes[next->tailvex]->data << " ";
				next = next->hlink;
			}
			cout << endl;
		}
	}
	void PrintOutDegrre(const int& index)
	{
		if (index < vnodes.size())
		{
			cout << vnodes[index]->data << "�ĳ���:";
			ENode* next = vnodes[index]->firstout;
			while (next != nullptr)
			{
				cout << vnodes[next->headvex]->data << " ";
				next = next->tlink;
			}
			cout << endl;
		}
	}
};