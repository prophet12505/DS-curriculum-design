#include <iostream>
#include <regex>
#include <string>
#include "Queue.h"

const regex int_type("\\d+");

struct TwoQueues {
	Queue<int> a;
	Queue<int> b;
};


TwoQueues IstreamFun()
{
	TwoQueues tq;
	Queue<int> qA, qB;
	string num_str, id_str;
	int num, id;
	cin >> num_str;
	if (!regex_match(num_str, int_type)) {
		cout << "第一个数请输入正整数！"; 
		exit(1);
	}
	num = stoi(num_str);
	for (int i = 0; i < num; i++) {
		cin >> id_str;
		if (!regex_match(id_str, int_type)) {
			cout << "第" << i+2 << "个数请输入正整数！";
			exit(1);
		}
		id = stoi(id_str);
		if (id % 2 != 0) {
			qA.EnQueue(id);
		}
		else
			qB.EnQueue(id);
	}
	tq.a = qA;
	tq.b = qB;
	return tq;
}

void OstreamFun(TwoQueues tq)
{
	Queue<int> qA = tq.a;     
	Queue<int> qB = tq.b;
	//qC is used to print(just make the code more perceptual)
	Queue<int> qC;
	int data;
	int time = 0;
	for (; ; ) {
		++time;
		if (!qA.isEmpty()) {
			data = qA.DeQueue();
			qC.EnQueue(data);
		}
		if(!qB.isEmpty()&&time%2==0) {
			data = qB.DeQueue();
			qC.EnQueue(data);
		}
		if (qA.isEmpty() && qB.isEmpty())
			break;
	}
	qC.print();
}

int main()
{
	TwoQueues t = IstreamFun();
	OstreamFun(t);
}
