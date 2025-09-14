#pragma once
#include"iostream"
using namespace std;
class SequenceString
{
	static const int MAXSIZE = 100;
	int length;
	char* data;
public:
	SequenceString() :length(0) { data = nullptr; }
	SequenceString(const char arr[]) :length(0)
	{
		const char* str = arr;
		if (str) {
			length = std::strlen(str);
			data = new char[length + 1];
			for (int i = 0; i < length; i++)
			{
				data[i] = *str;
				str++;
			}
			data[length] = '\0';
		}
		else {
			data = nullptr;
			length = 0;
		}
	}
	SequenceString(char* str) :length(0) {
		if (str) {
			length = std::strlen(str);
			data = new char[length + 1];
			for (int i = 0; i < length;i++)
			{
				data[i] = *str;
				str++;
			}
		}
		else {
			data = nullptr;
			length = 0;
		}
	}

	~SequenceString() {
		delete[]data;
	}
	void Print()
	{
		int i = 0;
		while (data[i] != '\0')
		{
			cout << data[i];
			i++;
		}
		cout << endl;
	}
	int Index(const char* substr)
	{
		if (substr == nullptr)return 0;
		int sublen = strlen(substr);
		int times = 0;
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < sublen; j++)
			{
				times++;
				if (data[i] != substr[j])
				{
					i = i - j;
					break;
				}
				else if (j == sublen - 1)
				{
					i = i - j;
					cout << "times:" << times << endl;
					return i + 1;
				}
				else i++;
			}
		}
		cout << "times:" << times << endl;
		return -1;
	}
	int KMPMatch(const char* substr)
	{
		int n = strlen(substr);
		vector<int>next = BuildNext(substr);
		int times = 0;
		int i = 0, j = 0;
		while (i<length)
		{
			times++;
			if (data[i] == substr[j])
			{
				if (j >= n - 1)
				{
					cout << "times:" << times << endl;
					return i - j + 1;
				}
				j++; i++;
			}
			else
			{
				if (j == 0)i++;
				j = next[max(0,j-1)];
			}
		}
		cout << "times:" << times << endl;
		return -1;
	}
	vector<int>BuildNext(const char* str)
	{
		//1��left��ʼΪ0��rightΪ1(0��ʱ���һ��Ԫ��û��ǰ��׺)
		//2��str[left]==str[right]����ʱ����󹫹�ǰ��׺����Ϊ++left(left���±��0��ʼ)
		//3���������������ݵ�ret[left-1](���left-1��right-1��ƥ����Ͳ���Ҫleft��0��ʼ�ٴ�ƥ����)
		//����ABACABAB,��ʱleft==3��right==7,ǰ����ƥ���leftֻ����ݵ�1
		int n = strlen(str);
		vector<int>ret(n,0);
		int left = 0; int right = 1;
		while (right < n)
		{
			if (str[left] == str[right])ret[right++] = ++left;//ƥ������ָ������
			else
			{
				if (left <= 0)right++;//��ƥ������ʱleft==0ֻ��Ҫ����right
				left = ret[max(0, left-1)];//��ƥ���ʱleft!=0�����
			}
		}
		return ret;
	}
};