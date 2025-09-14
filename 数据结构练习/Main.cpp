#include"iostream"
#include"vector"
#include"LinearList/SequenceList.hpp"//顺序表
#include"LinearList/LinkList/SLinkList.hpp"//单链表
#include"LinearList/LinkList/DLinkList.hpp"//双链表
#include"LinearList/LinkList/SLinkList_Loop.hpp"//循环单链表
#include"LinearList/LinkList/DLinkList_Loop.hpp"//循环双链表
#include"LinearList/LinkList/StaticLinkList.hpp"//静态链表
#include"LinearList/Stack/SquenceStack.hpp"//顺序栈(特殊顺序表,先进后出)
#include"LinearList/Stack/LinkStack.hpp"//链式栈(特殊单链表,先进后出)
#include"LinearList/Queue/SequenceQueue_Loop.hpp"//循环顺序队列(先进先出)
#include"LinearList/Queue/LinkQueue.hpp"//链式队列(先进先出)
#include"LinearList/Queue/DSequenceQueue_Loop.hpp"//双端循环顺序队列
#include"LinearList/String/SequenceString.hpp"//串(数组)
#include"LinearList/String/LinkSequenceString.hpp"
#include"Tree/BinaryTree/BaseBinaryTree.hpp"//二叉树基类
#include"Tree/BinaryTree/BinarySearchTree.hpp"//二叉搜索树
#include"Tree/BinaryTree/AVLTree.hpp"//平衡二叉搜索树
#include"Tree/BinaryTree/RedBlackTree.hpp"//红黑树
#include"Tree/BTree.hpp"//B树
#include"Tree/BPlusTree.hpp"//B+树
#include"Tree/Heap.hpp"//堆
#include"Tree/BinaryIndexTree.hpp"//树状数组
#include"Tree/BinaryTree/HuffmanTree.hpp"//哈夫曼树
#include"Tree/SegmentTree .hpp"//线段树
#include"Graph/AdjacencyMatrix.hpp"//邻接矩阵
#include"Graph/AdjacencyList.hpp"//邻接链表
#include"Graph/CrossLinkedList.hpp"//十字链表
#include"Graph/AdjacencyMultiList.hpp"//邻接多重表
#include"SortAlgorithm.hpp"
#include"Counter.hpp"
using namespace std;
using namespace sort_algorithm;
int main()
{
	
	int arr[] = { 1,2,3,4,5,6,7,0 };
	//int arr[] = { 9,17,3,7,31,29,47,23,71,35,8};
	int size = sizeof(arr) / sizeof(arr[0]);
	
	vector<int>test({ 1,2,3,4,7,1,2,3,4 });
	/*BubbleSort(test);
	SelectSort(test);
	QuickSort(test,false);*/
	//InsertionSort(test,false);
	//MergeSort(test,false);
	//
	
	//邻接多重表--未完成
	/*vector<vector<int>>data({
		{0,1,0,1,0},
		{1,0,1,0,1},
		{0,1,0,1,1},
		{1,0,1,0,0},
		{0,1,1,0,0},
		});
	MulityList* ml = new MulityList(data);
	ml->Print();*/

	//十字链表
	/*string des =
		"A:BC#"
		"B:#"
		"C:AD#"
		"D:ABC#";
	vector<vector<int>>data({
		{0,1,1,0},
		{0,0,0,0},
		{1,0,0,1},
		{1,1,1,0},
		});
	CrossLinkedList* cll = new CrossLinkedList(des);
	cll->Print();
	cll->PrintInDegrre(2);
	cll->PrintOutDegrre(2);
	cll->PrintInDegrre(1);
	cll->PrintOutDegrre(1);*/
	//邻接表
	/*string des =
		"A:BCDE#"
		"B:D#"
		"C:E#"
		"D:#"
		"E:DB#";
	vector<vector<int>>data({
		{0,0,0,0,0},
		{1,0,6,0,1},
		{1,0,0,0,1},
		{1,0,1,0,1},
		{1,0,1,0,1}
		});
	ListGraph* lg = new ListGraph(des);
	lg->Print();
	cout << lg->outDegrre(0) << endl;*/

	//邻接矩阵
	/*vector<vector<int>>data({
		{0,0,0,0,0},
		{1,0,6,0,1},
		{1,0,0,0,1},
		{1,0,1,0,1},
		{1,0,1,0,1}
		});
	
	MatrixGraph* mg = new MatrixGraph(data);
	cout << mg->inDegrre(2) << endl;
	cout << mg->outDegrre(1) << endl;
	cout << mg->weight(1,2) << endl;
	mg->Print();*/

	//线段树
	/*vector<int>test2({ 3,20,11,19,6,2});
	SegmentTree* sgt = new SegmentTree(test2);
	sgt->PrintMin();
	sgt->PrintMax();
	sgt->PrintSum();
	sgt->UpdataPoint(6, 1);
	cout << sgt->QueryMin(2, 1) << endl;
	cout << sgt->QueryMax(2, 1) << endl;
	sgt->PrintMin();
	sgt->PrintMax();
	sgt->PrintSum();
	sgt->UpdataRangle(1, 0, 5);
	sgt->PrintMin();
	sgt->PrintMax();
	sgt->PrintSum();*/

	//哈夫曼树
	/*HFTree* hf = new HFTree("AAABBCKKKK");
	hf->PrintChar_Code();
	hf->PrintCode();
	hf->ReConstructTree("ABAACDC");
	hf->PrintChar_Code();
	hf->PrintCode();
	delete hf;*/


	//树状数组
	/*BIT<int>* bit = new BIT<int>(arr, size);
	bit->Print();
	bit->update(12, 5);
	bit->Print();
	cout << bit->query(1);
	cout << bit->query(2, 4);
	vector<int> arr2({ 12,77,8,2,9,0 });
	cout << bit->InversePairs(arr2) << endl;
	while (1)
	{
		int a;
		cin >> a;
		cout << bit->get(a) << endl;
	}*/
	
	
	//堆
	/*Heap<int>* minheap = new Heap<int>(arr, size);
	Heap<int>* maxheap = new Heap<int>(arr, size,false);
	
	minheap->Print();
	minheap->Pop();
	minheap->Print();
	minheap->Pop();
	minheap->Print();
	minheap->Pop();
	minheap->Print();
	minheap->Pop();
	minheap->Print();

	maxheap->Print();
	maxheap->Pop();
	maxheap->Print();
	maxheap->Pop();
	maxheap->Print();
	maxheap->Pop();
	maxheap->Print();
	maxheap->Pop();

	minheap->Print();
	minheap->Sort();
	minheap->Print();
	maxheap->Print();
	maxheap->Sort();
	maxheap->Print();*/

	//B+树
	/*BPlusTree<int>* BPT = new BPlusTree<int>(arr, size);
	BPT->LevelPrint();
	BPT->Remove(8);
	BPT->Remove(9);
	BPT->Remove(71);
	BPT->LevelPrint();
	BPT->PrintLinkList();
	delete BPT;*/

	//B树
	/*BTree<int>* BT = new BTree<int>(arr, size);
	BT->LevelPrint();
	BTreeNode<int>* re = BT->Search(17);
	if (re == nullptr)
	{
		cout << "nullptr" << endl;
	}
	else
	{
		for (auto i : re->values)
		{
			cout << i << endl;
		}
	}*/
	
	//BT->Remove(17);
	//BT->LevelPrint();


	//红黑树
	/*RBT<int>* rbt = new RBT<int>(arr, size);
	rbt->LevelPrint();
	rbt->InPrint(); 
	rbt->PrintSerializedStr();
	rbt->Init(rbt->Deserialize(rbt->Serialize()));
	rbt->LevelPrint();
	rbt->PrintSerializedStr();*/

	//平衡二叉树
	/*AVL<int>* avl = new AVL<int>(arr, size);
	avl->LevelPrint();
	avl->Remove(4);
	avl->LevelPrint();
	cout<<avl->GetHeight(4);*/
	//cout << avl->MaxNode()->value;
	
	//二叉搜索树(BST)
	/*BST<int>* bbt = new BST<int>(arr, size);
	bbt->PrePrint();
	bbt->InPrint();
	bbt->PostPrint();
	bbt->LevelPrint();
	bbt->TreeDepth();
	delete bbt;*/
	
	//串
	/*SequenceString *SString=new SequenceString("11111117,w,w,w,w,e,,rr11111118");
	SString->Print();
	const char* ch = "ABACABABAAABBBCC";
	int* next = new int[strlen(ch)];
	SString->BuildNext(ch);
	cout << SString->Index("11111118") << endl;
	cout << SString->KMPMatch("11111118") << endl;*/

	//单链表
	/*SLinkList<int>* SL = new SLinkList<int>(arr, 4);
	SL->ShowList();
	delete SL;

	//双链表
	DLinkList<int>* DL = new DLinkList<int>(arr, 4);
	DL->ShowList();
	delete DL;

	//循环单链表
	SLinkList_Loop<int>* SL_Loop = new SLinkList_Loop<int>();
	SL_Loop->ShowList();
	delete SL_Loop;*/

	//循环双链表
	/*DLinkList_Loop<int>* DL_Loop = new DLinkList_Loop<int>(arr, size);
	DL_Loop->Insert(7, 9);
	DL_Loop->ShowListN();
	DL_Loop->ShowListP();
	delete DL_Loop;*/

	//静态链表
	/*StaticLinkList<int>* StaticL = new StaticLinkList<int>(arr, size);
	StaticL->Insert(7, 9);
	StaticL->ShowList();
	StaticL->ShowAllNode();*/

	//顺序栈
	/*SeqStack<int>* SStack = new SeqStack<int>(arr, size);
	SStack->Print();
	SStack->Pop();
	SStack->Print();*/

	//链式栈
	/*LinkStack<int>* LStack = new LinkStack<int>(arr, size);
	LStack->Print();
	LStack->Pop();
	LStack->Print();*/

	//顺序队列
	/*SQueue_Loop<int>* SQueue_Loop = new SQueue_Loop<int>(arr,size);
	SQueue_Loop->Print();
	SQueue_Loop->Pop();
	SQueue_Loop->Print();
	SQueue_Loop->Push(10);
	SQueue_Loop->Print();
	delete SQueue_Loop;*/

	//链式队列
	/*LinkQueue<int>* LQueue = new LinkQueue<int>(arr, size);
	LQueue->Print();
	LQueue->Pop();
	LQueue->Print();
	LQueue->Push(10);
	LQueue->Push(10);
	LQueue->Push(10);
	LQueue->Print();
	delete LQueue;*/

	//双端循环顺序队列
	/*DQueue_Loop<int>* SQueue = new DQueue_Loop<int>(arr,size);
	SQueue->Print();
	SQueue->Pop_back();
	SQueue->Print();
	SQueue->Push_front(10);
	SQueue->Print();
	delete SQueue;*/
}