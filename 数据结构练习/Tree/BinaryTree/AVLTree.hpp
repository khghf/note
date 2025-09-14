//���������������ÿ���������������߶Ȳ�(BF)������һ
// //////////////////////////////////////////////////////////////////////////////////////////////////////
//                                   ��Ҫͨ����ת������ƽ��                                            //
//																									   //
//																									   //
//        LL��                                RR��                                                     //
//			a             	b                  	a                 	b								   //
//		   / 	����a		   / \ 				 \ 	    ����a	   / \ 								   //
//		  b     ---��	  c   a				      b     ---��	  a   d								   //
//       / \			       \			     / \			 /      							   //
//      c   d			        d			    c   d			c        							   //
//																									   //
//																									   //
//        																							   //
//         LR��                                              RL��                         			   //
//		 	 a             	a                          		  a             	a           		   //
//		    / 	 ����b	   /  				 				   \ 	 ����b	     \ 					   //
//		   b     ---��	  d   	��ΪLL��			 		    b     ---��	      c	    ��ΪLL��	   //
//		    \			 /    			     				   /		     	   \				   //
//		     c			b        			 				  c			            b				   //
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include"iostream"
#include"structs.hpp"
#include"BaseBinaryTree.hpp"
using namespace std;
template<class T>
class AVL :public BaseBinaryTree<T>
{
public:
	AVL() {}
	AVL(const T arr[], int size)
	{
		__super::Init(arr, size);
	}
protected:
	virtual void Insert(const T& Value, TreeNode<T>*& Node)override//��ΪҪ�޸�ָ������Ҫ��������
	{
		if (Value <= Node->value)
		{
			//С�ڵ��ڸ����������ݹ�����ҵ�һ���յ���������
			if (Node->left != nullptr)Insert(Value, Node->left);
			else
			{
				Node->left = new TreeNode<T>(Value);
				Node->left->parent = Node;
				Node->left->Height = __super::NodeHeight(Node->left);
			}
		}
		else
		{
			//���ڸ���������ҵݹ�����ҵ�һ���յ���������
			if (Node->right != nullptr)Insert(Value, Node->right);
			else
			{
				Node->right = new TreeNode<T>(Value);
				Node->right->parent = Node;
				Node->right->Height = __super::NodeHeight(Node->right);
			}
		}
		Node->Height = __super::NodeHeight(Node);
		//�������ƽ������
		Node->BF = CalcBF(Node);
		if (Node->BF >= 2)
		{
			cout << "��תǰ��";  __super::LevelPrint();
			if (Node->left->BF == -1)
			{
				//LR
				LeftRotate(Node->left);
			}
			RightRotate(Node);
			cout << "��ת��";  __super::LevelPrint();

		}
		if (Node->BF <= -2)
		{
			cout << "��תǰ��";  __super::LevelPrint();
			if (Node->right->BF == 1)
			{
				//RF
				RightRotate(Node->right);
			}
			LeftRotate(Node);
			cout << "��ת��";  __super::LevelPrint();
		}
	}
public:
	int CalcBF(TreeNode<T>* node)
	{
		//return __super::NodeHeight(node->left) - __super::NodeHeight(node->right);
		if (node->left == nullptr && node->right == nullptr)return 0;
		else if (node->left != nullptr && node->right == nullptr) return node->left->Height;
		else if (node->left == nullptr && node->right != nullptr) return -node->right->Height;
		else return node->left->Height - node->right->Height;
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

		//��������
		node->BF = CalcBF(node);
		node->Height =__super::NodeHeight(node);
		node_right->BF = CalcBF(node_right);
		node_right->Height = __super::NodeHeight(node_right);
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

		node->BF = CalcBF(node);
		node->Height = __super::NodeHeight(node);
		node_left->BF = CalcBF(node_left);
		node_left->Height = __super::NodeHeight(node_left);
	}
	void Remove(const T& value)
	{
		TreeNode<T>* node = Search(value);
		if (node == nullptr) { cout << "Remove:�����ڸýڵ�"; return; }
		TreeNode<T>* node_parent = node->parent;
		TreeNode<T>* node_left = node->left;
		TreeNode<T>* node_right = node->right;
		TreeNode<T>* newnode = nullptr;
		if (node_left!=nullptr&&node_right==nullptr)
		{
			//ֻ�������������
			node_left->parent = node_parent;
			newnode = node_left;
			if (node_parent->left == node)node_parent->left = node_left;
			if (node_parent->right == node)node_parent->right = node_left;
		}
		else if (node_left == nullptr&&node_right!=nullptr)
		{
			//ֻ�������������
			node_right->parent = node_parent;
			newnode = node->right;
			if (node_parent->left == node)node_parent->left = node_right;
			if (node_parent->right == node)node_parent->right = node_right;
		}
		else if(node_left != nullptr && node_right != nullptr)
		{
			//���������������,�����������������ֵ������滻
			TreeNode<T>* node_max = MaxNode(node_left);//���ֵ��������������������û��������
			TreeNode<T>* node_max_left = node_max->left;
			TreeNode<T>* node_max_parent = node_max->parent;
			newnode = node_max;
			node_max->parent = node->parent;
			node_max->left = node_left!=node_max?node_left:nullptr;//���ֵ������Ҫɾ����������ʱ�����ֵ���������ÿ�
			node_max->right = node_right;
			if (node_parent->left == node)node_parent->left = node_max;
			if (node_parent->right == node)node_parent->right = node_max;

			if (node_max_left != nullptr)
			{
				node_max_left->parent = node_max_parent;
			}
			if (node_max_parent->left == node_max)node_max_parent->left = node_max_left;
			if (node_max_parent->right == node_max)node_max_parent->right = node_max_left;
		}
		else
		{
			//û���������������
			if (node_parent->left == node)node_parent->left = nullptr;
			if (node_parent->right == node)node_parent->right = nullptr;
		}
		delete node;
		node = nullptr;
		newnode = newnode == nullptr ? node_parent : newnode;
		ReCalcAllNodeHeight(__super::root_parent->left);
		while (newnode != __super::root_parent)
		{
			newnode->BF = CalcBF(newnode);
			if (newnode->BF <= -2)
			{
				if (newnode->right->BF == 1)
				{
					RightRotate(newnode->right);
				}
				LeftRotate(newnode);
			}
			if (newnode->BF >= 2)
			{
				if (newnode->left->BF == -1)
				{
					LeftRotate(newnode->left);
				}
				RightRotate(newnode);
			}
			newnode = newnode->parent;
		}
	}
	TreeNode<T>* Search(const T& value)const
	{
		TreeNode<T>* temp = __super::root_parent->left;
		while (temp != nullptr)
		{
			if (value < temp->value)
			{
				temp = temp->left;
			}
			else if(value > temp->value)
			{
				temp = temp->right;
			}
			else
			{
				return temp;
			}
		}
		cout << "û�иýڵ㣺" << value << endl;
		return nullptr;
	}
	TreeNode<T>* MinNode()const
	{
		return MinNode(__super::root_parent->left);
	}
	TreeNode<T>* MaxNode()const
	{
		return MaxNode(__super::root_parent->left);
	}
	int GetHeight(const T& value)const
	{
		TreeNode<T>* temp = Search(value);
		if (!temp) { return 0; }
		return temp->Height;
	}
protected:
	int ReCalcAllNodeHeight(TreeNode<T>*root)
	{
		if (root != nullptr)
		{
			int l = ReCalcAllNodeHeight(root->left);
			int r = ReCalcAllNodeHeight(root->right);
			int re = l >= r ? ++l : ++r;
			root->Height = re;
			return re;
		}
		return 0;
	}
	TreeNode<T>* MinNode(TreeNode<T>*node)const
	{
		if (node == nullptr)return nullptr;
		if (node->left == nullptr)return node;
		TreeNode<T>* temp = node;
		TreeNode<T>* prevnode = nullptr;
		while (temp != nullptr)
		{
			prevnode = temp;
			temp = temp->left;
		}
		return prevnode;
	}
	TreeNode<T>* MaxNode(TreeNode<T>* node)const
	{
		if (node == nullptr)return nullptr;
		if (node->right == nullptr)return node;
		TreeNode<T>* temp = node;
		TreeNode<T>* prevnode = nullptr;
		while (temp != nullptr)
		{
			prevnode = temp;
			temp = temp->right;
		}
		return prevnode;
	}
};