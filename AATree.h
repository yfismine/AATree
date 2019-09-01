#ifndef _AATREEH_
#define _AATREEH_
#pragma once
#include<string>
using std::string;
namespace AA_TREE
{
	class AATree
	{
	public:
		AATree();
		~AATree();
		bool insert(int element, string name);
		bool remove(int element);
		void clear();
		bool find(int element);
	private:
		struct AANode
		{
			int element=0;
			string name;
			AANode *left;
			AANode *right;
			int level;
			AANode() :left(nullptr), right(nullptr), level(1) {};
			AANode(const int &e, const string n, AANode *lt, AANode *rt, int lv = 1)
				:element(e), name(n), left(lt), right(rt), level(lv) {};
		};
		AANode *nullNode;
		AANode *root;
		void rotateWithLeftChild(AANode *&k2);
		void rotateWithRightChild(AANode *&k1);
		void skew(AANode *&t);   //左旋 处理左水平链接情况
		void split(AANode *&t);  //右旋 处理连续右水平链接情况
		void clear(AANode *t);
		bool find(int element, AANode *t);
		bool insert(int element, string name, AANode *&t);
		bool remove(int element, AANode *&t);
	};
	void insert(AATree &tree);
	void remove(AATree &tree);
	void find(AATree &tree);
}
#endif

