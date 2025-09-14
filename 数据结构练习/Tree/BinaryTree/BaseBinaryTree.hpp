#pragma once
#include"iostream"
#include"queue"
#include"structs.hpp"
#include"string"
using namespace std;
template<class T>
class BaseBinaryTree
{
protected:
	//AVL����ת����ܻ�ı���ڵ㣬����������Ҫһ�������ָ����ָ����ڵ�
	TreeNode<T>* root_parent;//����ָ����ڵ㲻�洢ֵ
	int size;
public:
	BaseBinaryTree() :size(0){ root_parent = new TreeNode<T>();  }
	virtual ~BaseBinaryTree()
	{
		Destory();
	}
	void Init(TreeNode<T>* root)
	{
		Destory(this->root_parent->left);
		this->root_parent->left = root;
	}
	virtual void Insert(const T& Value)
	{
		if (this->root_parent->left == nullptr)
		{
			this->root_parent->left = new TreeNode<T>(Value);
			this->root_parent->left->parent = this->root_parent;
			this->root_parent->left->bColor = false;
			return;
		}
		Insert(Value, this->root_parent->left);
		this->size++;
	}
	void PrePrint()
	{
		cout << "ǰ�������";
		if (this->root_parent->left == nullptr)
		{
			cout << "BBT:����" << endl;
			return;
		}
		PrePrint(this->root_parent->left);
		cout << endl;
	}
	void InPrint()
	{
		cout << "���������";
		if (this->root_parent->left == nullptr)
		{
			cout << "BBT:����" << endl;
			return;
		}
		InPrint(this->root_parent->left);
		cout << endl;
	}
	void PostPrint()
	{
		cout << "���������";
		if (this->root_parent->left == nullptr)
		{
			cout << "BBT:����" << endl;
			return;
		}
		PostPrint(this->root_parent->left);
		cout << endl;
	}
	virtual void LevelPrint()
	{
		cout << "���������";
		if (this->root_parent->left == nullptr)
		{
			cout << "BBT:����" << endl;
			return;
		}
		queue<TreeNode<T>*>temp;
		temp.push(this->root_parent->left);
		while (!temp.empty())
		{
			TreeNode<T>* node = temp.front();
			temp.pop();
			cout << node->value << " ";
			if (node->left)temp.push(node->left);
			if (node->right)temp.push(node->right);
		}
		cout << endl;
	}
	int TreeDepth()
	{

		if (this->root_parent->left == nullptr) return 0;
		int dep = TreeDepth(this->root_parent->left);
		cout << "������ȣ�" << dep << endl;
		return dep;
	}
	int NodeHeight(TreeNode<T>* node)
	{
		if (node == nullptr)return 0;
		return TreeDepth(node);
	}
	void Destory()
	{
		Destory(this->root_parent->left);
		delete this->root_parent;
		this->root_parent = nullptr;
		cout << "Destory" << endl;
	}
	void PrintSerializedStr()
	{
		cout <<"���л����ַ�����" << Serialize() << endl;
	}
	string Serialize()
	{
		string str;
		str += '{';
		queue<TreeNode<T>*>temp;
		temp.push(this->root_parent->left);
		while (!temp.empty())
		{
			TreeNode<T>* node = temp.front();
			temp.pop();
			if (node != nullptr)
			{
				temp.push(node->left);
				temp.push(node->right);
				str += to_string(node->value)+',';
			}
			else
			{
				str += '#';
			}
		}
		str += '}';
		return str;
	}
	TreeNode<T>* Deserialize(const string&str) {
		if (str.length() == 0) {
			return nullptr;
		}
		string s=str.substr(1,str.length()-2);//�Ѵ����Ÿ�ȥ��
		if (str[0] == '#') {
			return nullptr;
		}
		// ����ͷ���
		queue<TreeNode<T>*> nodes;
		//atoi ��C��׼���е�һ��������ȫ��Ϊ "ASCII to Integer"
		//atoi �����������޷�ת�����ַ�ʱ����ֹͣת����������ת���Ĳ���
		TreeNode<T>* ret = new TreeNode<T>(atoi(s.c_str()));
		s = s.substr(s.find_first_of(',') + 1);
		nodes.push(ret);
		// �������л��ַ����ٲ�α���һ�飬��������
		while (!nodes.empty() && !s.empty())
		{
			TreeNode<T>* node = nodes.front();
			nodes.pop();
			if (s[0] == '#')
			{
				node->left = nullptr;
				s = s.substr(1);
			}
			else
			{
				node->left = new TreeNode<T>(atoi(s.c_str()));
				nodes.push(node->left);
				s = s.substr(s.find_first_of(',') + 1);
			}
			if (s[0] == '#')
			{
				node->right = nullptr;
				s = s.substr(1);
			}
			else
			{
				node->right = new TreeNode<T>(atoi(s.c_str()));
				nodes.push(node->right);
				s = s.substr(s.find_first_of(',') + 1);
			}
		}
		return ret;
	}
protected:
	virtual void Insert(const T& Value, TreeNode<T>*& Node)//ӦΪҪ�޸�ָ������Ҫ��������
	{
		if (Node == nullptr)
		{
			Node = new TreeNode<T>(Value);
			size++;
			//cout << Value << " ";
			return;
		}
		if (Value <= Node->value)Insert(Value, Node->left);
		else Insert(Value, Node->right);
	}
	void PrePrint(TreeNode<T>* root)
	{
		//ǰ�������������
		if (root != nullptr)
		{
			cout << root->value << " ";
			InPrint(root->left);
			InPrint(root->right);
		}
		return;
	}
	void InPrint(TreeNode<T>* root)
	{
		//��������������
		if (root != nullptr)
		{
			InPrint(root->left);
			cout << root->value << " ";
			InPrint(root->right);
		}
		return;
	}
	void PostPrint(TreeNode<T>* root)
	{
		//������������Ҹ�
		if (root != nullptr)
		{
			PostPrint(root->left);
			PostPrint(root->right);
			cout << root->value << " ";
		}
		return;
	}
	int TreeDepth(TreeNode<T>* Node)
	{
		if (Node != nullptr)
		{
			int l = TreeDepth(Node->left);
			int r = TreeDepth(Node->right);
			int re = l >= r ? ++l : ++r;
			/*cout << "l:" << l << endl;
			cout << "r:" << r << endl;*/
			return re;
		}
		return 0;
	}
	void Destory(TreeNode<T>* node)
	{
		if (node != nullptr)
		{
			Destory(node->left);
			Destory(node->right);
			//if (node == this->root)return;
			delete node;
		}
	}
	void Init(const T arr[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			this->Insert(arr[i]);
		}
	}
};