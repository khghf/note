#pragma once
template<class T>
struct TreeNode
{
	T value;
	TreeNode<T>*left;
	TreeNode<T>*right;
	TreeNode() :left(nullptr), right(nullptr),parent(nullptr),BF(0),Depth(0), bColor(true){}
	TreeNode(const T& Value) :value(Value), left(nullptr), right(nullptr), parent(nullptr), BF(0), Depth(0), Height(0), bColor(true) {}
	//Ϊƽ�������׼��
	TreeNode<T>* parent;
	int BF;
	int Depth;//��ȣ�����������
	int Height;//�߶ȣ�����������
	//�����
	bool bColor;//falseΪ��ɫ,trueΪ��ɫ
};
