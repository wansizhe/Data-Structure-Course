#include<iostream>
#include<string>
#include<cstring>
using namespace std;

typedef string atype;
struct node
{
	atype data;
	node* next;
};

class List
{
public:
	node* first;
	node* last;
	int length;

	List();
	List(int size);
	~List();
	int retrieve(int i, atype &e);
	int insert(int i,const atype &e);
	int remove(int i, atype &e);
	int size()const;
	void display();
	bool is_full()const;
	bool is_empty()const;
	void clear();
	int replace(int i, const atype &x);
	int append(const atype &x);
};
List::List()
{
	first = new node;
	first->next = NULL;
	last = first;
	length = 0;
}
List::List(int size)
{
	first = new node;
	first->next = NULL;
	last = first;
	length = size;
	node* p = new node;
	p->data='\0';
	p->next = first->next;
	first->next = p;
	last = p;
	for (int i = 1; i < size; i++)
	{
		p = new node;
		p->data='\0' ;
		p->next = first->next;
		first->next = p;
	}
}
List::~List()
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
int List::retrieve(int i, atype &e)
{
	if (first->next == NULL|| i > length)
		return -1;
	node* p = first->next;
	int j = 1;
	while (p != NULL&&j<i)
	{
		p = p->next;
		j++;
	}
	if (p != NULL&&j == i)
		e = p->data;
	return 0;
}
int List::insert(int i, const atype &e)
{
	if (first->next == NULL || i > length)
		return -1;
	node* p = first;
	int j = 0;
	while (p != NULL&&j != i - 1)
	{
		p = p->next;
		j++;
	}
	if (p != NULL&&j == i - 1)
	{
		node* t = new node;
		t->data = e;
		t->next = p->next;
		if (p->next == NULL)
			last = t;
		p->next = t;
		length++;
	}
	return 0;
}
int List::remove(int i, atype &e)
{
	if (first->next == NULL || i > length)
		return -1;
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
	return 0;
}
int List::size()const
{
	return length;
}
void List::display()
{
	if (first == NULL)
		return;
	node* p = first->next;
	int i = 1;
	while (p != NULL)
	{
		cout <<"{["<<i<<']'<< p->data <<'[';
		if (i + 1 > length)
			cout << "null" << "]}    ";
		else
			cout << i + 1 << "]}    ";
		p = p->next;
		if (i % 3 == 0)
			cout << endl;
		i++;
	}
	cout << endl;
	return;
}
bool List::is_full()const
{
	if (first->next == NULL)
		return true;
	int i=0;
	node* p;
	p = first->next;
	for(int j=0;j<length;j++)
		if (p->data[0] != '\0')
		{
			i++;
			p = p->next;
		}
	if (i != length)
		return false;
	else
		return true;
}
bool List::is_empty()const
{
	if (first->next == NULL)
		return true;
	int i = 0;
	node* p;
	p = first->next;
	for (int j = 0; j<length; j++)
		if (p->data[0] != '\0')
		{
			i++;
			p = p->next;
		}
	if (i != 0)
		return false;
	else
		return true;
}
void List::clear()
{
	if (first->next == NULL)
		return;
	node* p;
	p = first->next;
	for (int j = 0; j<length; j++)
	{
		p->data[0] = '\0';
		p = p->next;
	}
	return;
}
int List::replace(int i,const atype &x)
{
	int j = 1;
	if (first->next == NULL||i>length)
		return -1;
	node* p = first->next;
	while (i == j)
	{
		p = p->next;
		j++;
	}
	p->data = x;
	return 0;
}
int List::append(const atype &x)
{
	if (first == NULL)
		return -1;
	node* p = new node;
	p->data = x;
	p->next = NULL;
	last->next = p;
	last = p;
	return 0;
}

int main()
{
	cout << "1）按输入序列：Jan、Feb、Mar、Apr、May 建立初始链表。" << endl;
	string t[5] = { "Jan","Feb","Mar","Apr","May" };
	string s;
	List list(7);
	node* p = list.first->next;
	for (int i = 0; i < 5; i++)
	{
		p->data = t[i];
		p = p->next;
	}
	list.display();
	cout << endl;

	cout << "2）在Feb前，May之后插入Jun、Oct" << endl;
	list.insert(2, "Jun");
	list.display();
	list.insert( 7,"Oct");
	list.display();
	cout << endl;

	cout << "3）先后删除Mar和Jan" << endl;
	list.remove(4, s);
	list.display();
	list.remove(1, s);
	list.display();
	cout << endl;

	cout << "4）在Apr之前插入Dec" << endl;
	list.insert(3, "Dec");
	list.display();
	cout << endl;

	return 0;
}