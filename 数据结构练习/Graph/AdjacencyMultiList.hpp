#pragma once
#include"BaseGraph.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;
//弧结点
struct ENodeM
{
	int i, j;//边的两个顶点的编号
	int weight;
	ENodeM* iLink,*jLink;//依附顶点i，j的下一条边
	ENodeM() :i(-1), j(-1), weight(-1), iLink(nullptr), jLink(nullptr) {}
	ENodeM(int i,int j):i(i),j(j),weight(-1),iLink(nullptr),jLink(nullptr){}
	ENodeM(int weight) :weight(weight),i(-1), j(-1), iLink(nullptr), jLink(nullptr) {}
};
//顶点结点
struct VNodeM
{
	string data;
	ENodeM* firstedge;
	VNodeM():data(""), firstedge(nullptr){}
	VNodeM(string data) :data(data), firstedge(nullptr) {}
};
class MulityList
{
protected:
	vector<VNodeM*>vnodes;
public:
	MulityList() {}
	MulityList(vector<vector<int>>data) 
	{
		vnodes.resize(data.size());
		for (int i = 0; i < data.size(); i++)
		{
			vnodes[i] = new VNodeM();
		}
		map<int, vector<ENodeM*>>jLinks;
		ENodeM** vhi = nullptr;
		ENodeM** vhj = nullptr;
		for (int i = 0; i < data.size(); i++)
		{
			vnodes[i]->data = to_string(i);
			vhi = &vnodes[i]->firstedge;
			for (int j = 0; j <data.size()-i; j++)
			{
				if (data[i][j] > 0)
				{
					while ((*vhi) != nullptr)
					{
						if ((*vhi)->i == i)
						{
							vhi = &(*vhi)->iLink;
						}
						else
						{
							vhi = &(*vhi)->jLink;
						}
						continue;
					}
					ENodeM* temp = new ENodeM(i, j);
					*vhi = temp;
					if ((*vhi)->i == i)
					{
						vhi = &(*vhi)->iLink;
					}
					else
					{
						vhi = &(*vhi)->jLink;
					}
					if (vnodes[j]->firstedge == nullptr)vnodes[j]->firstedge = temp;
					jLinks[j].push_back(temp);
				}
			}
		}
		/*for (int i = 0; i < data.size(); i++)
		{
			vnodes[i]->data = to_string(i);
			vh = &vnodes[i]->firstedge;
			for (int j = 0; j < data.size(); j++)
			{
				if (data[i][j] > 0)
				{
					ENodeM* temp = new ENodeM(i, j);
					*vh = temp;
					vh = &temp->iLink;
					if (vnodes[i]->firstedge == nullptr)
					{
						vnodes[i]->firstedge = temp;
					}
					jLinks[j].push_back(temp);
				}
			}
		}*/
		for (auto in : jLinks)
		{
			int cur = 0;
			for (; cur + 1 < in.second.size(); cur++)
			{
				ENodeM* cure = in.second[cur];
				ENodeM* nexte = in.second[cur + 1];
				cure->jLink = nexte;
			}
		}
	}
	void Print()
	{
		ENodeM* next = nullptr;
		for (int i = 0; i < vnodes.size(); i++)
		{
			cout << vnodes[i]->data << ":";
			next = vnodes[i]->firstedge;
			while (next != nullptr)
			{
				if (next->i == i)
				{
					cout << vnodes[next->j]->data << " ";
					next = next->iLink;
				}
				else
				{
					cout << vnodes[next->i]->data << " ";
					next = next->jLink;
				}
			}
			cout << endl;
		}
		/*for (auto in : vnodes)
		{
			cout << in->data << ":";
			next = in->firstedge;
			while (next != nullptr)
			{
				cout << vnodes[next->j]->data << " ";

				next = next->iLink;
			}
			cout << endl;
		}*/
	}
};