#include<iostream>
#include<ctime>
#include"AATree.h"
using namespace std;
using namespace AA_TREE;
int main(void)
{
	AATree tree;
	int select;
	while (1)
	{
		cout << "1：插入 2：删除结点  3：查找结点 4：清空AA树 5：退出" << endl;
		cout << "请输入选择" << endl;
		try
		{
			cin >> select;
			if (!cin)
				throw runtime_error("输入的编号有误！");
		}
		catch (runtime_error err)
		{
			cout << err.what()
				<< "\n是否退出或者重新输入"
				<< "\nY:退出   N:重新输入" << endl;
			string c;
			cin.clear();
			cin.ignore(100, '\n');
			cin >> c;
			if (!cin || c == "Y")
				break;
			else
				continue;

		}
		switch (select)
		{
		case 1: insert(tree); break;
		case 2: remove(tree); break;
		case 3: find(tree); break;
		case 4: tree.clear(); break;
		case 5: return 0;
		default:cout << "编号输入错误！\n请重新输入" << endl; break;
		}
	}
}
