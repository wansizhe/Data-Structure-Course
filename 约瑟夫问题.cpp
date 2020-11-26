#include<iostream>
using namespace std;

typedef int atype;
struct node
{
	atype data;
	node* next;
};
/*ѭ������*/
class clinked
{
public:
	node* first;
	node* last;
	int length;

	clinked();
	~clinked();
	void creat(int n);
	void getelem(int i, atype &e);
	void insertone(int i, atype e);
	void deleteone(int i, atype &e);
	int getlen();
	void merge(clinked &list);
	int findone(atype x);
	void display();
};
clinked::clinked()
{
	first = new node;
	first->next = first;
	last = first;
	length = 0;
}
clinked::~clinked()
{
	if (first != NULL)
	{
		node* p = first->next;
		while (p != first)
		{
			node* t = p;
			p = p->next;
			delete t;
		}
		delete first;
		last = first;
		length = 0;
	}
}
void clinked::creat(int n)
{
	node* p;
	for (int i = 1; i<=n; i++)
	{
		p = new node;
		p->data = i;
		p->next = last->next;
		last->next = p;
		last = p;
		length++;
	}
	last->next = first;
	return;
}
void clinked::getelem(int i, atype &e)
{
	node* p = first->next;
	int j = 1;
	if (i > length)
	{
		i = i%length;
	}
	while (p != first&&j<i)
	{
		p = p->next;
		j++;
	}
	if (p != first&&j == i)
		e = p->data;
	return;
}
void clinked::insertone(int i, atype e)
{
	node* p = first;
	int j = 0, k = 0;

	while ((p != first || k == 0) && j != i - 1)
	{
		p = p->next;
		j++;
		if (p == first)
			k++;
	}
	if ((p != first || k == 0) && j == i - 1)
	{
		node* t = new node;
		t->data = e;
		t->next = p->next;
		if (p->next == first)
			last = t;
		p->next = t;
		last->next = first;
		length++;
	}
	return;
}
void clinked::deleteone(int i, atype &e)
{
	node* p, *q;
	int j = 0, k = 0;
	p = first;
	while ((p != first || k == 0) && j != i - 1)
	{
		p = p->next;
		j++;
		if (p == first)
			k++;
	}
	if (p->next != first&&j == i - 1)
	{
		q = p->next;
		if (q->next == first)
			last = p;
		p->next = q->next;
		e = q->data;
		delete q;
		last->next = first;
		length--;
	}
	return;
}
int clinked::getlen()
{
	return length;
}
void clinked::merge(clinked &list)
{
	length = length + list.length;
	last->next = list.first->next;
	list.last->next = first;
	delete list.first;
	list.first = NULL;
	list.last = list.first;
	return;
}
int clinked::findone(atype x)
{
	int i = 1;
	node *p;
	p = first->next;
	while (p != first&&p->data != x)
	{
		p = p->next;
		i++;
	}
	if (p == first)
		i = -1;
	return i;
}
void clinked::display()
{
	if (first == NULL)
		return;
	node* p = first->next;
	while (p != first)
	{
		cout << p->data << "  ";
		p = p->next;
	}
	cout << '(' << p->next->data << ')';
	cout << endl;
	return;
}

/*���josephus����*/
void solve(clinked &jose, int s, int m)
{
	node* p = jose.first->next, *q;
	int i = 1;
	atype e;
	while (i != s)					//���ҵ���ʼ��λ��
	{
		p = p->next;
		if (p == jose.first)
			p = p->next;
		i++;
	}
	i = 1;
	while (p!=jose.first)
	{
		if (i == m)
		{
			cout << p->data << "  ";
			q = p->next;		//������һ�ڵ�ĵ�ַ
			jose.deleteone(jose.findone(p->data), e);		//�ҵ���ǰԪ�ر�ţ�ɾ����
			i = 1;			//������Ϊ1
			p = q;
		}
		i++;
		p = p->next;
		if (p == jose.first)			//�ص�ͷ�������ǰһ��
			p = p->next;
	}

	return;
}

int main()
{
	int n, s, m;

	cout << "����������" << endl;
	cin >> n;
	cout << "���뿪ʼ���˵����" << endl;
	cin >> s;
	cout << "����������" << endl;
	cin >> m;

	clinked josephus;
	josephus.creat(n);
	cout << endl << endl;
	josephus.display();
	cout << endl;
	cout << "����˳��" << endl;
	solve(josephus, s, m);
	cout << endl;

	return 0;
}