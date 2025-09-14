#pragma once
#include"BaseGraph.hpp"
#include<iostream>
#include<vector>
#include<map>
using namespace std;
class MatrixGraph :public BaseGraph<int, int>
{
protected:
	vector<pair<vector<int>, string>>data;
	map<int,string>v_name;
public:
	MatrixGraph() {}
	MatrixGraph(vector<vector<int>>data)
	{
		this->data.resize(data.size());
		for (int i = 0; i < data.size(); i++)
		{
			this->data[i].first = data[i];
			this->data[i].second = "unDefineName";
			v_name.emplace(i, "unDefineName");
		}
	}
	virtual int inDegrre(int v)const override
	{
		int ret = 0;
		if (existV(v))
		{
			for (int i = 0; i < data.size(); i++)
			{
				if (i == v)continue;
				if (data[i].first[v] > 0)ret++;
			}
		}
		return ret;
	}
	virtual int outDegrre(int v)const override
	{
		int ret = 0;
		if (existV(v))
		{
			for (auto in : data[v].first)
			{
				if (in > 0)ret++;
			}
		}
		return ret;
	}
	virtual bool existE(int v1, int v2)const override
	{
		if (!existV(v1))return false;
		if (!existV(v2))return false;
		if (data[v1].first[v2] > 0)return true;
		return false;
	}
	virtual bool existV(int v)const override
	{
		return v >= data.size() ? false : true;
	}
	virtual int weight(int v1, int v2)const override
	{
		int ret = 0;
		if (existE(v1, v2))ret = data[v1].first[v2];
		return ret;
	}
	void Print()
	{
		for (auto in1 : data)
		{
			cout << in1.second << ":";
			for (auto in2 : in1.first)
			{
				cout << in2 << " ";
			}
			cout << endl;
		}
	}
	void Print_Name()
	{
		for (int i = 0; i < data.size(); i++)
		{
			cout << v_name[i] << ":";
			for (int j = 0; j < data[i].first.size(); j++)
			{
				if (data[i].first[j] != 0)cout << v_name[j] << " ";
			}
			cout << endl;

		}
	}
};