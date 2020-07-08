#include<iostream>
using namespace std;

typedef char atype;
const atype sepa='*';
const int spacenum=3;

struct tnode
{
	atype data;
	tnode* left;
	tnode* right;
};

void cprtra(tnode*);
void cintra(tnode*);
void cpotra(tnode*);
void lvtra(tnode*);
void leaf(tnode*);

void creat(tnode* t)
{
	atype m;
	cin>>m;
	if(m==sepa)
		t=NULL;
	else
	{
		t=new tnode;
		t->data=m;
		creat(t->left);
		creat(t->right);
	}
	return;
}
void destroy(tnode* t)
{
	if(t!=NULL)
	{
		destroy(t->left);
		destroy(t->right);
		delete t;
	}
	return;
}
void prtra(tnode* t)
{
	if(t!=NULL)
	{
		cout<<t->data<<"  ";
		prtra(t->left);
		prtra(t->right);
	}
	return;
}
void intra(tnode* t)
{
	if(t!=NULL)
	{
		intra(t->left);
		cout<<t->data<<"  ";
		intra(t->right);
	}
	return;
}
void potra(tnode* t)
{
	if(t!=NULL)
	{
		potra(t->left);
		potra(t->right);
		cout<<t->data<<"  ";
	}
	return;
}
void display(tnode* t,int n)
{
	if(t!=NULL)
	{
		display(t->left,n+1);
		for(int i=1;i<=n;i++)
			cout<<' ';
		cout<<t->data;
		display(t->right,n+1);
	}
	return;
}
int depth(tnode* t)
{
	int dl,dr;
	if(t!=NULL)
	{
		dl=depth(t->left);
		dr=depth(t->right);
		return (dl>dr?dl+1:dr+1);
	}
	return 0;
}
int size(tnode* t)
{
	if(t==NULL)
		return 0;
	return (size(t->left)+size(t->right)+1);
}
void exchange(tnode* t)
{
	tnode *p;
	if(t!=NULL)
	{
		t->left=p;
		t->left=t->right;
		t->right=p;
		exchange(t->left);
		exchange(t->right);
	}
	return;
}
void copy(tnode* t,tnode* tt)
{
	if(t!=NULL)
	{
		tt=new tnode;
		tt->data=t->data;
		tt->left=NULL;
		tt->right=NULL;
		copy(t->left,tt->left);
		copy(t->right,tt->right);
	}
	return;
}

int main()
{
	tnode* root=NULL,*root_=NULL;

	cout<<"*****二叉树*****"<<endl;
	getchar();

	cout<<"===================="<<endl;
	cout<<"建立二叉树"<<endl;
	getchar();
	cout<<"按先序方式输入二叉树，空格表示NULL"<<endl;
	creat(root);
	cout<<"已建立"<<endl;
	display(root,spacenum);
	cout<<endl;
	getchar();

	cout<<"===================="<<endl;
	cout<<"先序遍历"<<endl;
	getchar();
	prtra(root);
	cout<<endl;
	cout<<"已遍历"<<endl;
	display(root,spacenum);
	cout<<endl;
	getchar();

	cout<<"===================="<<endl;
	cout<<"中序遍历"<<endl;
	getchar();
	intra(root);
	cout<<endl;
	cout<<"已遍历"<<endl;
	display(root,spacenum);
	cout<<endl;
	getchar();

	cout<<"===================="<<endl;
	cout<<"后序遍历"<<endl;
	getchar();
	potra(root);
	cout<<endl;
	cout<<"已遍历"<<endl;
	display(root,spacenum);
	cout<<endl;
	getchar();

	cout<<"===================="<<endl;
	cout<<"求深度"<<endl;
	getchar();
	cout<<"depth="<<depth(root)<<endl;
	cout<<"已求出"<<endl;
	display(root,spacenum);
	cout<<endl;
	getchar();

	cout<<"===================="<<endl;
	cout<<"求结点数"<<endl;
	getchar();
	cout<<"size="<<size(root)<<endl;
	cout<<"已求出"<<endl;
	display(root,spacenum);
	cout<<endl;
	getchar();

	cout<<"===================="<<endl;
	cout<<"复制"<<endl;
	getchar();
	copy(root,root_);
	cout<<"已复制"<<endl;
	display(root,spacenum);
	cout<<endl;
	display(root_,spacenum);
	cout<<endl;
	getchar();

	cout<<"===================="<<endl;
	cout<<"交换左右子树"<<endl;
	getchar();
	exchange(root);
	cout<<"已交换"<<endl;
	display(root,spacenum);
	cout<<endl;
	getchar();

	cout<<"===================="<<endl;
	cout<<"销毁"<<endl;
	getchar();
	destroy(root);
	destroy(root_);
	cout<<"已销毁"<<endl;
	cout<<endl;

	return 0;
}