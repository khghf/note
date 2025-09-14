//插入操作
//一、找到目标结点,在查找过程中如果插入的键大与查找过程中经过的结点的最大索引键值，
//    则需要更新该节点的最大索引键值
//二、插入结点后判断结点是否溢出
//  1、溢出
//      第一步、是否为叶子结点，不是则分割结点的键成两个新的结点，是则还需要分割孩子结点
//      第二步、将左右结点插入链表中
//      第三步、判断当前结点是否为根结点
//          是根节点：
//                  (1)新键一个根结点，在根节点内添加左右结点的索引，将这两个结点添加到孩子数组
//                  (2)更新两个结点的父节点指向
//          不是根结点：
//                  (1)将溢出结点的左右兄弟结点存储起来
//                  (2)清空父节点的孩子结点数组
//                  (3)依次添加左兄弟结点、分割的左右结点、右兄弟结点
//                  (4)更新两个结点的父节点指向
//  2、未溢出直接返回
//删除操作
//一、找到要删除键所在的结点
//二、删除后是否满足下限(大于(ceil(M / 2.f)))
//  满足：
//      直接删除，然后更新父节点中的索引(需要递归调用一直更新到根结点)
//  不满足：
//      1、获取该节点的目标兄弟(左 / 右兄弟结点)
//      2、目标兄弟结点不为空
//          删除当前结点中的目标值并更新父节点中的索引
//          * 兄弟结点借出键后还满足下限
//              1、存储兄弟结点借出来的键
//              2、兄弟结点删除借出去的键
//              3、给当前结点添加兄弟结点借出的键
//              4、更新父结点对孩子结点的索引(孩子结点所拥有的最大键值)
//          * 兄弟结点借出键后不满足下限
//              1、与兄弟结点合并(键合并，孩子结点合并)
//                  左兄弟：获取父节点丢失的键值索引(左兄弟结点的最大键值)
//                      左兄弟->next = 当前结点->next
//                  右兄弟：获取父节点丢失的键值索引(当前结点的最大键值)
//                      当前结点->next = 右兄弟->next
//              2、移除父节点中因合并而消失的孩子结点
//              3、释放结点空间(当前结点 / 兄弟结点)
//              4、改变合并进来的孩子结点的父结点指向
//              5、递归调用删除函数，删除父节点内因合并而丢失的键值索引
//              注意：因为这里要递归调用删除函数来删除父节点中的指定键值，所以这里没有调用更行父节点索引的函数
//      3、兄弟结点为空(该节点为根节点)
//          * 只有一个孩子结点
//              让根节点指向孩子结点，然后释放之前的根节点的空间
//          * 有 >= 2个孩子结点
//              直接移除键就行
#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
template<class T>
struct BPlusNode
{
    vector<T> keys;          // 存储键
    vector<BPlusNode<T>*> childs; // 指向子节点的指针向量
    BPlusNode<T>* next;            // 指向下一个叶子节点的指针（用于顺序访问）
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
        //是叶子结点
        if (node->childs.size() <= 0)
        {
            node->keys.push_back(key);
            sort(node->keys.begin(), node->keys.end());
            Adjust(node);
        }
        //不是叶子结点
        else
        {
            if (key < *(node->keys.begin()))
            {
                //小于结点最小值，往左边走
                Insert(key, *(node->childs.begin()));
            }
            else if (key > *(node->keys.end() - 1))
            {
                //大于结点最大值，往右边走
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
        //关键字个数超出限制
        if (node->keys.size() > this->root->M)
        {
            int mid = this->root->M / 2;
            //1、以M/2为中间值将结点分割成左右两部分
            BPlusNode<T>* leftnode = new BPlusNode<T>();
            BPlusNode<T>* rightnode = new BPlusNode<T>();
            //该节点为叶子结点，只需要分割键值
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
            //该节点不是叶子节点,分割结点的键和孩子结点
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
            //将孩子结点串连起来
            rightnode->next = node->next;
            node->next = rightnode;
            //该结点是根结点
            if (node == this->root)
            {
                //创建根节点，更新根节点内对孩子结点的索引
                BPlusNode<T>* root = new BPlusNode<T>();
                root->keys.push_back(*(node->keys.end() - 1));
                root->keys.push_back(*(rightnode->keys.end() - 1));
                //更新根节点的孩子数组
                root->childs.push_back(node);
                root->childs.push_back(rightnode);
                //更新孩子结点的父结点指向
                node->parent = root;
                rightnode->parent = root;
               
                this->root = root;
            }
            else
            {//不是叶子结点
                //将左、右兄弟存储起来
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
                //先清空父节点的孩子结点再按次序依次添加
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
            //删除后仍满足下限
            if (node->keys.size() > ceil(this->root->M / 2.f))
            {
                remove(node->keys.begin(), node->keys.end(), key);
                node->keys.erase(node->keys.end() - 1);
                //更新父节点对孩子结点的索引
                UpdateIndex(parentnode);
                return;
            }
            //删除后不满足下限
            else
            {
                //情况一向左右兄弟借
                //找目标兄弟
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
                    T parentRemoveKey = *(node->keys.end() - 1);
                    remove(node->keys.begin(), node->keys.end(), key);
                    node->keys.erase(node->keys.end() - 1);
                    //更新父节点对孩子结点的索引
                    UpdateIndex(parentnode);
                    T BrotherKey;
                    BPlusNode<T>* Brotherchild = nullptr;
                    //兄弟借值后仍满足下限
                    if (TargetBrother->keys.size() > ceil(this->root->M / 2.f))
                    {
                        if (bIsLeftBrother)
                        {//左兄弟
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
                        {//右兄弟
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
                        //更新父节点对孩子结点的索引
                        UpdateIndex(parentnode);
                    }
                    //兄弟借值后不满足下限
                    else
                    {
                        
                        if (bIsLeftBrother)
                        {//左兄弟
                            //删除结点和左兄弟合并
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
                        {//右兄弟
                            //右兄弟和删除结点合并
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
                       
                        //只要发生了合并那么父节点就需要删除一个索引
                        Remove(parentRemoveKey, parentnode);
                       

                    }
                }
                //没有兄弟结点说明是根节点
                else
                {

                    if (node->childs.size() <= 1)
                    {
                        //这时候根节点需要改变指向
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
        //更新父节点对孩子结点的索引
        node->keys.clear();
        for (auto in : node->childs)
        {
            node->keys.push_back(*(in->keys.end() - 1));
            //cout << *(in->keys.end() - 1) << endl;
        }
        UpdateIndex(node->parent);

    }
};