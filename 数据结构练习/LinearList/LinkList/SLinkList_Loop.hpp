#include"SLinkList.hpp"
template<class T>
class SLinkList_Loop :public SLinkList<T>
{
public:
	SLinkList_Loop()
	{
		this->head = new SNode<T>();
		this->length = 0;
	}
	SLinkList_Loop(const T arr[], int size, bool TailInsert = true)
	{
		//int size = ;
		this->head = new SNode<T>();
		this->length = 0;
		SNode<T>* temp = this->head;
		if (TailInsert)
		{
			//尾插法
			for (int i = 0; i < size; i++)
			{
				temp->next = new SNode<T>();
				this->length++;
				temp->next->data = arr[i];
				temp = temp->next;
				if (i == size - 1)temp->next = this->head;
			}
		}
		else
		{
			//头插法
			for (int i = 0; i < size; i++)
			{
				temp = new SNode<T>();
				this->length++;
				temp->data = arr[i];
				temp->next = this->head->next;
				this->head->next = temp;
				if (i == 0)temp->next = this->head;
			}
		}
	}
	~SLinkList_Loop()
	{
		SNode<T>* temp = nullptr;
		int DeleteCount = 0;
		if (!this->head->next) { return; }
		while (this->head->next != this->head)
		{
			temp = this->head->next;
			this->head->next = temp->next;
			delete temp;
			DeleteCount++;
		}
		this->head->next = nullptr;//这里只是解开循环而没有完全删除是因为基类也会调用析构函数会对同一内存删除两次
		cout << "~SLinkList_Loop():DeleteCount:" << DeleteCount << endl;
		cout << "---------------------------" << endl;
	}
	void ShowList()//输出点链表所有结点的值
	{
		cout << "SLinkList_Loop:" << endl;
		if (!this->head->next) { cout << "SLinkList_Loop:空表" << endl; return; }
		SNode<T>* temp = this->head->next;
		int LoopCount = 0;
		while (temp->next != this->head)
		{
			cout << temp->data << " ";
			temp = temp->next;
			LoopCount++;
		}
		cout << temp->data << " ";
		cout << "length:" << this->length<<" ";
		cout << "LoopCount:" << LoopCount << endl;
	}
};