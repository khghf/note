#pragma once
#include"iostream"
#include"structs.hpp"
#include"BaseBinaryTree.hpp"
using namespace std;
template<class T>
class BST:public BaseBinaryTree<T>
{
public:
	BST() {}
	BST(const T arr[], int size)
	{
		__super::Init(arr, size);
	}
	virtual void Insert(const T& Value, TreeNode<T>*& Node)override//应为要修改指向所以要传递引用
	{
		if (Node == nullptr)
		{
			Node = new TreeNode<T>(Value);
			this->size++;
			//cout << Value << " ";
			return;
		}
		if (Value <= Node->value)Insert(Value, Node->left);
		else Insert(Value, Node->right);
	}
};