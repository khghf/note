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
		//1、left初始为0，right为1(0的时候就一个元素没有前后缀)
		//2、str[left]==str[right]，此时的最大公共前后缀长度为++left(left是下标从0开始)
		//3、如果不满足则回溯到ret[left-1](如果left-1和right-1曾匹配过就不需要left从0开始再次匹配了)
		//例如ABACABAB,此时left==3，right==7,前面有匹配的left只需回溯到1
		int n = strlen(str);
		vector<int>ret(n,0);
		int left = 0; int right = 1;
		while (right < n)
		{
			if (str[left] == str[right])ret[right++] = ++left;//匹配两个指针右移
			else
			{
				if (left <= 0)right++;//不匹配若此时left==0只需要右移right
				left = ret[max(0, left-1)];//不匹配此时left!=0则回溯
			}
		}
		return ret;
	}
};