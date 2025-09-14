#pragma once
#include<iostream>
#include<string>
#include<queue>
#include<map>
using namespace std;
struct HFNode
{
	char*ch;
	HFNode* left,*right;
	int weight;
	HFNode() :ch(nullptr), left(nullptr), right(nullptr), weight(0) {}
	HFNode(char ch) :ch(new char(ch)), left(nullptr), right(nullptr), weight(0) {}
	HFNode(int w) :ch(nullptr), left(nullptr), right(nullptr), weight(w) {}
	~HFNode(){
		delete ch; ch = nullptr;
	}
};
class HFTree
{
	struct com
	{
		bool operator()(HFNode* n1, HFNode* n2)
		{
			return n1->weight > n2->weight;
		}
	};
protected:
	map<char, string>char_code;//存储每个字符对应的编码
	string char_code_temp;//临时变量
	string code;//存储字符串对应的编码
	HFNode*root;//根结点
public:
	HFTree():root(nullptr)
	{

	}
	HFTree(const string& str) :root(nullptr)
	{
		ReConstructTree(str);
	}
	~HFTree()
	{
		Destory(this->root);
	}
	void ReConstructTree(const string& str)
	{
		priority_queue<HFNode*, vector<HFNode*>, com>minheap;
		char_code.clear();
		code.clear();
		//统计字符频率
		map<char, int>temp;
		for (auto in : str)
		{
			temp[in]++;
		}
		//构建小根堆
		HFNode* node = nullptr;
		for (auto in : temp)
		{
			node = new HFNode(in.first);
			node->weight = in.second;
			minheap.push(node);
		}
		//构建哈夫曼树
		while (!minheap.empty())
		{
			HFNode* node1 = nullptr;
			HFNode* node2 = nullptr;
			HFNode* newnode = nullptr;
			if (minheap.size() >= 2)
			{
				node1 = minheap.top();
				minheap.pop();
				node2 = minheap.top();
				minheap.pop();
				newnode = new HFNode(node1->weight + node2->weight);
				minheap.push(newnode);
				newnode->left = node1;
				newnode->right = node2;
			}
			else
			{
				root = minheap.top();
				minheap.pop();
			}
		}
		//构建字符对应的哈夫曼编码
		ConstructChar_Code(this->root);
		//构建输入的字符串对应的编码
		ConstructCode(str);
	}
	void PrintChar_Code()
	{
		for (auto in : char_code)
		{
			cout << in.first << ":" << in.second << endl;
		}
	}
	void PrintCode()
	{
		cout << code << endl;
	}
protected:
	void ConstructChar_Code(HFNode*root)
	{
		if (root == nullptr)return;
		if (root->ch != nullptr)
		{
			char_code[*root->ch] = char_code_temp;
		}
		else
		{
			if (root->left != nullptr)
			{
				char_code_temp += '0';
				ConstructChar_Code(root->left);
				char_code_temp.pop_back();
			}
			if (root->right != nullptr)
			{
				char_code_temp += '1';
				ConstructChar_Code(root->right);
				char_code_temp.pop_back();
			}
		}
	}
	void ConstructCode(const string&str)
	{
		for (auto in : str)
		{
			auto temp = char_code.find(in);
			if (temp != char_code.end())code += temp->second+" ";
		}
	}
	void Destory(HFNode*root)
	{
		if (root == nullptr)return;
		Destory(root->left);
		Destory(root->right);
		delete root;
	}
};