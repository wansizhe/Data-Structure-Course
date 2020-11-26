#include<iostream>
using namespace std;

typedef int atype;
#define max 20
/*˳��ջ*/
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
	atype* p = top - 1;
	while (p != NULL&&p != base)
	{
		cout << *p << "  ";
		p--;
	}
	cout << endl;
}
/*����ƥ��*/
int can_match(ord_stack &stor, char str[])		//�ж��Ƿ����ƥ��
{
	int e;
	for (int i = 0; i < 20; i++)
	{
		if (str[i] == '(')
			stor.push(i);
		else if (str[i] == ')')
		{
			if (stor.base == stor.top)			//ƥ�������ջΪ�գ�����ƥ��
				return 0;
			stor.pop(e);
		}
	}
	if (stor.base != stor.top)			//������ջ���գ�����ƥ��
		return 0;
	return 1;
}
void match(ord_stack &stor, char str[])
{
	int e;
	for (int i = 0; str[i]!='\0'&&i < 20; i++)
	{
		if (str[i] == '(')
			stor.push(i);				//����ջ
		else if (str[i] == ')')
		{
			stor.pop(e);					//����ջ
			cout << e << '-' << i << "  ";
		}
	}
	return;
}
/*������ʽ*/
int pri(char istk, char ostk)			//���ȼ��жϱ�ջ������������������Ƚ�
{
	if (istk == '+')
	{
		switch (ostk)
		{
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return -1;
		case '/':
			return -1;
		case '(':
			return -1;
		case ')':
			return 1;
		case '#':
			return 1;
		default:
			return 0;
		}
	}
	else if (istk == '-')
	{
		switch (ostk)
		{
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return -1;
		case '/':
			return -1;
		case '(':
			return -1;
		case ')':
			return 1;
		case '#':
			return 1;
		default:
			return 0;
		}
	}
	else if (istk == '*')
	{
		switch (ostk)
		{
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return 1;
		case '/':
			return 1;
		case '(':
			return -1;
		case ')':
			return 1;
		case '#':
			return 1;
		default:
			return 0;
		}
	}
	else if (istk == '/')
	{
		switch (ostk)
		{
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return 1;
		case '/':
			return 1;
		case '(':
			return -1;
		case ')':
			return 1;
		case '#':
			return 1;
		default:
			return 0;
		}
	}
	else if (istk == '(')
	{
		switch (ostk)
		{
		case '+':
			return -1;
		case '-':
			return -1;
		case '*':
			return -1;
		case '/':
			return -1;
		case '(':
			return -1;
		case ')':
			return 0;
		case '#':
			return 0;
		default:
			return 0;
		}
	}
	else if (istk == ')')
	{
		switch (ostk)
		{
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return 1;
		case '/':
			return 1;
		case '(':
			return 0;
		case ')':
			return 1;
		case '#':
			return 1;
		default:
			return 0;
		}
	}
	else if (istk == '#')
	{
		switch (ostk)
		{
		case '+':
			return -1;
		case '-':
			return -1;
		case '*':
			return -1;
		case '/':
			return -1;
		case '(':
			return -1;
		case ')':
			return 0;
		case '#':
			return -1;
		default:
			return 0;
		}
	}
	else
		return 0;
}
int getv(int b, char c, int a)			//��ֵ
{
	int sum=0;
	switch (c)				//����c�ķ����ж�������ʽ
	{
	case '+' :
		sum = a + b;
		break;
	case '-' :
		sum = b - a;
		break;
	case '*':
		sum = a*b;
		break;
	case '/':
		sum = b / a;
		break;
	default:
		break;
	}
	return sum;
}
void solve(ord_stack &num, ord_stack &opt ,char str[])
{
	int sum = 0;
	opt.push(int('#'));				// # �������ջ
	for (int i = 0; str[i] != '\0'&&i < 20;)
	{
		if (str[i] >= '0'&&str[i] <= '9')			// ���ǲ�����
		{
			int j = i+1;
			for (; str[j] >= '0'&&str[j] <= '9'; j++);				// ȷ��������λ��
			char *t = new char[j - i + 1];
			for (int k = 0; k <=j-i-1; k++)				// ���ַ�������ת��Ϊ������
				t[k] = str[i + k];
			t[j - i] = '\0';
			int m = atoi(t);
			num.push(m);			// ��������ջ
			i = j;
		}
		else                     // ���������
		{
			if (opt.base == opt.top - 1)			// ��ջ�����������ֱ����ջ
			{
				opt.push(int(str[i]));
				i++;
			}
			else
			{
				int e, flag;
				opt.gettop(e);			//��ȡջ��Ԫ��
				char ch = e;
				flag=pri(ch, str[i]);			//�Ƚ����ȼ�
				if (flag == -1)
				{
					opt.push(int(str[i]));
					i++;
				}
				else if (flag == 1)
				{
					int a, b, c;
					num.pop(a);
					num.pop(b);
					opt.pop(c);
					sum = getv(b, char(c), a);
					num.push(sum);
				}
				else if (flag == 0)			//�����Ż�#����
				{
					opt.pop(e);
					i++;
					if (e == int('#'))
						break;
				}
			}
		}
	}
	num.pop(sum);
	cout << endl;
	cout << " =  " << sum;
	return;
}

int main()
{
	ord_stack stor, num, opt;
	stor.initial();
	num.initial();
	opt.initial();
	char str[21];

	cout << "*****����ƥ��*****" << endl << endl;

	cout << "�����ƥ���С�������У����20����" << endl;
	cin >> str;
	if (can_match(stor, str) == 0)
		cout << "�޷�ƥ��" ;
	else
		match(stor, str);
	cout << endl << endl;

	cout << "*****���ʽ��ֵ*****" << endl << endl;
	str[0] = '\0';
	cout << "    ";
	cin >> str;
	int l = strlen(str);
	str[l] = '#';
	str[l+1] = '\0';
	solve(num, opt, str);
	cout << endl;
	cout << endl;
	getchar();
	getchar();
	return 0;
}