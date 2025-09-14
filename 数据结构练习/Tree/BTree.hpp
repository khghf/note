//����:
//ƽ�⣺����Ҷ�ӽ�㶼��ͬһ��
//������ߵ� < �м�� < �ұߵ�
//		��·������m��B����ÿ�����
//			����У�m����֧, �洢m - 1��Ԫ��
//			�����У�ceil(m / 2)(����ȡ��)����֧ceil(m / 2) - 1��Ԫ��
//		���ڵ�������2����֧��1��Ԫ��



/*�������
			һ�������ҵ�Ҫ����Ľ��
			����ֱ�Ӳ���
			�����ж��Ƿ����
			�����
			��һ�����ҵ���������м�Ԫ�أ��������Ҳ��ַָ��������㣬�����������ָ��ǵ��ͷſռ�
			�ڶ��������м�Ԫ�����絽���ڵ�
			��û�и���㡣
			ֱ�Ӵ���һ������㣬��������Ϊ���ڵ���Ҫ�ı���ڵ�
			��ָ��
			���ָ���������������븸�ڵ�ĺ��ӽ�������У���ס���ﲻ�ܴ��Һ��ӽ�������˳��
			�����ҵĺ��ӽ���Ԫ��ֵ���𽥵�����
			���������жϸ��ڵ��Ƿ����*/
/*����B����ɾ�������������Ϊ�������
һ��ɾ������Ҷ�ӽ��Ԫ��
	1��ɾ��������������Ԫ�ص����ޣ�ֱ��ɾ��Ȼ�󷵻�
	2��ɾ������������Ԫ�ص����ޣ�
		���ֵܽ��裺
			(1)���ֵܽ����Ԫ�غ��Լ�����������Ԫ�ص����ޡ�
				��һ�������Ԫ�ظ�����㡣
				�ڶ������Ӹ�����Ԫ���з�һ�����ʵ�Ԫ��������
				�����������븸������������Ԫ�ء�
			(2)���ֵܽ��������������Ԫ�ص����ޡ�
				��һ�����Ӹ�����Ԫ���з�һ�����ʵ�Ԫ���������ֵܽ����Լ�(�ǵò�Ҫ��Ҫɾ��Ԫ�غϲ���)��
				�ڶ�����������ʣ�µ�Ԫ�غ͸�������������Ԫ�ز����ֵܽ���У������Ͳ���newһ������ˡ���ú�
						�ǵ��ͷŽ��ռ䡣
				���������ݹ����ɾ��������ɾ����������������Ԫ�ء�
����ɾ���Ĳ���Ҷ�ӽ��Ԫ��			
	1���Ӻ�̵ĺ��ӽ������һ��Ԫ�����滻Ҫɾ����Ԫ��,��û�к�̺��ӽ����ֱ��ɾ��Ȼ�󷵻�
	2������ɾ���������Ӻ��ӽ����ɾ���滻Ԫ�أ������ͻ��ɳ�ɾ��Ҷ�ӽ��Ԫ�ص����
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
	const int M=3;//����
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
		/*�������
			һ�������ҵ�Ҫ����Ľ��
			����ֱ�Ӳ���
			�����ж��Ƿ����
			�����
			��һ�����ҵ���������м�Ԫ�أ��������Ҳ��ַָ��������㣬�����������ָ��ǵ��ͷſռ�
			�ڶ��������м�Ԫ�����絽���ڵ�
			��û�и���㡣
			ֱ�Ӵ���һ������㣬��������Ϊ���ڵ���Ҫ�ı���ڵ�
			��ָ��
			���ָ���������������븸�ڵ�ĺ��ӽ�������У���ס���ﲻ�ܴ��Һ��ӽ�������˳��
			�����ҵĺ��ӽ���Ԫ��ֵ���𽥵�����
			���������жϸ��ڵ��Ƿ����*/

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
		//����B����ɾ�������������Ϊ�������
		//һ��ɾ������Ҷ�ӽ��Ԫ��
		//	1��ɾ��������������Ԫ�ص����ޣ�ֱ��ɾ��Ȼ�󷵻�
		//	2��ɾ������������Ԫ�ص����ޣ�
		//	   ���ֵܽ��裺
		//				(1)���ֵܽ����Ԫ�غ��Լ�����������Ԫ�ص����ޡ�
		//						��һ�������Ԫ�ظ�����㡣
		//						�ڶ������Ӹ�����Ԫ���з�һ�����ʵ�Ԫ��������
		//						�����������븸������������Ԫ�ء�
		//				(2)���ֵܽ��������������Ԫ�ص����ޡ�
		//						��һ�����Ӹ�����Ԫ���з�һ�����ʵ�Ԫ���������ֵܽ����Լ�(�ǵò�Ҫ��Ҫɾ��Ԫ�غϲ���)��
		//						�ڶ�����������ʣ�µ�Ԫ�غ͸�������������Ԫ�ز����ֵܽ���У������Ͳ���newһ������ˡ���ú�
		//								�ǵ��ͷŽ��ռ䡣
		//						���������ݹ����ɾ��������ɾ����������������Ԫ�ء�
		//����ɾ���Ĳ���Ҷ�ӽ��Ԫ��			
		//	1���Ӻ�̵ĺ��ӽ������һ��Ԫ�����滻Ҫɾ����Ԫ��
		//	2������ɾ���������Ӻ��ӽ����ɾ���滻Ԫ�أ������ͻ��ɳ�ɾ��Ҷ�ӽ��Ԫ�ص����
		
		//�ҵ�Ҫɾ����ֵ���ڵĽ��
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
			//���ж��Ƿ��к��ӽ��
			if (node->childs.size()<=0)
			{
				//û�������ýڵ��Ԫ����
				InsertToNode(value, node);
			}
			else
			{
				//�к��ӽ��
				if (value <= node->values[0])
				{
					//С�ڵ�����Сֵ���������
					Insert(value, node->childs[0]);
				}
				else if (value > node->values[node->values.size() - 1])
				{
					//�������ֵ�����ұ���
					Insert(value, *(node->childs.end()-1));
				}
				else
				{
					//������Сֵ��С�ڵ������ֵ
					int i = 0;
					for (;i < node->values.size(); i++)
					{
						if (value < node->values[i])break;
					}
					//����Ŀ��ֵ��һ���Ԫ�ص������
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
		//1��ɾ������Ҷ�ӽ���Ԫ��
		if (node->childs.size() <= 0)
		{
			if (node->values.size() > ceil(root->M / 2.f) - 1)
			{	//ɾ��������������
				//ֱ��ɾ��
				remove(node->values.begin(), node->values.end(), value);
				node->values.erase(node->values.end() - 1);
				return;
			}
			else
			{
				//����/���ֵܽ�Ԫ��
				BTreeNode<T>* LeftBrother = nullptr;
				BTreeNode<T>* RightBrother = nullptr;
				BTreeNode<T>* TargetBrother = nullptr;
				int ParentChilds = node->parent->childs.size();
				for (int i = 0; i < ParentChilds; i++)
				{
					if (node->parent->childs[i] == node)
					{
						//ע�⵱nodeΪ��1�������һ������ʱ��LeftBrother/RightBrother �͵���node
						LeftBrother = node->parent->childs[max(0, i - 1)];
						RightBrother = node->parent->childs[min(ParentChilds - 1, i + 1)];
						break;
					}
				}
				bool bIsLeftBrother = false;
				if (LeftBrother == node && RightBrother != node)
				{
					//ֻ�����ֵ�,û�����ֵ�
					TargetBrother = RightBrother;
					bIsLeftBrother = false;
				}
				else if (RightBrother == node && LeftBrother != node)
				{
					//ֻ�����ֵ�,û�����ֵ�
					TargetBrother = LeftBrother;
					bIsLeftBrother = true;
				}
				else
				{
					//�����ֵܺ����ֵܣ�Ĭ��ѡ�����ֵ�
					TargetBrother = LeftBrother;
					bIsLeftBrother = true;
				}

				if (TargetBrother != nullptr)
				{
					if (TargetBrother->values.size() > ceil(root->M / 2.f) - 1)
					{	//���ֵܽ���ֵ������������

						T BrotherValue;
						T ParentValue;
						if (bIsLeftBrother)
						{//��������ֵܵ�ֵ

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
						{//��������ֵܵ�ֵ

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
					{//���ֵܽ���ֵ���������ޣ��Ӹ��ڵ��һ��Ԫ�����������ֵܽ��ϲ�

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
						//�Ӹ��ڵ�ĺ��ӽ���������Ƴ��Լ�
						remove(node->parent->childs.begin(), node->parent->childs.end(), node);
						node->parent->childs.erase(node->parent->childs.end() - 1);

						Remove(ParentValue, node->parent);
						//�ͷ��ڴ�
						delete node; node = nullptr;
					}
				}
			}
		}
		//2��ɾ���Ĳ���Ҷ�ӽ���Ԫ��
		else
		{
			remove(node->values.begin(), node->values.end(), value);
			node->values.erase(node->values.end() - 1);
			//�Ӻ�̽������һ��Ԫ�ش���
			T childvalue;
			BTreeNode<T>* child = nullptr;
			for (int i = 0; i < node->childs.size(); i++)
			{
				if (value < *(node->childs[i]->values.begin()))
				{

					child = node->childs[i];
					childvalue = *(child->values.begin());
					//�к��Ԫ�ص�����²Ż���룬û�о�ֱ��ɾ��û�в���
					InsertToNode(childvalue, node);
					Remove(childvalue, child);
					break;
				}
			}
		}
	}
	void Adjust(BTreeNode<T>*node)
	{
		//�ж��Ƿ����
		if (node->values.size() > node->M-1)
		{
			int mid = node->values.size() / 2;
			BTreeNode<T>* leftnode = new BTreeNode<T>();
			BTreeNode<T>* rightnode = new BTreeNode<T>();
			//��Ҫ�����Ԫ�ص���������ָ��
			for (int i = 0; i < node->values.size(); i++)
			{
				//�ָ�ֵ
				if (i < mid)leftnode->values.push_back(node->values[i]);
				if(i>mid)rightnode->values.push_back(node->values[i]);
			}
			for (int i = 0; i < node->childs.size(); i++)
			{
				//�ָ�������ĺ��ӽ��
				if (*(node->childs[i]->values.end() - 1) <= node->values[mid])
				{
					//���ӽ��ӵ�е�ֵ�е����ֵС�ڵ����м�ֵ�Ļ��ֵ����
					leftnode->childs.push_back(node->childs[i]);
					node->childs[i]->parent = leftnode;
				}
				else
				{
					//���ӽ����ӵ�е�ֵ�е���Сֵ�����м�ֵ�Ļ��ֵ��Ҳ�
					rightnode->childs.push_back(node->childs[i]);
					node->childs[i]->parent = rightnode;
				}
			}
			if (node->parent == nullptr)
			{
				//û�и��ڵ�������ֱ��newһ����������
				BTreeNode<T>* rootnode = new BTreeNode<T>(node->values[mid]);
				rootnode->childs.push_back(leftnode);
				rootnode->childs.push_back(rightnode);
				leftnode->parent = rootnode;
				rightnode->parent = rootnode;
				node->parent = rootnode;
				if (node == this->root)this->root = rootnode;//����������ĸ����ʱ���¸ı������ָ��
			}
			else
			{
				//�и��ڵ�
				int indexInparent = 0;
				vector<BTreeNode<T>*>& parentchailds = node->parent->childs;
				for (;indexInparent < parentchailds.size(); indexInparent++)
				{
					if (parentchailds[indexInparent] == node)break;
				}
				//�����ڵ�����Һ���������Ϊ���޽������ҷָ
				vector<BTreeNode<T>*>childsLeft;
				vector<BTreeNode<T>*>childsRight;
				for (int i=0; i < parentchailds.size(); i++)
				{
					if (i < indexInparent)childsLeft.push_back(parentchailds[i]);
					if (i > indexInparent)childsRight.push_back(parentchailds[i]);
				}
				//������ٰ�������룬�Ա���������µĺ��ӽ�㲻����Һ��ӽ�������
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
				//��ֵ�����������
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