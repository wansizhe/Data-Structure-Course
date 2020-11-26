#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>;
using namespace std;
#define max 10
typedef string atype;

struct node
{
	atype data;
	node* next;
};

class lin_queue
{
public:
	node* front;
	node* rear;
	lin_queue();
	void initial();
	void destroy();
	void enqueue(atype e);
	void dequeue(atype& e);
	int is_empty();
	void gethead(atype &e);
	void display();
};
lin_queue::lin_queue()
{
	front = NULL;
	rear = front;
}
void lin_queue::initial()
{
	front = new node;
	front->next = NULL;
	rear = front;
	return;
}
void lin_queue::destroy()
{
	while (front != NULL)
	{
		rear = front->next;
		delete front;
		front = rear;
	}
	return;
}
void lin_queue::enqueue(atype e)
{
	node* p = new node;
	p->data = e;
	p->next = NULL;
	rear->next = p;
	rear = p;
	return;
}
void lin_queue::dequeue(atype &e)
{
	if (front == rear)
		return;
	node* p = front->next;
	e = p->data;
	front->next = p->next;
	if (rear == p)
		rear = front;
	delete p;
	return;
}
int lin_queue::is_empty()
{
	if (rear == front)
		return 0;
	else
		return 1;
}
void lin_queue::gethead(atype &e)
{
	if (rear == front)
		return;
	e = front->next->data;
	return;
}
void lin_queue::display()
{
	if (front == rear)
		return;
	node* p = front->next;
	while (p != NULL)
	{
		cout << p->data << "  ";
		p = p->next;
	}
	cout << endl;
	return;
}

int main()
{
	/*生活中，打印机运用到了队列这一数据结构*/
	/*人在操作电脑时选择打印多个文件*/
	/*打印机按照人的选择顺序*/
	/*先被选择打印的文件就先被打印出来*/

	int n;
	lin_queue q;
	q.initial();
	string doc;		//文件内容
	cout << "输入文件数量，最多5个" << endl;
	cin >> n;
	cout << "输入文件内容，空格结束" << endl << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "输入第" << i + 1 << "个文件的内容：" << endl;
		cin >> doc;
		cout << endl;
		q.enqueue(doc);
	}
	
	ofstream fout;
	for (int i = 0; i < n; i++)
	{
		q.dequeue(doc);
		char t[2];
		t[0] = 'A' + i;
		t[1] = '\0';
		char tt[7] = "doc_";
		strcat(tt, t);
		fout.open(tt, ios::out);
		if (fout.is_open())
		{
			fout << doc;
			fout.close();
			cout << '[' << tt << ']' <<"  打印成功" << endl;
		}
		else
		{
			cout <<'['<< tt <<']'<< endl;
			cout << "{\t" << doc << "\t}" << endl;
			cout << "打印失败" << endl;
		}
	}
	return 0;
}