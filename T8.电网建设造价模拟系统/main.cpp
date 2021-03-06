#include "Graphlnk.h"
#include "Heap.h"
#include "MinSpanTree.h"
#include <iomanip>
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;


template<typename T, typename E>
void Prim(const T u0, Graphlnk<T, E>& G, MinSpanTree<T, E>& MST) {
	// u0 is the first vertex
	MSTEdgeNode<T, E> ed;
	int i, u, v, count;
	int n = G.getNumVertices();
	int m = G.getNumEdges();
	u = G.getVertexPos(u0);
	Heap<T, E> H(m);
	// Vmst[] record the vertex that has visted
	bool *Vmst = new bool[n];
	for (int i = 0; i < n; i++) {
		Vmst[i] = false;
	}
	Vmst[u] = true;
	count = 1;
	while (count < n) {
		v = G.getFirstNeighbor(u);
		// insert the adjacent edges to the heap
		while (v != -1) {
			if (Vmst[v] == false) {
				ed.head = v;
				ed.tail = u;
				ed.key = G.getWeight(u, v);
				H.insert(ed);
			}
			v = G.getNextNeighbor(u, v);
		}
		while (!(H.isEmpty()) && count < n) {
			// extract the min node
			H.extract(ed);
			// add all the edges of this vertex
			if (Vmst[ed.head] == false) {
				MST.InsertNode(ed);
				u = ed.head;
				Vmst[u] = true;
				count++;
				break;
			}
		}
	}
}

void addVertexes(Graphlnk<char, int>& G, int& numCount) {
	cout << "请输入顶点的个数：";
	int n;
	cin >> n;
	numCount = n;
	cout << "请输入各个顶点的名称：";
	while (n > 0) {
		char name;
		cin >> name;
		G.insertVertex(name);
		n--;
	}
}

void addEdges(Graphlnk<char, int>& G) {
	int loop = 1;
	while (loop) {
		cout << "请输入两个顶点及边：";
		char v1,v2;
		int weight;
		cin >> v1 >> v2 >> weight;
		if (v1 == '?' || v2 == '?') {
			loop = 0;
			break;
		}
		int v1_pos = G.getVertexPos(v1);
		int v2_pos = G.getVertexPos(v2);
		if (!G.insertEdge(v1_pos, v2_pos, weight)) {
			cerr << "顶点创建失败，请检查后重新输入" << endl;
		}
	}
}


int main() {
	cout << "**" << setw(10) << ' ' << "电网造价模拟系统" << setw(10) << ' ' << "**" << endl;
	cout << "==========================================" << endl;
	cout << "**" << setw(9) << ' ' << "A --- 创建电网顶点" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "B --- 添加电网的边" << setw(9) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "C --- 构造最小生成树" << setw(7) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "D --- 显示最小生成树" << setw(7) << ' ' << "**" << endl;
	cout << "**" << setw(9) << ' ' << "E --- 退出程序" << setw(13) << ' ' << "**" << endl;
	cout << "==========================================" << endl;
	
	Graphlnk<char, int> G;
	MinSpanTree<char, int> MST;
	int numVertices = 0;
	string option;
	int loop = 1;
	int Init = 0;
	while (loop) {
		cout << endl << "请选择操作：";
		cin >> option;
		switch (option[0]) {
		case 'A':
			if (Init == 1) {
				cerr << "已有电网存在，不要重复创建" << endl;
			}
			else {
				addVertexes(G, numVertices);
				Init = 1;
			}
			break;
		case 'B':
			if (Init != 1) {
				cout << "请先创建电网" << endl;
			}
			else {
				addEdges(G);
			}
			break;
		case 'C':
			if (Init != 1) {
				cout << "请先创建电网" << endl;
				break;
			}
			cout << "请输入起始顶点：";
			char begin;
			cin >> begin;
			Prim(begin, G, MST);
			cout << "生成Prim最小生成树!" << endl;
			break;
		case 'D': {
			if (Init != 1) {
				cout << "请先创建电网" << endl;
				break;
			}
			cout << "最小生成树的顶点及边分别为：" << endl;
			for (int i = 0; i < numVertices - 1; i++) {
				char head = G.getValue(MST.edgevalue[i].tail);
				char tail = G.getValue(MST.edgevalue[i].head);
				cout << head << "-<" << MST.edgevalue[i].key << ">->" << tail;
				if (i != numVertices - 2) {
					cout << "\t";
				}
			}
			cout << endl;
			break;
		}
		case 'E':
			loop = 0;
			break;
		default:
			cout << "选项不存在，请重新输入" << endl;
			break;
		}
	}
}
