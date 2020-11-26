#include<iostream>
#include<cmath>
using namespace std;

typedef float atype;
struct node
{
	atype data;
	int pow;
	node* next;
};
/*单链表类*/
class term
{
public:
	node* first;
	int length;

	term();
	~term();
	void creat(int n);
	void display();
	void value(float&sum, float x);
};
term::term()
{
	first = new node;
	first->next = NULL;
	length = 0;
}
term::~term()
{
	if (first!=NULL&&first->next != NULL)
	{
		node* p = first->next;
		while (p != NULL)
		{
			node* t = p->next;
			delete p;
			p = t;
		}
		delete first;
	}
	length = 0;
}
void term::creat(int n)
{
	node* p;
	node *k = first;
	if (n == 0)
	{
		first->next = new node;
		first->next->next = NULL;
		first->next->data = 0;
		first->next->pow = 0;
	}
	else
	{
		for (int i = n; i > 0; i--)
		{
			p = new node;
			cin >> p->data >> p->pow;
			if (p->data != 0)
			{
				p->next = k->next;
				k->next = p;
				k = p;
				length++;
			}
		}
	}
	return;
}
void term::display()
{
	if (first == NULL)
		return;
	node* p = first->next;
	int i = 0;
	if (p == NULL)
		cout << '0';
	while (p != NULL)
	{
		if (p->data == 0)
		{
			p = p->next;
			continue;
		}
		if (i != 0 && p->data >= 0)
			cout << "+ ";
		if (p->data<0)
		{
			cout << '-';
			if (i != 0)
				cout << ' ';
		}
		if(!(fabs(p->data)==0|| fabs(p->data)==1&&p->pow!=0))
			cout << fabs(p->data);
		if (p->pow != 0)
			cout << 'x';
		if (p->pow != 1 && p->pow != 0)
			cout << '^' << p->pow;
		cout << ' ';
		p = p->next;
		i++;
	}
	cout << endl;
	return;
}
/*求值，将x值代入*/
void term::value(float&sum, float x)
{
	sum = 0;
	node* p = first->next;
	if (first == NULL || first->next == NULL)
		return;
	while (p != NULL)
	{
		sum = sum + p->data*pow(x, p->pow);
		p = p->next;
	}
	return;
}
/*t1被赋为t2，t2置0*/
void tcopy_set0(term &t1, term &t2)
{
	if (t1.first->next != NULL)		//销毁t1，
	{
		node* p = t1.first->next;
		while (p != NULL)
		{
			node* t0 = p->next;
			delete p;
			p = t0;
		}
	}
	t1.length = 0;
	t1.first->next = t2.first->next;		//交换t1，t2头结点指向
	t1.length = t2.length;
	t2.first->next = NULL;
	t2.length = 0;
	return;

}
/*加*/
void tplus(term &t1, term &t2, term &t)
{
	node* p = t1.first->next, *q = t2.first->next, *k = t.first;
	node* m;
	while (p != NULL&&q != NULL)
	{
		m = new node;
		m->data = 0;
		if (p->pow>q->pow)
		{
			m->pow = q->pow;
			m->data = q->data;
			q = q->next;

			m->next = k->next;
			k->next = m;
			k = k->next;
			t.length++;
		}
		else if (q->pow>p->pow)
		{
			m->pow = p->pow;
			m->data = p->data;
			p = p->next;

			m->next = k->next;
			k->next = m;
			k = k->next;
			t.length++;
		}
		else if (p->pow == q->pow&&p->data + q->data != 0)
		{
			m->pow = p->pow;
			m->data = p->data + q->data;
			p = p->next;
			q = q->next;

			m->next = k->next;
			k->next = m;
			k = k->next;
			t.length++;
		}
		else if (p->pow == q->pow&&p->data + q->data == 0)
		{
			p = p->next;
			q = q->next;
		}
	}
	if (p == NULL&&q != NULL)
	{
		while (q != NULL)
		{
			m = new node;
			m->data = q->data;
			m->pow = q->pow;
			q = q->next;
			m->next = k->next;
			k->next = m;
			k = k->next;
			t.length++;
		}
	}
	else if (p != NULL&&q == NULL)
	{
		while (p != NULL)
		{
			m = new node;
			m->data = p->data;
			m->pow = p->pow;
			p = p->next;
			m->next = k->next;
			k->next = m;
			k = k->next;
			t.length++;
		}
	}
	return;
}
/*减*/
void tminus(term &t1, term &t2, term &t)
{
	node* p = t1.first->next, *q = t2.first->next, *k = t.first;
	node* m;
	while (p != NULL&&q != NULL)
	{
		m = new node;
		m->data = 0;
		if (p->pow>q->pow)
		{
			m->pow = q->pow;
			m->data = 0 - q->data;
			q = q->next;

			m->next = k->next;
			k->next = m;
			k = k->next;
			t.length++;
		}
		else if (q->pow>p->pow)
		{
			m->pow = p->pow;
			m->data = p->data;
			p = p->next;

			m->next = k->next;
			k->next = m;
			k = k->next;
			t.length++;
		}
		else if (p->pow == q->pow&&p->data - q->data != 0)
		{
			m->pow = p->pow;
			m->data = p->data - q->data;
			p = p->next;
			q = q->next;

			m->next = k->next;
			k->next = m;
			k = k->next;
			t.length++;
		}
		else if (p->pow == q->pow&&p->data - q->data == 0)
		{
			p = p->next;
			q = q->next;
		}
	}
	if (p == NULL&&q != NULL)
	{
		while (q != NULL)
		{
			m = new node;
			m->data = q->data;
			m->pow = q->pow;
			q = q->next;
			m->next = k->next;
			k->next = m;
			k = k->next;
			t.length++;
		}
	}
	else if (p != NULL&&q == NULL)
	{
		while (p != NULL)
		{
			m = new node;
			m->data = p->data;
			m->pow = p->pow;
			p = p->next;
			m->next = k->next;
			k->next = m;
			k = k->next;
			t.length++;
		}
	}
	return;
}
/*乘*/
void tmulti(term &t1, term &t2, term &t)
{
	if (t.first->next != NULL)
	{
		node* p = t.first->next;
		while (p != NULL)
		{
			node* t0 = p->next;
			delete p;
			p = t0;
		}
	}
	t.length = 0;
	node *q,* r;
	q = t2.first->next;
	term *temp = new term[t2.length];
	for (int i = 0; i <= t2.length - 1; i++)
	{
		node* m = temp[i].first;
		if (q != NULL)
		{
			r = t1.first->next;
			while (r != NULL)
			{
				node* s = new node;
				s->data = r->data*q->data;
				s->pow = r->pow + q->pow;
				s->next = m->next;
				m->next = s;
				m = s;
				r = r->next;
			}
		}

		q = q->next;
	}
	term tt;
	//tt.creat(0);
	tplus(temp[0], temp[1], t);
	for (int i = 2; i < t2.length;i++)
	{
		tplus(temp[i],t,tt);
		tcopy_set0(t, tt);
	}
	return;
}


int main()
{
	term t1, t2, tp, tm, tmu;
	int n;
	float x, sum;

	cout << "请输入多项式的项数：";
	cin >> n;
	cout << "请按指数递增的顺序依次输入每一项的 系数 和 指数 :" << endl;
	t1.creat(n);
	t1.display();
	getchar();
	getchar();
	
	cout << "请输入x的值：" << endl << "x = ";
	cin >> x;
	cout << endl;
	cout << "    ";
	t1.display();
	cout << " =  ";
	t1.value(sum, x);
	cout << sum << endl;
	getchar();
	getchar();
	
	cout << "请输入多项式的项数：";
	cin >> n;
	cout << "请按指数递增的顺序依次输入每一项的 系数 和 指数 :" << endl;
	t2.creat(n);
	t2.display();
	getchar();
	getchar();
	
	cout << "相减" << endl;
	tminus(t1, t2, tm);
	cout << endl;
	tm.display();

	getchar();
	cout << "相加" << endl;
	tplus(t1, t2, tp);
	cout << endl;
	tp.display();
	

	getchar();
	cout << "相乘" << endl;
	tmulti(t1, t2, tmu);
	cout << endl;
	tmu.display();

	getchar();
	return 0;
}