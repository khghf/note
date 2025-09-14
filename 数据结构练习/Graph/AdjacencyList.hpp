#pragma once
#include"BaseGraph.hpp"
#include<iostream>
#include<vector>
#include<map>
using namespace std;
struct LV
{
	string name;
	LV* next;
	LV() :name(""), next(nullptr) {}
	LV(string name) :name(name), next(nullptr) {}
	LV(LV* next) :name(""), next(next) {}
	LV(string name,LV*next):name(name),next(next) {}
};
typedef LV vtype;
class ListGraph :public BaseGraph<int,int>
{
protected:
	vector<vtype>data;
public:
	ListGraph() {}
	ListGraph(string description) {
		string name;
		bool bName = true;
		vtype* vh = nullptr;
		for (auto in : description)
		{
			if(in==':')
			{
				bName = false;
				data.emplace_back(vtype(name));
				vh = &(*(data.end()-1));
				name.clear();
			}
			else if (in == '#')
			{
				bName = true;
			}
			else 
			{
				if (bName)name += in;
				else
				{
					string n;n += in;
					vtype* temp = new vtype(n);
					vh->next = temp;
					vh = vh->next;
				}
			}
		}
	}
	ListGraph(vector<vector<int>>data)
	{
		int n = data.size();
		this->data.resize(n);
		for (int i = 0; i < n; i++)
		{
			this->data[i].name = to_string(i);
			vtype* vh = &this->data[i];
			for (int j = 0; j < n; j++)
			{
				if (data[i][j] > 0)
				{
					vtype* temp = new vtype(to_string(j));
					vh->next = temp;
					vh = vh->next;
				}
			}
		}
	}
	virtual int inDegrre(int v)const override
	{
		int ret = 0;
		return ret;
	}
	virtual int outDegrre(int v)const override
	{
		int ret = 0;
		vtype* next = data[v].next;
		while (next != nullptr)
		{
			ret++;
			next = next->next;
		}
		return ret;
	}
	
	virtual bool existE(int v1, int v2)const override
	{
		if (existV(v1))
		{
			vtype* temp = data[v1].next;
			while (temp != nullptr)
			{
				if (temp->name == data[v2].name)return true;
				temp = temp->next;
			}
		}
		return false;
	}
	virtual bool existV(int v)const override
	{
		if (v < data.size())return true;
		return false;
	}
	virtual int weight(int v1, int v2)const override
	{
		int ret = 0;
		return ret;
	}
	void Print()
	{
		for (auto in : data)
		{
			cout << in.name << ":";
			vtype* temp = in.next;
			while (temp!=nullptr)
			{
				cout << temp->name << " ";
				temp = temp->next;
			}
			cout << endl;
		}
	}
	
};