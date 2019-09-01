#include "AATree.h"
#include<iostream>
using std::cout;
using std::cin;
using std::endl;
using namespace AA_TREE;


AATree::AATree()
{
	nullNode = new AANode;
	nullNode->left = nullNode->right = nullNode;
	nullNode->level = 0;
	root = nullNode;
}


AATree::~AATree()
{
	clear(root);
}

bool AA_TREE::AATree::insert(int element, string name)
{
	return insert(element, name, root);
}

bool AA_TREE::AATree::remove(int element)
{
	return remove(element, root);
}

void AA_TREE::AATree::clear()
{
	clear(root);
	root = nullNode;
}

bool AA_TREE::AATree::find(int element)
{
	return find(element, root);
}

void AA_TREE::AATree::rotateWithLeftChild(AANode *& k2)
{
	AANode *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2 = k1;
}

void AA_TREE::AATree::rotateWithRightChild(AANode *& k1)
{
	AANode *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1 = k2;
}

void AA_TREE::AATree::skew(AANode *& t)
{
	if (t->left->level == t->level)
		rotateWithLeftChild(t);
}

void AA_TREE::AATree::split(AANode *& t)
{
	if (t->right->right->level == t->level)
	{
		rotateWithRightChild(t);
		t->level++;
	}
}

void AA_TREE::AATree::clear(AANode * t)
{
	if (t == nullNode);
	else
	{
		clear(t->left);
		clear(t->right);
		delete t;
	}
}

bool AA_TREE::AATree::find(int element, AANode * t)
{
	if (t == nullNode)
		return false;
	else if (element < t->element)
		return find(element, t->left);
	else if (element > t->element)
		return find(element, t->right);
	else
	{
		cout << "键值：" << t->element << "  " << "名称：" << t->name << endl;
		return true;
	}
}

bool AA_TREE::AATree::insert(int element, string name, AANode *& t)
{
	static bool flag = false;
	if (t == root)
		flag = false;
	if (t == nullNode)
	{
		t = new AANode(element, name, nullNode, nullNode);
		flag = true;
	}
	else if (element < t->element)
		insert(element, name, t->left);
	else if (element > t->element)
		insert(element, name, t->right);
	else
		return false;
	skew(t);
	split(t);
	if (t == root)
		return flag;
}

bool AA_TREE::AATree::remove(int element, AANode *& t)
{
	static AANode *lastNode, *deleteNode = nullNode;
	static bool flag = false;
	if (t == root)
		flag = false;
	/*通过递归保存路径并先寻找到真正的删除结点
	 *lastNode保存递归末尾结点，deleteNode保存
	 *待删除结点
	 */
	if (t != nullNode)
	{
		lastNode = t;
		if (element < t->element)
			remove(element, t->left);
		else
		{
			deleteNode = t;
		    remove(element, t->right);
		}
		if (t == lastNode)   //实际执行删除的代码部分
		{
			if (deleteNode == nullNode || element != deleteNode->element)  //没有找到待删除结点或者待删除结点已经删除
				return false;
			deleteNode->element = t->element;  //用其右子树的最小结点替代删除结点，进行删除操作
			deleteNode->name = t->name;
			t = t->right;     //如果其子树的最小结点存在儿子，必然是右儿子，然后链接到其右儿子
			delete lastNode;
			flag = true;
		}
		/*该部分执行AA树的调整部分*/
		else
			if (t->left->level < t->level - 1 || t->right->level < t->level - 1)   //如果删除一个结点后导致邻层的高度间距大于1时就需要调整（降低高层高度）
			{
				if (t->right->level > --t->level)    //降低高层的高度，如果高层结点有水平右链接，则其水平右链接的高度也需要降低
					t->right->level = t->level;
				/*可以知道高度降低最多会导致同一层出现6个结点，故最多出现3个左水平链接或者2个连续
				 *的右水平链接，所以通过3次skew和2次split必然可以解决所有的情况
				 */
				skew(t);
				skew(t->right);
				skew(t->right->right);
				split(t);
				split(t->right);
			}
	}
	if (t == root)
		return flag;
}

void AA_TREE::insert(AATree & tree)
{
	int element;
	string name;
	cout << "请输入键值与名称：" << endl;
	cin >> element >> name;
	if (tree.insert(element, name))
		cout << "插入成功" << endl;
	else
		cout << "插入失败" << endl;
}

void AA_TREE::remove(AATree & tree)
{
	int element;
	cout << "请输入键值：" << endl;
	cin >> element;
	if (tree.remove(element))
		cout << "删除成功" << endl;
	else
		cout << "删除失败" << endl;
}

void AA_TREE::find(AATree & tree)
{
	int element;
	cout << "请输入待查找的结点键值：" << endl;
	cin >> element;
	if (tree.find(element));
	else
		cout << "该结点不存在" << endl;
}
