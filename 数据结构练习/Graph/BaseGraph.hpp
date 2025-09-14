#pragma once
#include<vector>
using namespace std;
template<class vtype,class etype>
class BaseGraph
{
protected:
	int Vnum, Enum;
public:
	virtual ~BaseGraph() {}
	virtual int inDegrre(vtype v)const = 0;
	virtual int outDegrre(vtype v)const = 0;
	virtual bool existE(vtype v1, vtype v2)const = 0;
	virtual bool existV(vtype v)const = 0;
	virtual int weight(vtype v1, vtype v2)const = 0;

};