#include<iostream>
using namespace std;

typedef int atype;
struct node
{
	atype data;
	node* next;
};
struct dnode
{
	atype data;
	dnode* prev;
	dnode* next;
};

class linked
{
public:
	node* first;
	node* last;
	int length;

	linked();
	~linked();
	void creat(int n);
	void getelem(int i, atype &e);
	void insertone(int i, atype e);
	void deleteone(int i, atype &e);
	void merge(linked &list);
	int getlen();
	int findone(atype x);
	void unionlist(linked &list);
	void display();
	void resverse();
	void deletespr();
};
linked::linked()
{
	first = new node;
	first->next = NULL;
	last = first;
	length = 0;
}
linked::~linked()
{
		node* p = first->next;
		while (p != NULL)
		{
			node* t = p->next;
			delete p;
			p = t;
		}
		delete first;
		last = first;
		length = 0;
}
void linked::creat(int n)
{
	node* p;
	for (int i = n; i>0; i--)
	{
		p = new node;
		cin >> p->data;
		p->next = last->next;
		last->next = p;
		last = p;
		length++;
	}
	return;
}
void linked::getelem(int i, atype &e)
{
	node* p = first->next;
	int j = 1;
	while (p != NULL&&j<i)
	{
		p = p->next;
		j++;
	}
	if (p != NULL&&j == i)
		e = p->data;
	return;
}
void linked::insertone(int i, atype e)
{
	node* p = first;
	int j = 0;
	while (p != NULL&&j != i - 1)
	{
		p = p->next;
		j++;
	}
	if (p != NULL&&j == i-1)
	{
		node* t = new node;
		t->data = e;
		t->next = p->next;
		if (p->next == NULL)
			last = t;
		p->next = t;
		length++;
	}
	return;
}
void linked::deleteone(int i, atype &e)
{
	node* p, *q;
	int j = 0;
	p = first;
	while (p != NULL&&j != i - 1)
	{
		p = p->next;
		j++;
	}
	if (p->next != NULL&&j == i - 1)
	{
		q = p->next;
		if (q->next == NULL)
			last = p;
		p->next = q->next;
		e = q->data;
		delete q;
		length--;
	}
	return;
}
void linked::merge(linked &list)
{
	node *p1, *p2, *t;
	p1 = first->next;
	p2 = list.first->next;
	t = first;
	while (p1 != NULL&&p2!=NULL)
	{
		if (p1->data <= p2->data)
		{
			t->next = p1;
			t = t->next;
			p1 = p1->next;
		}
		else
		{
			t->next = p2;
			t = t->next;
			p2 = p2->next;
		}
	}
	if (p1 == NULL)
	{
		t->next = p2;
		last = list.last;
	}
	else
		t->next = p1;
	length = length + list.length;
	list.first->next = NULL;
	list.last = list.first;
	return;
}
int linked::getlen()
{
	return length;
}
int linked::findone(atype x)
{
	int i = 1;
	node *p;
	p = first->next;
	while (p != NULL&&p->data != x)
	{
		p = p->next;
		i++;
	}
	if (p == NULL)
		i = -1;
	return i;
}
void linked::unionlist(linked &list)
{
	node *p, *q, *b;
	atype x;
	b = first->next;
	p = list.first->next;
	while (p != NULL)
	{
		x = p->data;
		q = b;
		p = p->next;
		while (q != NULL&&q->data != x)
			q = q->next;
		if (q == NULL)
		{
			q = new node;
			q->data = x;
			q->next = first->next;
			first->next = q;
		}
	}
}
void linked::display()
{
	if (first == NULL)
		return;
	node* p = first->next;
	while (p != NULL)
	{
		cout << p->data << "  ";
		p = p->next;
	}
	cout << endl;
	return;
}
void linked::resverse()
{
	if (length <= 1)
		return;
	node *p, *q;
	node* t = first->next;
	p = first->next->next;
	while (p != NULL)
	{
		q = p->next;
		p->next = first->next;
		first->next = p;
		t->next = q;
		p = q;
	}
}
void linked::deletespr()
{
	node *p, *q;
	p = first->next;
	q = first->next;
	atype x;
	int k = 1;
	while (p != NULL)
	{
		q = first;
		x = p->data;
		int i = 0;
		while (q->next != NULL)
		{
			if (q->next->data == x && (i + 1) != k)
			{
				node* m = q->next;
				q->next = m->next;
				delete m;
				length--;
			}
			else
			{
				q = q->next;
				i++;
			}
		}
		p = p->next;
		k++;
	}
}

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
	for (int i = n; i>0; i--)
	{
		p = new node;
		cin >> p->data;
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

class dlinked
{
public:
	dnode* first;
	dnode* last;
	int length;

	dlinked();
	~dlinked();
	void creat(int n);
	void getelem(int i, atype &e);
	void insertone(int i, atype e);
	void deleteone(int i, atype &e);
	void merge(dlinked &list);
	int findone(atype x);
	void display();
};
dlinked::dlinked()
{
	first = new dnode;
	first->next = NULL;
	first->prev = NULL;
	last = first;
	length = 0;
}
dlinked::~dlinked()
{
	if (first != NULL&&first->next != NULL)
	{
		dnode* p = first->next;
		while (p != NULL)
		{
			dnode* t = p;
			p = p->next;
			delete t;
		}
		delete first;
		last = first;
		length = 0;
	}
}
void dlinked::creat(int n)
{
	dnode* p;
	for (int i = n; i>0; i--)
	{
		p = new dnode;
		cin >> p->data;
		p->prev = last;
		p->next = last->next;
		last->next = p;
		last = p;
		length++;
	}
	last->next = NULL;
	first->next->prev = NULL;
	return;
}
void dlinked::getelem(int i, atype &e)
{
	dnode* p = first->next;
	int j = 1;
	if (i > length)
	{
		i = i%length;
	}
	while (p != NULL&&j<i)
	{
		p = p->next;
		j++;
	}
	if (p != NULL&&j == i)
		e = p->data;
	return;
}
void dlinked::insertone(int i, atype e)
{
	dnode* p = first;
	int j = 0;

	while ((p != NULL) && j != i - 1)
	{
		p = p->next;
		j++;
	}
	if ((p != NULL) && j == i - 1)
	{
		dnode* t = new dnode;
		t->data = e;
		t->prev = p;
		t->next = p->next;
		if (p->next == NULL)
			last = t;
		else
			t->next->prev = t;
		p->next = t;
		last->next = NULL;
		first->next->prev = NULL;
		length++;
	}
	return;
}
void dlinked::deleteone(int i, atype &e)
{
	dnode* p, *q;
	int j = 0;
	p = first;
	while ((p != NULL) && j != i - 1)
	{
		p = p->next;
		j++;
	}
	if (p->next != NULL&&j == i - 1)
	{
		q = p->next;
		if (q->next == NULL)
			last = p;
		else
			q->next->prev = p;
		p->next = q->next;
		e = q->data;
		delete q;
		last->next = NULL;
		first->next->prev = NULL;
		length--;
	}
	return;
}
void dlinked::merge(dlinked &list)
{
	length = length + list.length;
	last->next = list.first->next;
	list.first->next->prev = last;
	delete list.first;
	list.first = NULL;
	list.last = list.first;
	first->next->prev = NULL;
	return;
}
int dlinked::findone(atype x)
{
	int i = 1;
	dnode *p;
	p = first->next;
	while (p != NULL&&p->data != x)
	{
		p = p->next;
		i++;
	}
	if (p == NULL)
		i = -1;
	return i;
}
void dlinked::display()
{
	if (first == NULL)
		return;
	dnode* p = first->next;
	while (p != NULL)
	{
		if (p->prev != NULL)
			cout << '(' << p->prev->data << ')';
		cout << p->data << "  ";
		p = p->next;
	}
	//cout << '(' << p->next->data << ')';
	cout << endl;
	return;
}


int is_clink(node* first)
{
	int x = 0;
	node *p = first->next;
	while (p != NULL)
	{
		if (p == first)
		{
			x = 1;
			break;
		}
		else
			p = p->next;
	}
	return x;
}

int main()
{
	linked list, l;
	int n;
	atype e;
	int cyc;

	cout << "*****������*****" << endl;
	getchar();

	cout << "====================" << endl;
	cout << "��Enter����������" << endl;
	getchar();
	cout << "�����������ȣ�";
	cin >> n;
	cout << "����������Ԫ�أ�";
	list.creat(n);
	cout << "�Ѵ���" << endl;
	list.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter���ж������Ƿ�ѭ��" << endl;
	getchar();
	cyc = is_clink(list.first);
	cout << "���ж�    ";
	if (cyc)
		cout << "��ѭ������" << endl;
	else
		cout << "����ѭ������" << endl;
	list.display();
	cout << endl << "Enter������..." << endl;
	getchar();

	cout << "====================" << endl;
	cout << "��Enter��ɾ�����������" << endl;
	getchar();
	list.deletespr();
	cout << "��ɾ��" << endl;
	list.display();
	cout << endl << "Enter������..." << endl;
	getchar();

	cout << "====================" << endl;
	cout << "��Enter����ȡԪ��" << endl;
	getchar();
	cout << "�������ȡԪ����ţ�";
	cin >> n;
	list.getelem(n, e);
	cout << "�ѻ�ȡ    elem=";
	if (n <= list.length)
		cout << e << endl;
	else
		cout << "NULL" << endl;
	list.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter������Ԫ��" << endl;
	getchar();
	cout << "���������λ�ú�Ԫ�أ�";
	cin >> n >> e;
	list.insertone(n, e);
	cout << "�Ѳ���" << endl;
	list.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter��ɾ��" << endl;
	getchar();
	cout << "�������ɾ��Ԫ����ţ�";
	cin >> n;
	list.deleteone(n, e);
	cout << "��ɾ��    elem=" << e << endl;
	list.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter���ٴ�������" << endl;
	getchar();
	cout << "�����������ȣ�";
	cin >> n;
	cout << "����������Ԫ�أ�";
	l.creat(n);
	cout << "�Ѵ���" << endl;
	l.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter���ϲ�����" << endl;
	getchar();
	list.merge(l);
	cout << "�Ѻϲ�" << endl;
	list.display();
	cout << endl << "Enter������..." << endl;
	getchar();

	cout << "====================" << endl;
	cout << "��Enter����ȡ����" << endl;
	getchar();
	cout << "�ѻ�ȡ    length=" <<list.getlen()<< endl;
	list.display();
	cout << endl << "Enter������..." << endl;
	getchar();

	cout << "====================" << endl;
	cout << "��Enter������Ԫ��" << endl;
	getchar();
	cout << "����������ҵ�Ԫ�أ�";
	cin >> e;
	n=list.findone(e);
	cout << "�Ѳ���    ��Ԫ��" ;
	if (n == -1)
		cout << "���ڱ���" << endl;
	else
		cout << "�Ǳ��е�" << n << "��Ԫ��" << endl;
	list.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter���ٴ�������" << endl;
	getchar();
	cout << "�����������ȣ�";
	cin >> n;
	cout << "����������Ԫ�أ�";
	l.creat(n);
	cout << "�Ѵ���" << endl;
	l.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter����������" << endl;
	getchar();
	list.unionlist(l);
	cout << "�����" << endl;
	list.display();
	cout << endl << "Enter������..." << endl;
	getchar();

	cout << "====================" << endl;
	cout << "��Enter����������" << endl;
	getchar();
	list.resverse();
	cout << "������" << endl;
	list.display();
	cout << endl << "Enter������..." << endl;
	getchar();


	clinked clist, cl;
	int cn;
	atype ce;

	cout << "*****ѭ������*****" << endl;
	getchar();

	cout << "====================" << endl;
	cout << "��Enter����������" << endl;
	getchar();
	cout << "�����������ȣ�";
	cin >> cn;
	cout << "����������Ԫ�أ�";
	clist.creat(cn);
	cout << "�Ѵ���" << endl;
	clist.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter���ж������Ƿ�ѭ��" << endl;
	getchar();
	cyc = is_clink(clist.first);
	cout << "���ж�    ";
	if (cyc)
		cout << "��ѭ������" << endl;
	else
		cout << "����ѭ������" << endl;
	clist.display();
	cout << endl << "Enter������..." << endl;
	getchar();

	cout << "====================" << endl;
	cout << "��Enter����ȡԪ��" << endl;
	getchar();
	cout << "�������ȡԪ����ţ�";
	cin >> cn;
	clist.getelem(cn, ce);
	cout << "�ѻ�ȡ    elem=";
	cout << ce << endl;
	clist.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter������Ԫ��" << endl;
	getchar();
	cout << "���������λ�ú�Ԫ�أ�";
	cin >> cn >> ce;
	clist.insertone(cn, ce);
	cout << "�Ѳ���" << endl;
	clist.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter��ɾ��" << endl;
	getchar();
	cout << "�������ɾ��Ԫ����ţ�";
	cin >> cn;
	clist.deleteone(cn, ce);
	cout << "��ɾ��    elem=" << ce << endl;
	clist.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter���ٴ�������" << endl;
	getchar();
	cout << "�����������ȣ�";
	cin >> cn;
	cout << "����������Ԫ�أ�";
	cl.creat(cn);
	cout << "�Ѵ���" << endl;
	cl.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter���ϲ�����" << endl;
	getchar();
	clist.merge(cl);
	cout << "�Ѻϲ�" << endl;
	clist.display();
	cout << endl << "Enter������..." << endl;
	getchar();

	cout << "====================" << endl;
	cout << "��Enter����ȡ����" << endl;
	getchar();
	cout << "�ѻ�ȡ    length=" << clist.getlen() << endl;
	clist.display();
	cout << endl << "Enter������..." << endl;
	getchar();

	cout << "====================" << endl;
	cout << "��Enter������Ԫ��" << endl;
	getchar();
	cout << "����������ҵ�Ԫ�أ�";
	cin >> ce;
	cn = clist.findone(ce);
	cout << "�Ѳ���    ��Ԫ��";
	if (cn == -1)
		cout << "���ڱ���" << endl;
	else
		cout << "�Ǳ��е�" << cn << "��Ԫ��" << endl;
	clist.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();


	dlinked dlist, dl;
	int dn;
	atype de;

	cout << "*****˫������*****" << endl;
	getchar();

	cout << "====================" << endl;
	cout << "��Enter����������" << endl;
	getchar();
	cout << "�����������ȣ�";
	cin >> dn;
	cout << "����������Ԫ�أ�";
	dlist.creat(dn);
	cout << "�Ѵ���" << endl;
	dlist.display();
	cout << endl << "Enter������..." << endl;
	getchar();

	cout << "====================" << endl;
	cout << "��Enter����ȡԪ��" << endl;
	getchar();
	cout << "�������ȡԪ����ţ�";
	cin >> dn;
	dlist.getelem(dn, de);
	cout << "�ѻ�ȡ    elem=";
	cout << de << endl;
	dlist.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter������Ԫ��" << endl;
	getchar();
	cout << "���������λ�ú�Ԫ�أ�";
	cin >> dn >> de;
	dlist.insertone(dn, de);
	cout << "�Ѳ���" << endl;
	dlist.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter��ɾ��" << endl;
	getchar();
	cout << "�������ɾ��Ԫ����ţ�";
	cin >> dn;
	dlist.deleteone(dn, de);
	cout << "��ɾ��    elem=" << de << endl;
	dlist.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter���ٴ�������" << endl;
	getchar();
	cout << "�����������ȣ�";
	cin >> dn;
	cout << "����������Ԫ�أ�";
	dl.creat(dn);
	cout << "�Ѵ���" << endl;
	dl.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	cout << "====================" << endl;
	cout << "��Enter���ϲ�����" << endl;
	getchar();
	dlist.merge(dl);
	cout << "�Ѻϲ�" << endl;
	dlist.display();
	cout << endl << "Enter������..." << endl;
	getchar();

	cout << "====================" << endl;
	cout << "��Enter������Ԫ��" << endl;
	getchar();
	cout << "����������ҵ�Ԫ�أ�";
	cin >> de;
	dn = dlist.findone(de);
	cout << "�Ѳ���    ��Ԫ��";
	if (dn == -1)
		cout << "���ڱ���" << endl;
	else
		cout << "�Ǳ��е�" << dn << "��Ԫ��" << endl;
	dlist.display();
	cout << endl << "Enter������..." << endl;
	getchar();
	getchar();

	return 0;
}