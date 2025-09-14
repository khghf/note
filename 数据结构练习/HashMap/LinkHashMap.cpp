#pragma once
#include<iostream>
#include<vector>
struct HashNode
{
	int data;
	HashNode* next;
	HashNode* prev;
	HashNode(int d) :data(d), next(nullptr),prev(nullptr) {};
};
class HashMap
{
private:
	const static int MAXSIZE = 15;
	int maxPrime;
	std::vector<HashNode*>HashArray;
public:
	HashMap()
	{
		this->HashArray.resize(this->MAXSIZE, nullptr);
		for (int i = MAXSIZE - 1; i > 1; i--)
		{
			if (MAXSIZE % i == 0) {
				maxPrime = i;
				break;
			}
			else maxPrime = MAXSIZE;
		}
	}
	int HashFunction(int value)
	{
		return value % this->maxPrime;
	}
	bool IsEmpty()
	{
		int index = 0;
		while (this->HashArray[index] == nullptr)
		{
			index = ++index % this->MAXSIZE;
			if (index == 0)return true;
		}
		return false;
	}
	void Add(int value)
	{
		int index = this->HashFunction(value);
		if (this->HashArray[index] == nullptr)
		{
			this->HashArray[index] = new HashNode(value);
		}
		else
		{
			HashNode* temp = this->HashArray[index];
			while (temp->next != nullptr)
			{
				if (temp->data == value)return;
				temp = temp->next;
			}
			temp->next = new HashNode(value);
			temp->next->prev = temp;
		}
	}
	void Delete(int value)
	{
		if (this->IsEmpty())return;
		int index = this->HashFunction(value);
		HashNode* temp = this->HashArray[index];
		while (temp != nullptr)
		{
			if (temp->data == value)
			{
				if (temp->prev == nullptr)
				{
					this->HashArray[index] = nullptr;
					delete temp;
				}
				else
				{
					temp->prev->next = temp->next;
					delete temp;
				}
				return;
			}
			temp = temp->next;
		}
		std::cout << "无元素"<<value<<"，不需删除" << std::endl;
	}
	void Search(int value)
	{
		if (this->IsEmpty())return;
		int index = this->HashFunction(value);
		HashNode* temp = this->HashArray[index];
		while (temp != nullptr)
		{
			if (temp->data == value)
			{
				std::cout <<value<<"对应下标为:" <<index<< std::endl;
				return;
			}
			temp = temp->next;
		}
		std::cout << "未查到元素" << value<< std::endl;
	}
	void Print()
	{
		if (IsEmpty())return;
		int index = 0;
		HashNode* temp = nullptr;
		do
		{
			temp = this->HashArray[index];
			std::cout << index << ":";
			while (temp!= nullptr)
			{
				std::cout << temp->data << " ";
				temp = temp->next;
			}
			std::cout << std::endl;
			index = ++index % this->MAXSIZE;
		} while (index != 0);
		std::cout << std::endl;
	}
};
