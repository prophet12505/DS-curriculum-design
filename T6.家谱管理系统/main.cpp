#include "FamiTree.h"
#include "List.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

FamiTree tree = new FamiTree();

void Establish()
{
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	string name;
	cin >> name;
	TreeNode* root = new TreeNode(name);
	tree.root = root;
	cout <<  "此家谱的祖先是：" << root->name;
}


void Improve(FamiTree& tree) {
	cout << "输入要建立家庭的人的姓名：";
	string name;
	cin >> name;
	if (!(tree.Find(name, tree.root))) {
		cout << "没有找到这个人" << endl;
	}
	else {
		int num;
		cout << "请输入" << name << "的儿女人数：";
		cin >> num;
		cout << "请依次输入" << name << "的儿女姓名：";
		TreeNode* node = tree.current;
		while (num > 0) {
			string child;
			cin >> child;
			node->addChild(child);
			num--;
		}
		cout << node->name << "的第一代子孙是：";
		node->printChild();
	}
}

void AddFamiMember(FamiTree& tree) {
	cout << "输入要添加儿子（或女儿）的人的姓名：";
	string name;
	cin >> name;
	if (!(tree.Find(name, tree.root))) {
		cout << "没有找到这个人" << endl;
	}
	else {
		TreeNode* node = tree.current;
		cout << "请输入" << name << "新添加的儿子（或女儿）的姓名：";
		string child;
		cin >> child;
		node->addChild(child);
		cout << node->name << "的第一代子孙是：";
		node->printChild();
	}
}

void DeletePartialTree(FamiTree& tree) {
	cout << "输入要解散家庭的人的目前姓名：";
	string name;
	cin >> name;
	if (!(tree.Find(name, tree.root))) {
		cout << "没有找到这个人" << endl;
	}
	else {
		TreeNode* node = tree.current;
		cout << "要解散家庭的人的姓名是" << name << endl;
		if (node->firstChild == NULL) {
			cout << "可是" << node->name << "已经没有家庭了 ToT";
		}
		else {
			cout << node->name << "的第一代子孙是：";
			node->printChild();
			node->firstChild = NULL;
		}
	}
}

void ModifyMemberName(FamiTree& tree) {
	cout << "输入要更改姓名的人的目前姓名：";
	string name;
	cin >> name;
	if (!(tree.Find(name, tree.root))) {
		cout << "没有找到这个人" << endl;
	}
	else {
		TreeNode* node = tree.current;
		cout << "请输入更改后的姓名：";
		string new_name;
		cin >> new_name;
		node->name = new_name;
		cout << name << "已更名为" << new_name;
	}
}


int main()
{
	cout << "**" << setw(14) << ' ' << "家谱管理系统" << setw(16) << ' ' << "**" << endl;
	cout << "==============================================" << endl;
	cout << "**" << setw(13) << ' ' << "请选择要执行的操作" << setw(11) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "A --- 完善家谱" << setw(15) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "B --- 添加家庭成员" << setw(11) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "C --- 解散局部家庭" << setw(11) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "D --- 更改家庭成员姓名" << setw(7) << ' ' << "**" << endl;
	cout << "**" << setw(13) << ' ' << "E --- 退出程序" << setw(15) << ' ' << "**" << endl;
	cout << "==============================================" << endl;
	Establish();

	int loop = 1;

	while (loop) {
		cout << endl << endl << "请选择要执行的操作：";
		char id;
		cin >> id;
		switch (id)
		{
		case 'A':
			Improve(tree);
			break;
		case 'B':
			AddFamiMember(tree);
			break;
		case 'C':
			DeletePartialTree(tree);
			break;
		case 'D':
			ModifyMemberName(tree);
			break;
		case 'T':
			tree.pre_traversal(tree.root);
			break;
		case 'E':
			loop = 0;
			break;
		default:
			cout << "请输入正确的序号" << endl;
			break;
		}
	}
}