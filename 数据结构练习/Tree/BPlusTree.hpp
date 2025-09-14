//�������
//һ���ҵ�Ŀ����,�ڲ��ҹ������������ļ�������ҹ����о����Ľ������������ֵ��
//    ����Ҫ���¸ýڵ�����������ֵ
//������������жϽ���Ƿ����
//  1�����
//      ��һ�����Ƿ�ΪҶ�ӽ�㣬������ָ���ļ��������µĽ�㣬������Ҫ�ָ�ӽ��
//      �ڶ����������ҽ�����������
//      ���������жϵ�ǰ����Ƿ�Ϊ�����
//          �Ǹ��ڵ㣺
//                  (1)�¼�һ������㣬�ڸ��ڵ���������ҽ����������������������ӵ���������
//                  (2)�����������ĸ��ڵ�ָ��
//          ���Ǹ���㣺
//                  (1)��������������ֵܽ��洢����
//                  (2)��ո��ڵ�ĺ��ӽ������
//                  (3)����������ֵܽ�㡢�ָ�����ҽ�㡢���ֵܽ��
//                  (4)�����������ĸ��ڵ�ָ��
//  2��δ���ֱ�ӷ���
//ɾ������
//һ���ҵ�Ҫɾ�������ڵĽ��
//����ɾ�����Ƿ���������(����(ceil(M / 2.f)))
//  ���㣺
//      ֱ��ɾ����Ȼ����¸��ڵ��е�����(��Ҫ�ݹ����һֱ���µ������)
//  �����㣺
//      1����ȡ�ýڵ��Ŀ���ֵ�(�� / ���ֵܽ��)
//      2��Ŀ���ֵܽ�㲻Ϊ��
//          ɾ����ǰ����е�Ŀ��ֵ�����¸��ڵ��е�����
//          * �ֵܽ����������������
//              1���洢�ֵܽ�������ļ�
//              2���ֵܽ��ɾ�����ȥ�ļ�
//              3������ǰ�������ֵܽ�����ļ�
//              4�����¸����Ժ��ӽ�������(���ӽ����ӵ�е�����ֵ)
//          * �ֵܽ����������������
//              1�����ֵܽ��ϲ�(���ϲ������ӽ��ϲ�)
//                  ���ֵܣ���ȡ���ڵ㶪ʧ�ļ�ֵ����(���ֵܽ�������ֵ)
//                      ���ֵ�->next = ��ǰ���->next
//                  ���ֵܣ���ȡ���ڵ㶪ʧ�ļ�ֵ����(��ǰ��������ֵ)
//                      ��ǰ���->next = ���ֵ�->next
//              2���Ƴ����ڵ�����ϲ�����ʧ�ĺ��ӽ��
//              3���ͷŽ��ռ�(��ǰ��� / �ֵܽ��)
//              4���ı�ϲ������ĺ��ӽ��ĸ����ָ��
//              5���ݹ����ɾ��������ɾ�����ڵ�����ϲ�����ʧ�ļ�ֵ����
//              ע�⣺��Ϊ����Ҫ�ݹ����ɾ��������ɾ�����ڵ��е�ָ����ֵ����������û�е��ø��и��ڵ������ĺ���
//      3���ֵܽ��Ϊ��(�ýڵ�Ϊ���ڵ�)
//          * ֻ��һ�����ӽ��
//              �ø��ڵ�ָ���ӽ�㣬Ȼ���ͷ�֮ǰ�ĸ��ڵ�Ŀռ�
//          * �� >= 2�����ӽ��
//              ֱ���Ƴ�������
#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
template<class T>
struct BPlusNode
{
    vector<T> keys;          // �洢��
    vector<BPlusNode<T>*> childs; // ָ���ӽڵ��ָ������
    BPlusNode<T>* next;            // ָ����һ��Ҷ�ӽڵ��ָ�루����˳����ʣ�
    BPlusNode<T>* parent;
    const int M = 3;
    BPlusNode():next(nullptr),parent(nullptr) {
        keys.reserve(M+1);
        childs.reserve(M+1);
    }
    BPlusNode(const T&key) :next(nullptr), parent(nullptr) {
        keys.reserve(M+1);
        keys.push_back(key);
        childs.reserve(M+1);
    }
};
template<class T>
class BPlusTree
{
protected:
    BPlusNode<T>* root;
    BPlusNode<T>* head;
public:
    BPlusTree() :root(nullptr) {}
    BPlusTree(const T arr[], int size) :root(nullptr) {
        for (int i = 0; i < size; i++)
        {
            Insert(arr[i]);
        }
    }
    ~BPlusTree()
    {
        Destory();
    }
    void Insert(const T& key)
    {
        if (root == nullptr)
        {
            root = new BPlusNode<T>(key);
            head = root;
            return;
        }
        Insert(key, root);
    }
    void LevelPrint()
    {
       
        queue<BPlusNode<T>*>temp;
        temp.push(root);
        while (!temp.empty())
        {
            BPlusNode<T>* next = temp.front();
            temp.pop();
            cout << "|";
            for (auto in: next->keys)
            {
                cout << in << " ";
            }
            for (auto in : next->childs)
            {
                temp.push(in);
            }
        }
        cout << "|" << endl;;
    }
    void Remove(const T& key)
    {
        Remove(key, SerchNode(key));
    }
    void PrintLinkList()
    {
        BPlusNode<T>* node = this->head;
        while (node != nullptr)
        {
            for (auto in : node->keys)
            {
                cout << in << " ";
            }
            node = node->next;
        }
        cout << endl;
   }
    void Destory()
    {
        if (root == nullptr)return;
        queue<BPlusNode<T>*>q;
        q.push(root);
        while (!q.empty())
        {
            BPlusNode<T>* node = q.front();
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
    void Insert(const T& key, BPlusNode<T>* &node)
    {
        if (node == nullptr)return;
        //��Ҷ�ӽ��
        if (node->childs.size() <= 0)
        {
            node->keys.push_back(key);
            sort(node->keys.begin(), node->keys.end());
            Adjust(node);
        }
        //����Ҷ�ӽ��
        else
        {
            if (key < *(node->keys.begin()))
            {
                //С�ڽ����Сֵ���������
                Insert(key, *(node->childs.begin()));
            }
            else if (key > *(node->keys.end() - 1))
            {
                //���ڽ�����ֵ�����ұ���
                *(node->keys.end() - 1) = key;
                Insert(key, *(node->childs.end() - 1));
            }
            else
            {
                for (int i = 0; i < node->keys.size(); i++)
                {
                    if (key < node->keys[i])
                    {
                        //*(node->keys.end() - 1) = key;
                        Insert(key, node->childs[i]);
                        break;
                    }
                }
            }
        }
    }
    void Adjust(BPlusNode<T>*& node)
    {
        //�ؼ��ָ�����������
        if (node->keys.size() > this->root->M)
        {
            int mid = this->root->M / 2;
            //1����M/2Ϊ�м�ֵ�����ָ������������
            BPlusNode<T>* leftnode = new BPlusNode<T>();
            BPlusNode<T>* rightnode = new BPlusNode<T>();
            //�ýڵ�ΪҶ�ӽ�㣬ֻ��Ҫ�ָ��ֵ
            if (node->childs.size() <= 0)
            {
                for (int i = 0; i < node->keys.size(); i++)
                {
                    if (i <= mid)
                    {
                        leftnode->keys.push_back(node->keys[i]);
                    }
                    else
                    {
                        rightnode->keys.push_back(node->keys[i]);
                    }
                }
            }
            //�ýڵ㲻��Ҷ�ӽڵ�,�ָ���ļ��ͺ��ӽ��
            else
            {
                for (int i = 0; i < node->keys.size(); i++)
                {
                    if (i <= mid)
                    {
                        leftnode->keys.push_back(node->keys[i]);
                        leftnode->childs.push_back(node->childs[i]);
                        node->childs[i]->parent = node;
                    }
                    else
                    {
                        rightnode->keys.push_back(node->keys[i]);
                        rightnode->childs.push_back(node->childs[i]);
                        node->childs[i]->parent = rightnode;
                    }
                }
                
            }

            node->childs.swap(leftnode->childs);
            node->keys.swap(leftnode->keys);
            delete leftnode; leftnode = nullptr;
            //�����ӽ�㴮������
            rightnode->next = node->next;
            node->next = rightnode;
            //�ý���Ǹ����
            if (node == this->root)
            {
                //�������ڵ㣬���¸��ڵ��ڶԺ��ӽ�������
                BPlusNode<T>* root = new BPlusNode<T>();
                root->keys.push_back(*(node->keys.end() - 1));
                root->keys.push_back(*(rightnode->keys.end() - 1));
                //���¸��ڵ�ĺ�������
                root->childs.push_back(node);
                root->childs.push_back(rightnode);
                //���º��ӽ��ĸ����ָ��
                node->parent = root;
                rightnode->parent = root;
               
                this->root = root;
            }
            else
            {//����Ҷ�ӽ��
                //�������ֵܴ洢����
                BPlusNode<T>* parentnode = node->parent;
                vector<BPlusNode<T>*>leftbrother;
                vector<BPlusNode<T>*>rightbrother;
                bool bLeft = true;
                for (auto in : parentnode->childs)
                {
                    if (bLeft)
                    {
                        if (in != node)leftbrother.push_back(in);
                        else bLeft = false;
                    }
                    else
                    {
                        if(in!=node)rightbrother.push_back(in);
                    }
                }
                //����ո��ڵ�ĺ��ӽ���ٰ������������
                parentnode->childs.clear();
                for (auto in : leftbrother)parentnode->childs.push_back(in);
                parentnode->childs.push_back(node);
                parentnode->childs.push_back(rightnode);

                rightnode->parent = parentnode;
                for (auto in : rightbrother)parentnode->childs.push_back(in);
                parentnode->keys.push_back(*(node->keys.end() - 1));
               
                if (!(binary_search(parentnode->keys.begin(), parentnode->keys.end(), *(rightnode->keys.end() - 1))))
                {
                    parentnode->keys.push_back(*(rightnode->keys.end() - 1));
                }
                sort(parentnode->keys.begin(), parentnode->keys.end());
                Adjust(parentnode);
            }
        }
    }
    BPlusNode<T>* SerchNode(const T& key)
    {
        BPlusNode<T>* node = this->root;
        while (node != nullptr)
        {
            if (node->childs.size() <= 0)
            {
                if (binary_search(node->keys.begin(), node->keys.end(), key))
                {
                    return node;
                }
                cout << "key:" << key << "not found" << endl;
                return nullptr;
            }
            if (key < *(node->keys.begin()))
            {
                node = *(node->childs.begin());
            }
            else if (key > *(node->keys.end() - 1))
            {
                node = *(node->childs.end()-1);
            }
            else
            {
                for (int i = 0; i < node->keys.size(); i++)
                {
                    if (key <= node->keys[i])
                    {
                        node = node->childs[i];
                        break;
                    }
                }
            }
        }
        cout << "key:" << key << "not found" << endl;
        return nullptr;
    }
    void Remove(const T& key, BPlusNode<T>* node)
    {
        if (node != nullptr)
        {
            BPlusNode<T>* parentnode = node->parent;
            //ɾ��������������
            if (node->keys.size() > ceil(this->root->M / 2.f))
            {
                remove(node->keys.begin(), node->keys.end(), key);
                node->keys.erase(node->keys.end() - 1);
                //���¸��ڵ�Ժ��ӽ�������
                UpdateIndex(parentnode);
                return;
            }
            //ɾ������������
            else
            {
                //���һ�������ֵܽ�
                //��Ŀ���ֵ�
                BPlusNode<T>* LeftBrother = nullptr;
                BPlusNode<T>* RightBrother = nullptr;
                BPlusNode<T>* TargetBrother = nullptr;

                if (parentnode != nullptr)
                {
                    int brothercount = parentnode->childs.size();
                    for (int i = 0; i < brothercount; i++)
                    {
                        if (node->parent->childs[i] == node)
                        {
                            LeftBrother = node->parent->childs[max(0, i - 1)];
                            RightBrother = node->parent->childs[min(brothercount - 1, i + 1)];
                        }
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
                    T parentRemoveKey = *(node->keys.end() - 1);
                    remove(node->keys.begin(), node->keys.end(), key);
                    node->keys.erase(node->keys.end() - 1);
                    //���¸��ڵ�Ժ��ӽ�������
                    UpdateIndex(parentnode);
                    T BrotherKey;
                    BPlusNode<T>* Brotherchild = nullptr;
                    //�ֵܽ�ֵ������������
                    if (TargetBrother->keys.size() > ceil(this->root->M / 2.f))
                    {
                        if (bIsLeftBrother)
                        {//���ֵ�
                            BrotherKey = *(TargetBrother->keys.end() - 1);
                            TargetBrother->keys.erase(TargetBrother->keys.end() - 1);
                            node->keys.insert(node->keys.begin(), BrotherKey);
                            if (TargetBrother->childs.size() > 0)
                            {
                                Brotherchild = *(TargetBrother->childs.end() - 1);
                                TargetBrother->childs.erase(TargetBrother->childs.end() - 1);
                                node->childs.insert(node->childs.begin(), Brotherchild);
                                Brotherchild->parent = node;
                            }
                        }
                        else
                        {//���ֵ�
                            BrotherKey = *(TargetBrother->keys.begin());
                            TargetBrother->keys.erase(TargetBrother->keys.begin());
                            node->keys.insert(node->keys.end(), BrotherKey);
                            if (TargetBrother->childs.size() > 0)
                            {
                                Brotherchild = *(TargetBrother->childs.begin());
                                TargetBrother->childs.erase(TargetBrother->childs.begin());
                                node->childs.insert(node->childs.end(), Brotherchild);
                                Brotherchild->parent = node;
                            }

                        }
                        //���¸��ڵ�Ժ��ӽ�������
                        UpdateIndex(parentnode);
                    }
                    //�ֵܽ�ֵ����������
                    else
                    {
                        
                        if (bIsLeftBrother)
                        {//���ֵ�
                            //ɾ���������ֵܺϲ�
                            parentRemoveKey = *(TargetBrother->keys.end() - 1);
                            for (auto in : node->keys)
                            {
                                TargetBrother->keys.push_back(in);
                            }
                            for (auto in : node->childs)
                            {
                                TargetBrother->childs.push_back(in);
                                in->parent = TargetBrother;

                            }
                            TargetBrother->next = node->next;
                            remove(node->parent->childs.begin(), node->parent->childs.end(), node);
                            node->parent->childs.erase(node->parent->childs.end() - 1);
                            delete node; node = nullptr;

                        }
                        else
                        {//���ֵ�
                            //���ֵܺ�ɾ�����ϲ�
                            for (auto in : TargetBrother->keys)
                            {
                                node->keys.push_back(in);
                            }
                            for (auto in : TargetBrother->childs)
                            {
                                node->childs.push_back(in);
                                in->parent = node;
                            }
                            node->next = TargetBrother->next;
                            remove(node->parent->childs.begin(), node->parent->childs.end(), TargetBrother);
                            node->parent->childs.erase(node->parent->childs.end() - 1);
                            delete TargetBrother; TargetBrother = nullptr;
                        }
                       
                        //ֻҪ�����˺ϲ���ô���ڵ����Ҫɾ��һ������
                        Remove(parentRemoveKey, parentnode);
                       

                    }
                }
                //û���ֵܽ��˵���Ǹ��ڵ�
                else
                {

                    if (node->childs.size() <= 1)
                    {
                        //��ʱ����ڵ���Ҫ�ı�ָ��
                        BPlusNode<T>* temp = this->root;
                        this->root = this->root->childs[0];
                        this->root->childs[0]->parent = nullptr;
                        delete temp; temp = nullptr;
                    }
                    else if (node->childs.size() >= 2)
                    {
                        remove(node->keys.begin(), node->keys.end(), key);
                        node->keys.erase(node->keys.end() - 1);
                    }
                }
            }
        }
    }
    void UpdateIndex(BPlusNode<T>* node)
    {
        if (node == nullptr)return;
        //���¸��ڵ�Ժ��ӽ�������
        node->keys.clear();
        for (auto in : node->childs)
        {
            node->keys.push_back(*(in->keys.end() - 1));
            //cout << *(in->keys.end() - 1) << endl;
        }
        UpdateIndex(node->parent);

    }
};