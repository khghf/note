//红黑树的性质和结论：左根右 根叶黑 不红红 黑路同
//	左根右：因为红黑树最后是二叉排序树的形态，所以它的数据分布满足顺序性。左<根<右
//	根叶黑：根结点为黑色；叶子结点是空结点，只能为黑色。
//	不红红：即红色结点的父亲和孩子不可能为红色，一定为黑色
//	黑路同：对于每个结点，从该结点到其下任何一个叶子结点的路径上经过的黑色结点的个数是相同的
//	结论1：从根结点到叶子结点的最长路径不大于最短路径的2倍。
//	结论2：有n个结点的红黑树RBT的高度h<=2log(n+1). 
//红黑树的结点默认为红色，因为在插入时红色的影响比黑色小 
// 
//每插入一个结点之后都需要满足红黑树的性质 
//每插入一个结点只会出现两种破环红黑树的情况：
//	情况一：破环了根叶黑性质。根节点为黑“叶子结点”为黑，这里的“叶子结点”是指叶子结点下的空结点(叶子结点左右孩子)
//			解决方案：
//			插入结点为根节点----------直接变黑
//	情况二：破环了不红红性质。红色结点的左、右、父结点不能是红色结点
//			解决方案：
//			1、插入结点的叔结点为红------叔、父、爷三个结点变色，爷结点变为插入结点并再次调整
//			2、插入结点的叔结点为黑------叔结点为黑色旋转后再对旋转点和中心点变色
//										 这两个点指的是LL或RR情况下的点(通过LR或RL转变过来后的，或者本身就是)
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
		//情况一：破环了根叶黑性质。根节点为黑“叶子结点”为黑，这里的“叶子结点”是指叶子结点下的空结点(叶子结点左右孩子)
		//插入结点为根节点----------直接变黑
		//情况二：破环了不红红性质。红色结点的左、右、父结点不能是红色结点
		//1、插入结点的叔结点为红------叔、父、爷三个结点变色，爷结点变为插入结点并再次调整
		//2、插入结点的叔结点为黑------叔结点为黑色旋转后再对旋转点和中心点变色，这两个点指的是LL或RR情况下的点(通过LR或RL转变过来后的，或者本身就是)
		if (node == nullptr)return;
		TreeNode<T>* f = node->parent, * g = f->parent, * u = GetUncleNode(node);
		//情况一：是否破环了根叶黑性质
		if (__super::root_parent->left == node) { node->bColor = false; return; }
		//情况二：是否破环了不红红性质
		if (!(node->bColor == true && node->parent->bColor == true))return;
		if (u!=nullptr&&u->bColor)
		{
			//1、叔节点为红色
			f->bColor = !f->bColor;
			g->bColor = !g->bColor;
			u->bColor = !u->bColor;
			Adjust(g);
		}
		else
		{
			//2、叔节点为黑色
			bool f_left = IsLeftNodeInParent(f);
			bool n_left = IsLeftNodeInParent(node);
			if (f_left)
			{
				if (!n_left)
				{
					//LR型
					LeftRotate(f);
				}
				//LL型
				g->bColor = !g->bColor;
				g->left->bColor = !g->left->bColor;
				RightRotate(g);

			}
			else
			{
				if (n_left)
				{
					//RL型
					RightRotate(f);
				}
				//RR型
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
		//处理父节点
		if (node_parent != nullptr)
		{
			if (node_parent->left == node)node_parent->left = node_right;
			else if (node_parent->right == node)node_parent->right = node_right;
		}
		//处理结点
		node->right = node_right_left;
		node->parent = node_right;
		//处理右结点
		node_right->parent = node_parent;
		node_right->left = node;
		//处理 右_左 结点
		if (node_right_left != nullptr)node_right_left->parent = node;
	}
	void RightRotate(TreeNode<T>* node)
	{
		TreeNode<T>* node_parent = node->parent;
		TreeNode<T>* node_left = node->left;
		TreeNode<T>* node_left_right = node_left->right;
		//处理父节点
		if (node_parent != nullptr)
		{
			if (node_parent->left == node)node_parent->left = node_left;
			else if (node_parent->right == node)node_parent->right = node_left;
		}
		//处理结点
		node->left = node_left_right;
		node->parent = node_left;
		//处理左结点
		node_left->parent = node_parent;
		node_left->right = node;
		//处理 左_右 结点
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
		if (self->parent == nullptr)return false;//此情况下的结点为根节点
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