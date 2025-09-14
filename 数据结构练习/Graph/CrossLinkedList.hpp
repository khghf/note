#pragma once
#include"BaseGraph.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;
//弧结点
struct ENode
{
	int tailvex;//弧尾顶点编号(下标)
	int headvex;//弧头顶点编号(下标)
	int weight;//权值
	ENode* hlink;//指向弧头相同的下一条弧
	ENode* tlink;//指向弧尾相同的下一条弧
	ENode() :weight(0), hlink(nullptr), tlink(nullptr), tailvex(-1), headvex(-1) {}
	ENode(int weight,int hv,int tv):weight(weight),hlink(nullptr),tlink(nullptr),tailvex(tv),headvex(hv){}
};
//顶点结点
struct VNode
{
	string data;//顶点数据
	ENode* firstin;//以该顶点作为弧头的第一条弧。例：该顶点为A.A<-B,该指针指向的是弧结点<-
	ENode* firstout;//以该顶点作为弧尾的第一条弧。例：该顶点为A.A->C,该指针指向的是弧结点->
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
		map<int, vector<ENode*>>hlinks;//根据下标将弧头相同的弧分类存储
		for (int i = 0; i < vnode_enode.size(); i++)
		{
			vh = &vnodes[i]->firstout;
			for (int j = 0; j < vnode_enode[i].second.size(); j++)
			{
				string vname; 
				vname += vnode_enode[i].second[j];
				//权重、弧头、弧尾
				temp = new ENode(0, vnode_index[vname], i);
				//指向弧尾相同的下一条弧
				*vh = temp;
				vh = &temp->tlink;
				//根据下标将弧头相同的弧分类存储
				hlinks[vnode_index[vname]].push_back(temp);
				if (vnodes[vnode_index[vname]]->firstin == nullptr)
				{
					//j顶点的第一条入边
					vnodes[vnode_index[vname]]->firstin = temp;
				}
			}
		}
		for (auto in : hlinks)
		{
			int cur = 0;
			for (; cur + 1 < in.second.size(); cur++)
			{
				//指向弧头相同的下一条弧(道路终点相同)
				ENode* cure = in.second[cur];
				ENode* nexte = in.second[cur + 1];
				cure->hlink = nexte;
			}
		}
	}
	CrossLinkedList(vector<vector<int>>data)
	{
		//十字链表有弧结点(道路)和顶点结点(城市)组成
		//弧结点(道路)有:
		//		弧尾编号(道路起点的城市)，弧头编号(道路终点的城市),权值(道路长度)
		//		指向弧头相同的下一条弧(道路终点相同)
		//		指向弧尾相同的下一条弧(道路起点相同)
		//顶点结点(城市)有:
		//		顶点数据(城市名称)
		//		指向该顶点的第一条边的指针(道路终点为该城市的道路。第一条！！)
		//		该顶点指向的第一条边的指针(道路起点为该城市的道路。第一条！！)
		int n = data.size();
		for (int i = 0; i < n; i++)
		{
			vnodes.emplace_back(new VNode());
		}
		ENode* temp = nullptr;
		ENode** vh = nullptr;
		map<int, vector<ENode*>>hlinks;//根据下标将弧头相同的弧分类存储
		for (int i = 0; i < n; i++)
		{
			vnodes[i]->data = to_string(i);
			vh = &vnodes[i]->firstout;
			for (int j = 0; j < n; j++)
			{
				if (data[i][j] > 0)
				{
					//权重、弧头、弧尾
					temp = new ENode(data[i][j], j, i);
					//指向弧尾相同的下一条弧
					*vh = temp;
					vh = &temp->tlink;
					//根据下标将弧头相同的弧分类存储
					hlinks[j].push_back(temp);
					if (vnodes[j]->firstin == nullptr)
					{
						//j顶点的第一条入边
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
				//指向弧头相同的下一条弧(道路终点相同)
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
			cout << vnodes[index]->data<<"的入度:";
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
			cout << vnodes[index]->data << "的出度:";
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