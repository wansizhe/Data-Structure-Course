#include<iostream>
using namespace std;

typedef char chtype;			//树中data的数据类型
enum tag{child,thread};			//枚举类，标记左右指针是子树还是线索
struct tnode					//线索二叉树 or 二叉树 结点
{
	chtype data;
	tnode* left;
	tnode* right;
	tag ltag;
	tag rtag;
};			
typedef tnode* atype;				//栈和队列中data数据类型为树结点指针
const chtype sepa = '#';			//规定间隔字符
const int spacenum = 3;			//规定打印的空格数

/*顺序栈及其操作*/
#define max 20
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

/*链队列及其操作*/
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


/*二叉树及其操作*/

/*创建二叉树*/
void creat(tnode* &t)
{
	chtype m;
	 cin>>m;
	if (m == sepa)					//为null字符，指针赋null
		t = NULL;
	else
	{
		t = new tnode;				//若不是null字符，申请结点
		t->data = m;
		t->ltag=child;
		t->rtag=child;
		creat(t->left);					//以左右为根继续建立二叉树
		creat(t->right);
	}
	return;
}
/*销毁二叉树*/
void destroy(tnode* t)
{
	if (t != NULL)					
	{
		destroy(t->left);						//先销毁子树，再释放根结点
		destroy(t->right);
		delete t;
	}
	return;
}
/*先序遍历-递归*/
void prtra(tnode* t)
{
	if (t != NULL)
	{
		cout << t->data << "  ";			//先访问根结点，再遍历左右子树		
		prtra(t->left);
		prtra(t->right);
	}
	return;
}
/*中序遍历-递归*/
void intra(tnode* t)
{
	if (t != NULL)
	{
		intra(t->left);
		cout << t->data << "  ";					//先遍历左子树，再访问根结点，再遍历右子树
		intra(t->right);
	}
	return;
}
/*后序遍历-递归*/
void potra(tnode* t)
{
	if (t != NULL)
	{
		potra(t->left);
		potra(t->right);
		cout << t->data << "  ";					//先遍历左右子树，再访问根结点
	}
	return;
}
/*打印二叉树*/
void display(tnode* t, int n)
{
	if (t != NULL)
	{
		display(t->left, n + 3);
		for (int i = 1; i <= n; i++)						//先打印左子树，相邻代之间隔三个空格，再打印根结点，然后打印右子树
			cout << ' ';
		cout << t->data << endl;
		display(t->right, n + 3);
	}
	return;
}
/*求深度*/
int depth(tnode* t)
{
	int dl, dr;
	if (t != NULL)
	{
		dl = depth(t->left);
		dr = depth(t->right);
		return (dl>dr ? dl + 1 : dr + 1);				//返回较大数+1
	}
	return 0;
}
/*求结点数*/
int size(tnode* t)
{
	if (t == NULL)
		return 0;
	return (size(t->left) + size(t->right) + 1);					//返回左右结点数之和+1
}
/*交换左右子树*/
void exchange(tnode* &t)
{
	tnode *p;
	if (t != NULL)
	{
		p=t->left;
		t->left = t->right;				//交换当前结点下的左右指针
		t->right = p;
		exchange(t->left);				//交换左结点以下的指针
		exchange(t->right);			//交换右结点以下的指针
	}
	return;
}
/*复制*/
void copy(tnode* t, tnode* &tt)
{
	if (t != NULL)
	{
		tt = new tnode;
		tt->data = t->data;				//复制当前根结点
		tt->left = NULL;
		tt->right = NULL;
		tt->ltag=t->ltag;
		tt->rtag=t->rtag;
		copy(t->left, tt->left);			//复制左子树
		copy(t->right, tt->right);		//复制右子树
	}
	return;
}
/*层次遍历*/
void lvtra(tnode* t)
{
	lin_queue q;			
	q.initial();					//自建队列使用要求，手动初始化
	q.enqueue(t);			//根结点指针入队
	while (q.is_empty() == 1)
	{
		tnode* k;									//  在队列不空的情况下，循环如下操作：
		q.dequeue(k);							//  出队一个结点的地址
		if (k != NULL)							//  如果不是null
		{												//  打印结点的data
			cout << k->data;				//  左右指针依次入队
			q.enqueue(k->left);
			q.enqueue(k->right);
		}
	}
	q.destroy();				//自建队列使用要求，手动销毁释放内存
	return;
}
/*先序遍历-非递归*/
void cprtra(tnode* t)
{
	ord_stack s;		//建立新栈
	tnode* tt = t;
	s.initial();
	s.push(NULL);		//为了在最后可以让循环结束，提前进栈一个null
	while (tt != NULL)
	{
		cout << tt->data << "  ";
		if (tt->right != NULL)
			s.push(tt->right);			//右指针不为null就进栈
		if (tt->left != NULL)
			tt = tt->left;					//向左指针推进
		else
			s.pop(tt);							//或从栈顶得到新指针
	}
	cout << endl;
	return;
}
/*中序遍历-非递归*/
void cintra(tnode* t)
{
	ord_stack s;
	s.initial();
	tnode* tt = t;
	while (tt != NULL || s.top != s.base)
	{
		if (tt != NULL)
		{
			s.push(tt);
			tt = tt->left;			//寻找没有左指针的结点
		}
		else
		{
			s.pop(tt);
			cout << tt->data << "  ";
			tt = tt->right;
		}
	}
	cout << endl;
	return;
}
/*后序遍历-非递归*/
void cpotra(tnode* t)
{
	tnode* p = t, *q = NULL;
	ord_stack s;
	s.initial();
	s.push(p);
	while (s.top != s.base)								//目的是找到左子树的最左边的叶子结点，开始输出
	{																	//右子树的最左边叶子结点
		if (p!=NULL&&p != q)							//根结点存在且没遍历过入栈
		{
			s.push(p);
			p = p->left;
		}
		else
		{
			s.pop(p);												//根结点不存在或已遍历过，则出栈一个
			if (s.base != s.top)
			{
				if (p->right != NULL&&p->right != q)				//右孩子存在且没遍历过，入栈
				{
					s.push(p);
					p = p->right;						//向右前进
				}
				else
				{
					cout << p->data << "  ";				//右孩子不存在，输出
					q = p;
				}
			}
		}
	}
	cout << endl;
	return;
}
/*求叶子结点数*/
int leaf(tnode* t)
{
	if (t == NULL)			
		return 0;
	else if (t->left == NULL&&t->right == NULL)
		return 1;
	else
		return leaf(t->left) + leaf(t->right);	//返回左指针的叶子结点数+右指针叶子结点数

}


/*线索二叉树相关操作-无头结点*/

/*九种线索化：（先序，中序，后序）*（全，前驱，后继）*/
/*中序全线索化*/
void inthread_all(tnode* p,tnode* pre=NULL)
{
	if(p!=NULL)
	{
		inthread_all(p->left,pre);				//对左子树进行全线索化
		/*对当前结点的操作开始*/
		if(p->left==NULL)		//第一个if
		{                       //对左指针的操作
			p->ltag=thread;		//如果没有左子树，标记置为线索
			p->left=pre;		//指针指向前驱
		}
		if(p->right==NULL)					//第2、3个if，对右指针操作
			p->rtag=thread;					//如果没有右子树，标记置为线索
		if(pre!=NULL&&pre->rtag==thread)	//如果当前结点可以被作为后继，即上一个结点存在而且右指针将指向后继
			pre->right=p;					//上一个元素的后继指针指向当前结点
		pre=p;						//当前结点的操作即将结束，成为“上一个结点”
		/*当前结点的操作结束*/
		inthread_all(p->right,pre);				//对右子树进行全线索化
	}
	return;
}
/*中序前驱线索化*/
void inthread_pre(tnode* p,tnode* pre=NULL)
{
	if(p!=NULL)
	{
		inthread_pre(p->left,pre);;				//对左子树进行前驱线索化
		if(p->left==NULL)
		{
			p->ltag=thread;						//只操作左指针
			p->left=pre;
		}
		pre=p;
		inthread_pre(p->right,pre);				//对右子树前驱线索化
	}
	return;
}
/*中序后继线索化*/
void inthread_suc(tnode* p,tnode* pre=NULL)
{
	if(p!=NULL)
	{
		inthread_suc(p->left,pre);				//对左子树进行后继线索化
		if(p->right==NULL)					
			p->rtag=thread;					    //只操作右子树
		if(pre!=NULL&&pre->rtag==thread)	
			pre->right=p;					
		pre=p;						
		inthread_suc(p->right,pre);				//对右子树进行后继线索化
	}
	return;
}
/*先序全线索化*/
void prthread_all(tnode* p,tnode* pre=NULL)
{
	if(p!=NULL)
	{
		/*对当前结点的操作开始*/
		if(p->left==NULL)		//第一个if
		{                       //对左指针的操作
			p->ltag=thread;		//如果没有左子树，标记置为线索
			p->left=pre;		//指针指向前驱
		}
		if(p->right==NULL)					//第2、3个if，对右指针操作
			p->rtag=thread;					//如果没有右子树，标记置为线索
		if(pre!=NULL&&pre->rtag==thread)	//如果当前结点可以被作为后继，即上一个结点存在而且右指针将指向后继
			pre->right=p;					//上一个元素的后继指针指向当前结点
		pre=p;						//当前结点的操作即将结束，成为“上一个结点”
		/*当前结点的操作结束*/
		prthread_all(p->left,pre);				//对左子树进行全线索化
		prthread_all(p->right,pre);				//对右子树进行全线索化
	}
	return;
}
/*先序前驱线索化*/
void prthread_pre(tnode* p,tnode* pre=NULL)
{
	if(p!=NULL)
	{
		if(p->left==NULL)
		{
			p->ltag=thread;						//只操作左指针
			p->left=pre;
		}
		pre=p;
		prthread_pre(p->left,pre);;				//对左子树前驱线索化
		prthread_pre(p->right,pre);				//对右子树前驱线索化
	}
	return;
}
/*先序后继线索化*/
void prthread_suc(tnode* p,tnode* pre=NULL)
{
	if(p!=NULL)
	{
		if(p->right==NULL)					
			p->rtag=thread;					    //只操作右子树
		if(pre!=NULL&&pre->rtag==thread)	
			pre->right=p;					
		pre=p;
		prthread_suc(p->left,pre);				//对左子树进行后继线索化						
		prthread_suc(p->right,pre);				//对右子树进行后继线索化
	}
	return;
}
/*后序全线索化*/
void pothread_all(tnode* p,tnode* pre=NULL)
{
	if(p!=NULL)
	{
		pothread_all(p->left,pre);				//对左子树进行全线索化
		pothread_all(p->right,pre);				//对右子树进行全线索化
		/*对当前结点的操作开始*/
		if(p->left==NULL)		//第一个if
		{                       //对左指针的操作
			p->ltag=thread;		//如果没有左子树，标记置为线索
			p->left=pre;		//指针指向前驱
		}
		if(p->right==NULL)					//第2、3个if，对右指针操作
			p->rtag=thread;					//如果没有右子树，标记置为线索
		if(pre!=NULL&&pre->rtag==thread)	//如果当前结点可以被作为后继，即上一个结点存在而且右指针将指向后继
			pre->right=p;					//上一个元素的后继指针指向当前结点
		pre=p;						//当前结点的操作即将结束，成为“上一个结点”
		/*当前结点的操作结束*/
	}
	return;
}
/*后序前驱线索化*/
void pothread_pre(tnode* p,tnode* pre=NULL)
{
	if(p!=NULL)
	{
		pothread_pre(p->left,pre);;				//对左子树前驱线索化
		pothread_pre(p->right,pre);				//对右子树前驱线索化
		if(p->left==NULL)
		{
			p->ltag=thread;						//只操作左指针
			p->left=pre;
		}
		pre=p;
	}
	return;
}
/*后序后继线索化*/
void pothread_suc(tnode* p,tnode* pre=NULL)
{
	if(p!=NULL)
	{
		pothread_suc(p->left,pre);				//对左子树进行后继线索化						
		pothread_suc(p->right,pre);				//对右子树进行后继线索化
		if(p->right==NULL)					
			p->rtag=thread;					    //只操作右子树
		if(pre!=NULL&&pre->rtag==thread)	
			pre->right=p;					
		pre=p;
	}
	return;
}

/*三种线索遍历：先序，中序后序*/
/*中序线索遍历*/
void intra_thr(tnode* t)
{

}
/*先序线索遍历*/
void prtra_thr(tnode* t)
{

}
/*后序线索遍历*/
void potra_thr(tnode* t)
{

}


int main()
{
	tnode* root = NULL, *root_ = NULL;

	cout << "*****二叉树*****" << endl;
	getchar();

	cout << "====================" << endl;
	cout << "建立二叉树" << endl;
	getchar();
	cout << "按先序方式输入二叉树，#表示NULL" << endl;
	creat(root);
	cout << "已建立" << endl;
	display(root, spacenum);
	cout << endl;
	getchar();

	cout << "====================" << endl;
	cout << "先序遍历-递归" << endl;
	getchar();
	prtra(root);
	cout << endl;
	cout << "已遍历" << endl;
	display(root, spacenum);
	cout << endl;
	getchar();

	cout << "====================" << endl;
	cout << "先序遍历-非递归" << endl;
	getchar();
	cprtra(root);
	cout << endl;
	cout << "已遍历" << endl;
	display(root, spacenum);
	cout << endl;
	getchar();

	cout << "====================" << endl;
	cout << "中序遍历-递归" << endl;
	getchar();
	intra(root);
	cout << endl;
	cout << "已遍历" << endl;
	display(root, spacenum);
	cout << endl;
	getchar();

	cout << "====================" << endl;
	cout << "中序遍历-非递归" << endl;
	getchar();
	cintra(root);
	cout << endl;
	cout << "已遍历" << endl;
	display(root, spacenum);
	cout << endl;
	getchar();

	cout << "====================" << endl;
	cout << "后序遍历-递归" << endl;
	getchar();
	potra(root);
	cout << endl;
	cout << "已遍历" << endl;
	display(root, spacenum);
	cout << endl;
	getchar();

	cout << "====================" << endl;
	cout << "后序遍历-非递归" << endl;
	getchar();
	cpotra(root);
	cout << endl;
	cout << "已遍历" << endl;
	display(root, spacenum);
	cout << endl;
	getchar();

	cout << "====================" << endl;
	cout << "层次遍历" << endl;
	getchar();
	lvtra(root);
	cout << endl;
	cout << "已遍历" << endl;
	display(root, spacenum);
	cout << endl;
	getchar();

	cout << "====================" << endl;
	cout << "求深度" << endl;
	getchar();
	cout << "depth=" << depth(root) << endl;
	cout << "已求出" << endl;
	display(root, spacenum);
	cout << endl;
	getchar();

	cout << "====================" << endl;
	cout << "求结点数" << endl;
	getchar();
	cout << "size=" << size(root) << endl;
	cout << "已求出" << endl;
	display(root, spacenum);
	cout << endl;
	getchar();

	cout << "====================" << endl;
	cout << "求叶子结点数" << endl;
	getchar();
	cout << "leaf=" << leaf(root) << endl;
	cout << "已求出" << endl;
	display(root, spacenum);
	cout << endl;
	getchar();

	cout << "====================" << endl;
	cout << "复制" << endl;
	getchar();
	copy(root, root_);
	cout << "已复制" << endl;
	display(root, spacenum);
	cout << endl << endl;
	display(root_, spacenum);
	cout << endl;
	getchar();

	cout << "====================" << endl;
	cout << "交换左右子树" << endl;
	getchar();
	exchange(root);
	cout << "已交换" << endl;
	display(root, spacenum);
	cout << endl;
	getchar();

	cout << "====================" << endl;
	cout << "销毁" << endl;
	getchar();
	destroy(root);
	destroy(root_);
	cout << "已销毁" << endl;
	cout << endl;
	getchar();

	return 0;
}