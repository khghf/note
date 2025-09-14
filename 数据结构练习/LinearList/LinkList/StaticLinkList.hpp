//��̬����ʹ������ķ�ʽʵ������Ĺ��ܣ�������������ʵ�ֵĸı���
//������Ҫ�漰�������������ܴ�ʱ�����ĺܶ��ϵͳ��Դ
//ͷ�ڵ㲻�����ݣ�һ��ֻ�в�֧��ָ������ԲŻ�ʹ�þ�̬����������ָ������
#pragma once
using namespace std;
template<typename T>
struct StaticNode
{
	T data;
	int next;
	StaticNode(int Next=-2):next(Next){}//-1��ʾΪβ�ڵ㣬-2��ʾ�ýڵ����
};
#define InitSize_StaticLinkList 10
template<class T>
class StaticLinkList
{
public:
	StaticNode<T>Data[InitSize_StaticLinkList];
	int length;
	StaticLinkList():length(0){}
	StaticLinkList(const T arr[], const int& size)
	{
		for (int i = 0; i < InitSize_StaticLinkList; i++)
		{
			this->Data[i].data = 0;//��ʼ������Ϊ��
			this->Data[i].next = -2;
		}
		length = 0;
		if (size == 0)return;
		this->Data[0].next = 1;//ͷ�ڵ㲻������
		if (size > InitSize_StaticLinkList - 1)
		{
			cout << "�ɴ洢���ݿռ�Ϊ��" << InitSize_StaticLinkList - 1 << endl;
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				this->Data[i + 1].data = arr[i];
				this->Data[i + 1].next = i+2;
				length++;

			}
			this->Data[size].next =-1;//���һ��Ԫ�ر�ʶΪβ��
		}
	}
	~StaticLinkList()
	{
		
	}
	void ShowList()
	{
		cout << "StaticLinkList:\n";
		if (length <= 0) { cout << "�ձ�" << endl; return; }
		int index = 0;
		while (Data[index].next != -1)
		{  
			index = Data[index].next;
			cout << "index:" << index << " ";
			cout << "data:" << Data[index].data << " ";
			cout << "next:" << Data[index].next << endl;
		}
		cout << Data[index+1].data << " ";
		cout << endl;
	}
	void ShowAllNode()
	{
		int i = 0;
		while (i<InitSize_StaticLinkList)
		{
			
			cout << "index:" << i << " ";
			cout << "data:" << Data[i].data << " ";
			cout << "next:" << Data[i].next << endl;
			i++;
		}
	}
	void Insert(const int& Location, const T& Value)
	{
		if (length >= InitSize_StaticLinkList-1) { cout << "�������޷�����" << endl; return; }
		int index = 0;//����ֵΪҪ����λ�õ�ǰһ��λ��������ע��������ṹ
		for (int i = 0; i < Location-1; i++)
		{
			index = Data[index].next;
		}
		int EmptyIndex = FindEmptyIndex();
		if (EmptyIndex != -1)
		{
			Data[EmptyIndex].data = Value;
			Data[EmptyIndex].next = Data[index].next;
			Data[index].next = EmptyIndex;
		}
	}
	int FindEmptyIndex()
	{
		for (int i = 1; i < InitSize_StaticLinkList; i++)
		{
			if (this->Data[i].next == -2)return i;
		}
		return -1;
	}
};

