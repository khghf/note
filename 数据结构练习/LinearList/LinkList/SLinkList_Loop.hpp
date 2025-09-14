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
			//β�巨
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
			//ͷ�巨
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
		this->head->next = nullptr;//����ֻ�ǽ⿪ѭ����û����ȫɾ������Ϊ����Ҳ����������������ͬһ�ڴ�ɾ������
		cout << "~SLinkList_Loop():DeleteCount:" << DeleteCount << endl;
		cout << "---------------------------" << endl;
	}
	void ShowList()//������������н���ֵ
	{
		cout << "SLinkList_Loop:" << endl;
		if (!this->head->next) { cout << "SLinkList_Loop:�ձ�" << endl; return; }
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