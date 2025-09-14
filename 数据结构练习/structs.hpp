#pragma once
template<class T>
struct TreeNode
{
	T value;
	TreeNode<T>*left;
	TreeNode<T>*right;
	TreeNode() :left(nullptr), right(nullptr),parent(nullptr),BF(0),Depth(0), bColor(true){}
	TreeNode(const T& Value) :value(Value), left(nullptr), right(nullptr), parent(nullptr), BF(0), Depth(0), Height(0), bColor(true) {}
	//为平衡二叉树准备
	TreeNode<T>* parent;
	int BF;
	int Depth;//深度：从上往下数
	int Height;//高度：从下往上数
	//红黑树
	bool bColor;//false为黑色,true为红色
};
