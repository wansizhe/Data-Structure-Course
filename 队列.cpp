#include<iostream>
using namespace std;
#define max 10
typedef int atype;

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

class cyc_queue
{
public:
	int front;
	int rear;
	atype* base;

	cyc_queue();
	~cyc_queue();
	void initial();
	int getlen();
	void enqueue(atype e);
	void dequeue(atype &e);
	int is_empty();
	void gethead(atype &e);
	void display();
};
cyc_queue::cyc_queue()
{
	front = 0;
	rear =0;
	base = NULL;
}
cyc_queue::~cyc_queue()
{
	if(base!=NULL)
		delete base;
}
void cyc_queue::initial()
{
	base = new atype[max];
	front = 0;
	rear = 0;
	return;
}
int cyc_queue::getlen()
{
	return (rear - front + max) % max;
}
void cyc_queue::enqueue(atype e)
{
	if ((rear + 1) % max == front)
		return;
	base[rear] = e;
	rear = (rear + 1) % max;
	return;
}
void cyc_queue::dequeue(atype &e)
{
	if (rear == front)
		return;
	e = base[front];
	front = (front + 1) % max;
	return;
}
int cyc_queue::is_empty()
{
	if (rear == front)
		return 0;
	else
		return 1;
}
void cyc_queue::gethead(atype &e)
{
	if (rear == front)
		return;
	e = base[front];
	return;
}
void cyc_queue::display()
{
	for (int i = front; i < rear;)
	{
		cout << base[i] << "  ";
		i = (i + 1) % max;
	}
	cout << endl;
	return;
}


int main()
{
	lin_queue linq;
	atype elem;
	int x;

	cout << "*****������*****" << endl;
	getchar();

	cout << "==========" << endl;
	cout << "��ʼ��" << endl;
	getchar();
	linq.initial();
	cout << "�ѳ�ʼ��" << endl;
	getchar();

	cout << "==========" << endl;
	cout << "�жϿ�" << endl;
	getchar();
	x=linq.is_empty();
	cout << "���ж�    " ;
	if (x == 0)
		cout << "Ϊ��" << endl;
	else
		cout << "��Ϊ��" << endl;
	getchar();

	cout << "==========" << endl;
	cout << "���" << endl;
	getchar();
	cout << "����10����" << endl;
	for (int i = 1; i <= 10; i++)
	{
		cin >> elem;
		linq.enqueue(elem);
	}
	cout << "�����" << endl;
	linq.display();
	getchar();
	getchar();

	cout << "==========" << endl;
	cout << "�жϿ�" << endl;
	getchar();
	x = linq.is_empty();
	cout << "���ж�    ";
	if (x == 0)
		cout << "Ϊ��" << endl;
	else
		cout << "��Ϊ��" << endl;
	linq.display();
	getchar();

	cout << "==========" << endl;
	cout << "ȡ����" << endl;
	getchar();
    linq.gethead(elem);
	cout << "�ѻ�ȡ    elem="<<elem<<endl;
	linq.display();
	getchar();

	cout << "==========" << endl;
	cout << "����(4��Ԫ��)" << endl;
	getchar();
	for (int i = 1; i <= 4; i++)
	{
		linq.dequeue(elem);
		cout << elem << "  ";
	}
	cout << endl;
	cout << "�ѳ���" << endl;
	linq.display();
	getchar();

	cout << "==========" << endl;
	cout << "����" << endl;
	getchar();
	linq.destroy();
	cout << "������" << endl;
	getchar();


	cyc_queue cycq;

	cout << "*****ѭ������*****" << endl;
	getchar();

	cout << "==========" << endl;
	cout << "��ʼ��" << endl;
	getchar();
	cycq.initial();
	cout << "�ѳ�ʼ��" << endl;
	getchar();

	cout << "==========" << endl;
	cout << "�жϿ�" << endl;
	getchar();
	x = cycq.is_empty();
	cout << "���ж�    ";
	if (x == 0)
		cout << "Ϊ��" << endl;
	else
		cout << "��Ϊ��" << endl;
	getchar();

	cout << "==========" << endl;
	cout << "���" << endl;
	getchar();
	cout << "����10����" << endl;
	for (int i = 1; i <= 10; i++)
	{
		cin >> elem;
		cycq.enqueue(elem);
	}
	cout << "�����" << endl;
	cycq.display();
	getchar();
	getchar();

	cout << "==========" << endl;
	cout << "�жϿ�" << endl;
	getchar();
	x = cycq.is_empty();
	cout << "���ж�    ";
	if (x == 0)
		cout << "Ϊ��" << endl;
	else
		cout << "��Ϊ��" << endl;
	cycq.display();
	getchar();

	cout << "==========" << endl;
	cout << "ȡ����" << endl;
	getchar();
	cycq.gethead(elem);
	cout << "�ѻ�ȡ    elem=" << elem << endl;
	cycq.display();
	getchar();

	cout << "==========" << endl;
	cout << "����(4��Ԫ��)" << endl;
	getchar();
	for (int i = 1; i <= 4; i++)
	{
		cycq.dequeue(elem);
		cout << elem << "  ";
	}
	cout << endl;
	cout << "�ѳ���" << endl;
	cycq.display();
	getchar();

	return 0;
}