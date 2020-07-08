#include<iostream>
using namespace std;

#define max 8;

struct huffman
{
	unsigned int weight,parent,left,right;
};

char **stdcode=NULL;

void select(huffman* tree,int n,int &s1,int &s2)
{
	huffman* p=tree;
	unsigned int w1[2],w2[2];
	w1[0]=-1;
	w2[0]=-1;
	for(int i=1;i<=n;i++,p++)
	{
		if(p->parent==0)
		{
			if(w1[0]==-1||w2[0]==-1)
			{
				if(w1[0]==-1)
				{
					w1[0]=p->weight;
					w1[1]=i;
				}
				else if(w2[0]==-1)
				{
					w2[0]=p->weight;
					w2[1]=i;
				}
			}
			else
			{
				if(p->weight<w1[0])
				{
					w1[0]=p->weight;
					w1[1]=i;
				}
				else if(p->weight<w2[0])
				{
					w2[0]=p->weight;
					w2[1]=i;
				}
			}
		}
	}
	s1=(w1[1]<w2[1]?w1[1]:w2[1]);
	s2=(w2[1]>w1[1]?w2[1]:w1[1]);
	return;
}

void encode(huffman* &tree,char** &code,int* w,int n)
{
	huffman* p;	//循环时需要的临时指针
	char* cd;
	int i,s1,s2,start;	//i为循环的计数
	unsigned int c,f;
	if (n<=1)	//n是字符数，只有一个字符不需要编码
		return;
	int m=2*n-1;	//m是节点数
	tree=new huffman[m+1];	//申请一个以结点为元素的数组，连续空间
	
	/*第一个循环，将表中前半部分的weight填完*/
	/*前半部分是有实际意义的结点*/

	for(p=tree+1,i=1;i<=n;i++,p++,w++)	//w是记录了每个元素权值的数组
	{
		p->weight=*w;	//把当前指向的权值赋给当前结点的weight元素
		p->parent=0;	//父亲暂赋为0
		p->left=0;
		p->right=0;		//有实际意义的结点必为叶子结点，孩子赋为0
	}

	/*第二个循环，将表中后半部分的数据置0*/
	/*后半部分是建立赫夫曼树时产生的新结点*/

	for(;i<=m;i++,p++)
	{
		p->weight=0;
		p->left=0;
		p->right=0;
		p->parent=0;	//全部暂赋为0
	}

	/*第三个循环，填完父子，完成赫夫曼树（tree数组）的建立*/
	
	for(i=n+1;i<=m;i++)
	{
		select(tree,i-1,s1,s2);		//寻找当前结点之前的，没有父亲的权值最小的两项，s1保存较小的数组标号，s2保存较大的数组标号
		tree[s1].parent=i;		
		tree[s2].parent=i;		//将找到的两项的父亲赋为当前结点的标号
		tree[i].left=s1;;
		tree[i].right=s2;		//将当前结点的孩子分别赋值，左小于右
		tree[i].weight=tree[s1].weight+tree[s2].weight;		//当前结点的权值为两孩子权值相加
	}

	code=new char*[n+1];	//保存所有出现的字符的标准编码
	cd=new char[n];		//申请一个临时的足够长的字符数组
	cd[n-1]='\0';		//最后赋为'\0'，当作字符串
	for(i=1;i<=n;i++)
	{
		start=n-1;		//编码从后向前赋值
		for(c=i,f=tree[c].parent;f!=0;c=f,f=tree[f].parent)
		{
			if(tree[f].left==c)
				cd[--start]='0';	//左孩子编码为0
			else
				cd[--start]='1';	//右孩子编码为1
			code[i]=new char[n-start];		//给对应字符申请适宜长度的空间保存标准编码
			strcpy(code[i],&cd[start]);		//保存编码
			cout<<code[i];		//输出
		}
	}
	delete cd;	//将临时字符数组释放
}