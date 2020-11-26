#include<iostream>
using namespace std;

typedef int atype;
#define max 10

struct node
{
	atype data;
	node *prev;
};

class ord_stack
{
public:
	atype* base;
	atype* top;
	int len;
	ord_stack();
	~ord_stack();
	void push(atype e);
	void pop(atype &e);
	void initial();
	void gettop(atype &e);
	void display();
};
ord_stack::ord_stack()
{
	base = NULL;
	top = base;
	len = 0;
}
ord_stack::~ord_stack()
{
	if (base != NULL)
		delete base;
}
void ord_stack::push(atype e)
{
	if (base == NULL)
		return;
	if (top - base >= len)
	{
		atype* p, *q;
		p = new atype[len + max];
		q = p;
		for (; q - p < len; q++)
			*q = base[q - p];
		delete base;
		base = p;
		top = q;
		len = len + max;
	}
	*top = e;
	top++;
	return;
}
void ord_stack::pop(atype &e)
{
	if (base == NULL || base == top)
		return;
	top--;
	e = *top;
	return;
}
void ord_stack::initial()
{
	base = new atype[max];
	if (base == NULL)
		return;
	top = base;
	len = max;
	return;
}
void ord_stack::gettop(atype &e)
{
	if (top == base)
		return;
	e = *(top - 1);
	return;
}
void ord_stack::display()
{
	atype* p = top-1;
	while(p!=NULL&&p!=base)
	{
		cout << *p << "  ";
		p--;
	}
	cout << endl;
}

class lin_stack
{
public:
	node* top;
	lin_stack();
	~lin_stack();
	void push(atype e);
	void pop(atype &e);
	void gettop(atype &e);
	void display();
};
lin_stack::lin_stack()
{
	top =NULL;
}
lin_stack::~lin_stack()
{
	if (top != NULL)
	{
		while (top !=NULL)
		{
			node *p = top->prev;
			delete top;
			top = p;
		}
	}
		
}
void lin_stack::push(atype e)
{
	node* p;
	p = new node;
	p->data = e;
	p->prev = top;
	top = p;
	return;
}
void lin_stack::pop(atype &e)
{
	if (top == NULL)
		return;
	e = top->data;
	node* p = top;
	top = top->prev;
	delete p;
}
void lin_stack::gettop(atype &e)
{
	if (top != NULL)
		e = top->data;
	return;
}
void lin_stack::display()
{
	node* p = top;
	while (p != NULL)
	{
		cout << p->data << "  ";
		p = p->prev;
	}
	cout << endl;
}

void num_syt_tran(int num, int base)
{
	int m, n;
	lin_stack lst;
	while (num != 0)
	{
		m = num%base;
		lst.push(m);
		num = num / base;
	}
	cout << "  =  ";
	while (lst.top != NULL)
	{
		lst.pop(n);
		if (n < 10)
			cout << n;
		else if (n >= 10 && n < 16)
			cout << char(55 + n);
	}
	switch (base)
	{
	case 2:
		cout << "(B)" << endl;
		break;
	case 8:
		cout << "(O)" << endl;
		break;
	case 16:
		cout << "(H)" << endl;
		break;
	default:
		cout << endl;
		break;
	}
	return;
}

int main()
{
	ord_stack ost;
	int elem;

	cout << endl;
	cout << "**********顺序栈**********" << endl;
	getchar();

	cout << "==========" << endl;
	cout << "初始化" << endl;
	getchar();
	ost.initial();
	cout << "已初始化" << endl;
	getchar();

	cout << "==========" << endl;
	cout << "入栈" << endl;
	getchar();
	cout << "输入12个数：" << endl;
	for (int i = 1; i <= 12; i++)
	{
		cin >> elem;
		ost.push(elem);
	}
	cout << "已入栈" << endl;
	ost.display();
	getchar();
	getchar();

	cout << "==========" << endl;
	cout << "获取栈顶元素" << endl;
	getchar();
	ost.gettop(elem);
	cout << "已获取" << endl;
	cout << "elem=" << elem << endl;
	ost.display();
	getchar();

	cout << "==========" << endl;
	cout << "出栈" << endl;
	getchar();
	cout << "出栈5个元素，按照出栈顺序分别为：" << endl;
	for (int i = 1; i <= 5; i++)
	{
		ost.pop(elem);
		cout << elem << "  ";
	}
	cout << endl;
	cout << "其余：" << endl;
	ost.display();
	getchar();

	lin_stack lst;

	cout << endl;
	cout << "**********链栈**********" << endl;
	getchar();

	cout << "==========" << endl;
	cout << "入栈" << endl;
	getchar();
	cout << "输入12个数：" << endl;
	for (int i = 1; i <= 12; i++)
	{
		cin >> elem;
		lst.push(elem);
	}
	cout << "已入栈" << endl;
	lst.display();
	getchar();
	getchar();

	cout << "==========" << endl;
	cout << "获取栈顶元素" << endl;
	getchar();
	lst.gettop(elem);
	cout << "已获取" << endl;
	cout << "elem=" << elem << endl;
	lst.display();
	getchar();

	cout << "==========" << endl;
	cout << "出栈" << endl;
	getchar();
	cout << "出栈5个元素，按照出栈顺序分别为：" << endl;
	for (int i = 1; i <= 5; i++)
	{
		lst.pop(elem);
		cout << elem << "  ";
	}
	cout << endl;
	cout << "其余：" << endl;
	lst.display();
	getchar();

	int num;

	cout << "***********数制转换**********" << endl;
	getchar();

	cout << "输入十进制数 " << endl;
	cin >> num ;
	cout << endl;
	cout << "     " << num << "(D)" << endl;
	num_syt_tran(num, 2);
	num_syt_tran(num, 8);
	num_syt_tran(num, 16);
	cout << endl;

	getchar();

	return 0;
}