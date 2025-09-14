//特性:
//平衡：所有叶子结点都在同一层
//有序：左边的 < 中间的 < 右边的
//		多路：对于m阶B树的每个结点
//			最多有：m个分支, 存储m - 1个元素
//			最少有：ceil(m / 2)(向上取整)个分支ceil(m / 2) - 1个元素
//		根节点最少有2个分支，1个元素



/*插入操作
			一、遍历找到要插入的结点
			二、直接插入
			三、判断是否溢出
			溢出：
			第一步、找到溢出结点的中间元素，将其左右部分分割成两个结点，如果溢出结点是指针记得释放空间
			第二步、将中间元素上溢到父节点
			若没有父结点。
			直接创建一个父结点，若溢出结点为根节点则要改变根节点
			的指向。
			将分割出来的两个结点加入父节点的孩子结点数组中，记住这里不能打乱孩子结点数组的顺序
			从左到右的孩子结点的元素值是逐渐递增的
			第三步、判断父节点是否溢出*/
/*关于B树的删除操作，大体分为两种情况
一：删除的是叶子结点元素
	1、删除后仍满足最少元素的下限：直接删除然后返回
	2、删除后不满足最少元素的下限：
		从兄弟结点借：
			(1)若兄弟结点借出元素后自己还满足最少元素的下限。
				第一步、借的元素给父结点。
				第二步、从父结点的元素中分一个合适的元素下来。
				第三步、插入父结点分配下来的元素。
			(2)若兄弟结点借出后不满足最少元素的下限。
				第一步、从父结点的元素中分一个合适的元素下来与兄弟结点和自己(记得不要把要删除元素合并了)。
				第二步、将自身剩下的元素和父结点分配下来的元素插入兄弟结点中，这样就不用new一个结点了。搞好后
						记得释放结点空间。
				第三步、递归调用删除函数，删除父结点分配下来的元素。
二：删除的不是叶子结点元素			
	1、从后继的孩子结点中拿一个元素来替换要删除的元素,若没有后继孩子结点则直接删除然后返回
	2、调用删除函数，从孩子结点中删除替换元素，到最后就会变成成删除叶子结点元素的情况
*/
#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
template<class T>
struct BTreeNode
{
	vector<BTreeNode<T>*>childs;
	vector<T>values;
	BTreeNode<T>* parent;
	const int M=3;//阶数
	BTreeNode() :parent(nullptr) {
		childs.reserve(M + 1);
		values.reserve(M);
	}
	BTreeNode(T value) :parent(nullptr){
		childs.reserve(M);
		values.reserve(M);
		values.push_back(value);
	}
};
template<class T>
class BTree
{
protected:
	BTreeNode<T>* root;
public:
	BTree() :root(nullptr) {}
	BTree(const T arr[], const int& size)
	{
		for (int i = 0; i < size; i++)
		{
			Insert(arr[i]);
		}
	}
	~BTree()
	{
		Destory();
	}
	void Insert(const T& value)
	{
		/*插入操作
			一、遍历找到要插入的结点
			二、直接插入
			三、判断是否溢出
			溢出：
			第一步、找到溢出结点的中间元素，将其左右部分分割成两个结点，如果溢出结点是指针记得释放空间
			第二步、将中间元素上溢到父节点
			若没有父结点。
			直接创建一个父结点，若溢出结点为根节点则要改变根节点
			的指向。
			将分割出来的两个结点加入父节点的孩子结点数组中，记住这里不能打乱孩子结点数组的顺序
			从左到右的孩子结点的元素值是逐渐递增的
			第三步、判断父节点是否溢出*/

		if (root == nullptr)
		{
			root = new BTreeNode<T>();
			root->values.push_back(value);
			return;
		}
		Insert(value, root);
	}
	void Remove(const T& value)
	{
		//关于B树的删除操作，大体分为两种情况
		//一：删除的是叶子结点元素
		//	1、删除后仍满足最少元素的下限：直接删除然后返回
		//	2、删除后不满足最少元素的下限：
		//	   从兄弟结点借：
		//				(1)若兄弟结点借出元素后自己还满足最少元素的下限。
		//						第一步、借的元素给父结点。
		//						第二步、从父结点的元素中分一个合适的元素下来。
		//						第三步、插入父结点分配下来的元素。
		//				(2)若兄弟结点借出后不满足最少元素的下限。
		//						第一步、从父结点的元素中分一个合适的元素下来与兄弟结点和自己(记得不要把要删除元素合并了)。
		//						第二步、将自身剩下的元素和父结点分配下来的元素插入兄弟结点中，这样就不用new一个结点了。搞好后
		//								记得释放结点空间。
		//						第三步、递归调用删除函数，删除父结点分配下来的元素。
		//二：删除的不是叶子结点元素			
		//	1、从后继的孩子结点中拿一个元素来替换要删除的元素
		//	2、调用删除函数，从孩子结点中删除替换元素，到最后就会变成成删除叶子结点元素的情况
		
		//找到要删除的值所在的结点
		Remove(value, Search(value));
	}
	BTreeNode<T>* Search(const T& value)
	{
		if (root == nullptr)return nullptr;
		BTreeNode<T>* ret = root;
		while (ret != nullptr)
		{
			if (value < ret->values[0])
			{
				if (ret->childs.empty())return nullptr;
				ret = ret->childs[0];
			}
			else if (value > *(ret->values.end() - 1))
			{
				if (ret->childs.empty())return nullptr;
				ret = *(ret->childs.end() - 1);
			}
			else
			{
				if (binary_search(ret->values.begin(), ret->values.end(), value))return ret;
				else
				{
					if (ret->childs.empty())return nullptr;
					for (int i = 0; i < ret->values.size(); i++)
					{
						if (ret->values[i] > value)
						{
							ret = ret->childs[i];
							break;
						}
					}
				}
			}
		}
		return ret;
	}
	void LevelPrint()
	{
		queue<BTreeNode<T>*>temp;
		temp.push(this->root);
		while (!temp.empty())
		{
			BTreeNode<T>* node = temp.front();
			temp.pop();
			if (node != nullptr)
			{
				cout << "|";
				for (auto in : node->values)
				{
					cout << in << " ";
				}
				for (auto in : node->childs)
				{
					temp.push(in);
				}
			}
		}
		cout << "|";
		cout << endl;
	}
	void Destory()
	{
		if (root == nullptr)return;
		queue<BTreeNode<T>*>q;
		q.push(root);
		while (!q.empty())
		{
			BTreeNode<T>* node = q.front();
			q.pop();
			for (auto in : node->childs)
			{
				q.push(in);
			}
			delete node;
		}
		root = nullptr;
	}
protected:
	void Insert(const T& value, BTreeNode<T>*& node)
	{

		if (node != nullptr)
		{
			//先判断是否有孩子结点
			if (node->childs.size()<=0)
			{
				//没有则插入该节点的元素中
				InsertToNode(value, node);
			}
			else
			{
				//有孩子结点
				if (value <= node->values[0])
				{
					//小于等于最小值往最左边走
					Insert(value, node->childs[0]);
				}
				else if (value > node->values[node->values.size() - 1])
				{
					//大于最大值往最右边走
					Insert(value, *(node->childs.end()-1));
				}
				else
				{
					//大于最小值，小于等于最大值
					int i = 0;
					for (;i < node->values.size(); i++)
					{
						if (value < node->values[i])break;
					}
					//往比目标值大一点的元素的左边走
					Insert(value, node->childs[i]);
				}
			}
		}
	}
	void InsertToNode(const T& value,BTreeNode<T>* targetnode)
	{
		vector<T>& v = targetnode->values;
		v.push_back(value);
		sort(v.begin(), v.end());
		Adjust(targetnode);
	}
	void Remove(const T& value, BTreeNode<T>* node)
	{
		//1、删除的是叶子结点的元素
		if (node->childs.size() <= 0)
		{
			if (node->values.size() > ceil(root->M / 2.f) - 1)
			{	//删除后仍满足下限
				//直接删除
				remove(node->values.begin(), node->values.end(), value);
				node->values.erase(node->values.end() - 1);
				return;
			}
			else
			{
				//找左/右兄弟借元素
				BTreeNode<T>* LeftBrother = nullptr;
				BTreeNode<T>* RightBrother = nullptr;
				BTreeNode<T>* TargetBrother = nullptr;
				int ParentChilds = node->parent->childs.size();
				for (int i = 0; i < ParentChilds; i++)
				{
					if (node->parent->childs[i] == node)
					{
						//注意当node为第1个或最后一个孩子时，LeftBrother/RightBrother 就等于node
						LeftBrother = node->parent->childs[max(0, i - 1)];
						RightBrother = node->parent->childs[min(ParentChilds - 1, i + 1)];
						break;
					}
				}
				bool bIsLeftBrother = false;
				if (LeftBrother == node && RightBrother != node)
				{
					//只有右兄弟,没有左兄弟
					TargetBrother = RightBrother;
					bIsLeftBrother = false;
				}
				else if (RightBrother == node && LeftBrother != node)
				{
					//只有左兄弟,没有右兄弟
					TargetBrother = LeftBrother;
					bIsLeftBrother = true;
				}
				else
				{
					//有左兄弟和右兄弟，默认选择左兄弟
					TargetBrother = LeftBrother;
					bIsLeftBrother = true;
				}

				if (TargetBrother != nullptr)
				{
					if (TargetBrother->values.size() > ceil(root->M / 2.f) - 1)
					{	//若兄弟结点借值后仍满足下限

						T BrotherValue;
						T ParentValue;
						if (bIsLeftBrother)
						{//借的是左兄弟的值

							BrotherValue = *(TargetBrother->values.end() - 1);
							int index = 0;
							for (; index < node->parent->values.size(); index++)
							{
								if (node->parent->values[index] > value)break;
							}
							index--;
							ParentValue = node->parent->values[index];
						}
						else
						{//借的是右兄弟的值

							BrotherValue = *(TargetBrother->values.begin());
							int index = 0;
							for (; index < node->parent->values.size(); index++)
							{
								if (node->parent->values[index] > value)break;
							}
							ParentValue = node->parent->values[index];
						}
						remove(TargetBrother->values.begin(), TargetBrother->values.end(), BrotherValue);
						TargetBrother->values.erase(TargetBrother->values.end() - 1);
						remove(node->parent->values.begin(), node->parent->values.end(), ParentValue);
						node->parent->values.erase(node->parent->values.end() - 1);
						remove(node->values.begin(), node->values.end(), value);
						node->values.erase(node->values.end() - 1);
						InsertToNode(BrotherValue, node->parent);
						InsertToNode(ParentValue, node);
					}
					else
					{//若兄弟结点借值后不满足下限，从父节点借一个元素下来并与兄弟结点合并

						T ParentValue;
						if (value < *(node->parent->values.begin()))ParentValue = *(node->parent->values.begin());
						else if (value > *(node->parent->values.end() - 1))ParentValue = *(node->parent->values.end() - 1);
						else
						{
							int index = 0;
							for (; index < node->parent->values.size(); index++)
							{
								T pv = node->parent->values[index];
								if (bIsLeftBrother)
								{
									if (*(TargetBrother->values.end() - 1) < pv && pv < *(node->values.begin()))
									{
										ParentValue = pv;
										break;
									}
								}
								else
								{
									if (*(node->values.end() - 1) < pv && pv < *(TargetBrother->values.begin()))
									{
										ParentValue = pv;
										break;
									}
								}
							}
						}
						
						for (auto in : node->values)
						{
							if(in!=value)InsertToNode(in, TargetBrother);
						}
						InsertToNode(ParentValue, TargetBrother);
						//从父节点的孩子结点数组中移除自己
						remove(node->parent->childs.begin(), node->parent->childs.end(), node);
						node->parent->childs.erase(node->parent->childs.end() - 1);

						Remove(ParentValue, node->parent);
						//释放内存
						delete node; node = nullptr;
					}
				}
			}
		}
		//2、删除的不是叶子结点的元素
		else
		{
			remove(node->values.begin(), node->values.end(), value);
			node->values.erase(node->values.end() - 1);
			//从后继结点中拿一个元素代替
			T childvalue;
			BTreeNode<T>* child = nullptr;
			for (int i = 0; i < node->childs.size(); i++)
			{
				if (value < *(node->childs[i]->values.begin()))
				{

					child = node->childs[i];
					childvalue = *(child->values.begin());
					//有后继元素的情况下才会插入，没有就直接删除没有插入
					InsertToNode(childvalue, node);
					Remove(childvalue, child);
					break;
				}
			}
		}
	}
	void Adjust(BTreeNode<T>*node)
	{
		//判断是否溢出
		if (node->values.size() > node->M-1)
		{
			int mid = node->values.size() / 2;
			BTreeNode<T>* leftnode = new BTreeNode<T>();
			BTreeNode<T>* rightnode = new BTreeNode<T>();
			//将要上溢的元素的左右两侧分割开来
			for (int i = 0; i < node->values.size(); i++)
			{
				//分割值
				if (i < mid)leftnode->values.push_back(node->values[i]);
				if(i>mid)rightnode->values.push_back(node->values[i]);
			}
			for (int i = 0; i < node->childs.size(); i++)
			{
				//分割其下面的孩子结点
				if (*(node->childs[i]->values.end() - 1) <= node->values[mid])
				{
					//孩子结点拥有的值中的最大值小于等于中间值的划分到左侧
					leftnode->childs.push_back(node->childs[i]);
					node->childs[i]->parent = leftnode;
				}
				else
				{
					//孩子结点结点拥有的值中的最小值大于中间值的划分到右侧
					rightnode->childs.push_back(node->childs[i]);
					node->childs[i]->parent = rightnode;
				}
			}
			if (node->parent == nullptr)
			{
				//没有父节点的情况下直接new一个父结点出来
				BTreeNode<T>* rootnode = new BTreeNode<T>(node->values[mid]);
				rootnode->childs.push_back(leftnode);
				rootnode->childs.push_back(rightnode);
				leftnode->parent = rootnode;
				rightnode->parent = rootnode;
				node->parent = rootnode;
				if (node == this->root)this->root = rootnode;//上溢的是树的根结点时重新改变根结点的指向
			}
			else
			{
				//有父节点
				int indexInparent = 0;
				vector<BTreeNode<T>*>& parentchailds = node->parent->childs;
				for (;indexInparent < parentchailds.size(); indexInparent++)
				{
					if (parentchailds[indexInparent] == node)break;
				}
				//将父节点的左右孩子以自身为界限进行左右分割，
				vector<BTreeNode<T>*>childsLeft;
				vector<BTreeNode<T>*>childsRight;
				for (int i=0; i < parentchailds.size(); i++)
				{
					if (i < indexInparent)childsLeft.push_back(parentchailds[i]);
					if (i > indexInparent)childsRight.push_back(parentchailds[i]);
				}
				//先清除再按次序插入，以便后面插入的新的孩子结点不会打乱孩子结点的排序
				parentchailds.clear();
				for (int i = 0; i < childsLeft.size(); i++)
				{
					parentchailds.push_back(childsLeft[i]);
				}
				parentchailds.push_back(leftnode);
				leftnode->parent = node->parent;
				parentchailds.push_back(rightnode);
				rightnode->parent = node->parent;
				for (int i = 0; i < childsRight.size(); i++)
				{
					parentchailds.push_back(childsRight[i]);
				}
				//将值上溢至父结点
				InsertToNode(node->values[mid], node->parent);
			}
			delete node;
			node = nullptr;
		}
	}
	int IndexInParentChilds(BTreeNode<T>* node)const
	{
		if (node->parent == nullptr)return -1;
		for (int i = 0; i < node->parent->childs.size(); i++)
		{
			if (node == node->parent->childs[i])return i;
		}
	}
};