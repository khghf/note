//����������ʺͽ��ۣ������ ��Ҷ�� ����� ��·ͬ
//	����ң���Ϊ���������Ƕ�������������̬�������������ݷֲ�����˳���ԡ���<��<��
//	��Ҷ�ڣ������Ϊ��ɫ��Ҷ�ӽ���ǿս�㣬ֻ��Ϊ��ɫ��
//	����죺����ɫ���ĸ��׺ͺ��Ӳ�����Ϊ��ɫ��һ��Ϊ��ɫ
//	��·ͬ������ÿ����㣬�Ӹý�㵽�����κ�һ��Ҷ�ӽ���·���Ͼ����ĺ�ɫ���ĸ�������ͬ��
//	����1���Ӹ���㵽Ҷ�ӽ����·�����������·����2����
//	����2����n�����ĺ����RBT�ĸ߶�h<=2log(n+1). 
//������Ľ��Ĭ��Ϊ��ɫ����Ϊ�ڲ���ʱ��ɫ��Ӱ��Ⱥ�ɫС 
// 
//ÿ����һ�����֮����Ҫ�������������� 
//ÿ����һ�����ֻ����������ƻ�������������
//	���һ���ƻ��˸�Ҷ�����ʡ����ڵ�Ϊ�ڡ�Ҷ�ӽ�㡱Ϊ�ڣ�����ġ�Ҷ�ӽ�㡱��ָҶ�ӽ���µĿս��(Ҷ�ӽ�����Һ���)
//			���������
//			������Ϊ���ڵ�----------ֱ�ӱ��
//	��������ƻ��˲�������ʡ���ɫ�������ҡ�����㲻���Ǻ�ɫ���
//			���������
//			1�������������Ϊ��------�塢����ү��������ɫ��ү����Ϊ�����㲢�ٴε���
//			2�������������Ϊ��------����Ϊ��ɫ��ת���ٶ���ת������ĵ��ɫ
//										 ��������ָ����LL��RR����µĵ�(ͨ��LR��RLת�������ģ����߱������)
// 
// 
// 
// 
//



#pragma once
#include"iostream"
#include"structs.hpp"
#include"BaseBinaryTree.hpp"
using namespace std;
template<class T>
class RBT :public BaseBinaryTree<T>
{
public:
	RBT() {}
	RBT(const T arr[], int size)
	{
		__super::Init(arr, size);
	}
	virtual void Insert(const T& Value)
	{
		if (__super::root_parent->left == nullptr)
		{
			__super::root_parent->left = new TreeNode<T>(Value);
			__super::root_parent->left->parent = __super::root_parent;
			__super::root_parent->left->bColor = false;
			return;
		}
		Insert(Value, __super::root_parent->left);
		__super::size++;
	}
protected:
	virtual void Insert(const T& Value, TreeNode<T>*& Node)override
	{
		if (Value <= Node->value)
		{
			if (Node->left != nullptr)Insert(Value, Node->left);
			else
			{
				Node->left = new TreeNode<T>(Value);
				Node->left->parent = Node;
				Adjust(Node->left);

			}
		}
		else
		{
			if (Node->right != nullptr)Insert(Value, Node->right);
			else
			{
				Node->right = new TreeNode<T>(Value);
				Node->right->parent = Node;
				Adjust(Node->right);
			}
		}
	}
	void Adjust(TreeNode<T>*&node)
	{
		//���һ���ƻ��˸�Ҷ�����ʡ����ڵ�Ϊ�ڡ�Ҷ�ӽ�㡱Ϊ�ڣ�����ġ�Ҷ�ӽ�㡱��ָҶ�ӽ���µĿս��(Ҷ�ӽ�����Һ���)
		//������Ϊ���ڵ�----------ֱ�ӱ��
		//��������ƻ��˲�������ʡ���ɫ�������ҡ�����㲻���Ǻ�ɫ���
		//1�������������Ϊ��------�塢����ү��������ɫ��ү����Ϊ�����㲢�ٴε���
		//2�������������Ϊ��------����Ϊ��ɫ��ת���ٶ���ת������ĵ��ɫ����������ָ����LL��RR����µĵ�(ͨ��LR��RLת�������ģ����߱������)
		if (node == nullptr)return;
		TreeNode<T>* f = node->parent, * g = f->parent, * u = GetUncleNode(node);
		//���һ���Ƿ��ƻ��˸�Ҷ������
		if (__super::root_parent->left == node) { node->bColor = false; return; }
		//��������Ƿ��ƻ��˲��������
		if (!(node->bColor == true && node->parent->bColor == true))return;
		if (u!=nullptr&&u->bColor)
		{
			//1����ڵ�Ϊ��ɫ
			f->bColor = !f->bColor;
			g->bColor = !g->bColor;
			u->bColor = !u->bColor;
			Adjust(g);
		}
		else
		{
			//2����ڵ�Ϊ��ɫ
			bool f_left = IsLeftNodeInParent(f);
			bool n_left = IsLeftNodeInParent(node);
			if (f_left)
			{
				if (!n_left)
				{
					//LR��
					LeftRotate(f);
				}
				//LL��
				g->bColor = !g->bColor;
				g->left->bColor = !g->left->bColor;
				RightRotate(g);

			}
			else
			{
				if (n_left)
				{
					//RL��
					RightRotate(f);
				}
				//RR��
				g->bColor = !g->bColor;
				g->right->bColor = !g->right->bColor;
				LeftRotate(g);
			}
		}
	}
	void LeftRotate(TreeNode<T>* node)
	{
		TreeNode<T>* node_parent = node->parent;
		TreeNode<T>* node_right = node->right;
		TreeNode<T>* node_right_left = node_right->left;
		//�����ڵ�
		if (node_parent != nullptr)
		{
			if (node_parent->left == node)node_parent->left = node_right;
			else if (node_parent->right == node)node_parent->right = node_right;
		}
		//������
		node->right = node_right_left;
		node->parent = node_right;
		//�����ҽ��
		node_right->parent = node_parent;
		node_right->left = node;
		//���� ��_�� ���
		if (node_right_left != nullptr)node_right_left->parent = node;
	}
	void RightRotate(TreeNode<T>* node)
	{
		TreeNode<T>* node_parent = node->parent;
		TreeNode<T>* node_left = node->left;
		TreeNode<T>* node_left_right = node_left->right;
		//�����ڵ�
		if (node_parent != nullptr)
		{
			if (node_parent->left == node)node_parent->left = node_left;
			else if (node_parent->right == node)node_parent->right = node_left;
		}
		//������
		node->left = node_left_right;
		node->parent = node_left;
		//��������
		node_left->parent = node_parent;
		node_left->right = node;
		//���� ��_�� ���
		if (node_left_right != nullptr)node_left_right->parent = node;
	}
public:
	bool IsLeftNodeInParent(TreeNode<T>* self)const
	{
		if (self->parent == nullptr)return false;
		return self->parent->left == self ? true : false;
	}
	bool IsRightNodeInParent(TreeNode<T>* self)const
	{
		if (self->parent == nullptr)return false;
		return self->parent->right == self ? true : false;
	}
	bool ColorOfUncle(TreeNode<T>* self)const
	{
		if (self->parent == nullptr)return false;//������µĽ��Ϊ���ڵ�
		TreeNode<T>* Uncle = GetUncleNode(self);
		if (Uncle== nullptr)return false;
		else
		{
			return Uncle->bColor;
		}
	}
	TreeNode<T>*& GetUncleNode(TreeNode<T>* self)const
	{
		TreeNode<T>* u = nullptr;
		if (self->parent == nullptr|| self->parent->parent==nullptr)return u;
		return IsLeftNodeInParent(self->parent) ? self->parent->parent->right : self->parent->parent->left;
	}
};