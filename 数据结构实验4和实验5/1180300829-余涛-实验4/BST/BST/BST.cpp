#include<stdio.h>
#include<stdlib.h>

typedef struct celltype
{
	int data;
	struct celltype* lchild, * rchild;
}bstnode;        
//二叉查找树的节点
typedef bstnode* BST;

int test1[1025];  //测试数组1
int test2[1025];  //测试数组2

void insertbst(int r, BST &f)
{
	if (f == NULL)
	{
		f = (bstnode*)malloc(sizeof(bstnode));
		if (f == NULL)
			printf("申请内存失败\n");
		f->data = r;
		f->lchild = NULL;
		f->rchild = NULL;
	}
	else if (r < f->data)
	{
		insertbst(r, f->lchild);
	}
	else if (r > f->data)
	{
		insertbst(r, f->rchild);
	}
}
//递归二叉树插入

BST createbt1(void)
{
	BST f;
	f = (bstnode*)malloc(sizeof(bstnode));
	f= NULL;  //初始化f为空
	int key,k=1;
	while (k<1025) 
	{
		insertbst(test1[k], f);
		k++;
	}
	return f;  //返回建立的二叉查找树的根
}
//对test1二叉查找树的建立

BST createbt2(void)
{
	BST f;
	f = (bstnode*)malloc(sizeof(bstnode));
	f = NULL;  //初始化f为空
	int key, k = 1;
	while (k < 1025)
	{
		insertbst(test2[k], f);
		k++;
	}
	return f;  //返回建立的二叉查找树的根
}
//对test2二叉查找树的建立

int deletemin(BST &f)
{
	int tmp;
	BST p;
	p=(bstnode*)malloc(sizeof(bstnode));
	if (f->lchild == NULL)
	{
		p = f;
		tmp = f->data;
		f = f->rchild;  //右链继承
		free(p);
		return tmp;
	}
	else
	{
		return (deletemin(f->lchild));
	}
}
//删除关键词最小的节点，并返回里面的数据

void deleteb(int k, BST &f)
{
	if (f != NULL)
	{
		if (k < f->data)
		{
			deleteb(k, f->lchild);
		}
		else if (k > f->data)
		{
			deleteb(k, f->rchild);
		}
		else   //找到了需要删除的数据
		{
			if (f->rchild == NULL)  //右子树为空直接继承左子树
			{
				f = f->lchild;
			}
			else if (f->lchild == NULL)  //左子树为空直接继承右子树
			{
				f = f->rchild;
			}
			else
				f->data = deletemin(f->rchild);   //左右子树都为空相当于删除右子树里面的最小关键字节点并把它的值复制到待删除的节点
		}
	}
}
//删除某个节点

BST searchbst(int k, BST f)
{
	BST p;
	p = (bstnode*)malloc(sizeof(bstnode));
	p= f;
	if (p == NULL|| k == p->data)
	{
		return p;
	}
	if (k < p->data)
	{
		return (searchbst(k, p->lchild));
	}
	else
		return (searchbst(k, p->rchild));
}
//二叉查找

void paixu(bstnode* f)
{
	if (f != NULL)
	{
		paixu(f->lchild);
		printf("%d ", f->data);
		paixu(f->rchild);
	}
}
//进行中序遍历输出

int binsearch(int f[], int low, int up, int k)
{
	int mid;
	if (low > up)
		return 0;
	else
	{
		mid = (low + up) / 2;
		if (k < f[mid])
		{
			return binsearch(f, low, mid - 1, k);
		}
		else if (k > f[mid])
		{
			return binsearch(f, mid + 1, up, k);
		}
		else
			return mid;
	}
}
//折半查找的递归算法

int count;

int asl_2(int f[], int low, int up, int k)
{
	int mid;
	if (low>up)
		return count;
	else
	{
		mid = (low + up) / 2;
		if (k < f[mid])
		{
			count++;
			return asl_2(f, low, mid - 1, k);
		}
		else if (k > f[mid])
		{
			count++;
			return asl_2(f, mid + 1, up, k);
		}
		else if (k == f[mid])
		{
			count++;
			return count;
		}
	}
}
//折半查找的查找长度

void createtest1()
{
	int k=1;
	for (int i = 1; i < 2049; i++)
	{
		if (i % 2 == 1)
		{
			test1[k] = i;
			k++;
		}
	}
}
//产生测试数组1

void createtest2()
{
	int i,j,temp,k=1;
	for (i = 1; i < 2049; i++)
	{
		if (i % 2 == 1)
		{
			test2[k] = i;
			k++;
		}
	}
	for (k = 1; k < 10000;k++)
	{
		i= rand() % 1025;
		j = rand() % 1025;
		temp = test2[i];
		test2[i] = test2[j];
		test2[j] = temp;
	}
}
//产生测试数组2

int asl(int k, BST f)
{
	BST p;
	p = (bstnode*)malloc(sizeof(bstnode));
	p = f;
	if (p == NULL)
	{
		return count;
	}
	if (k == p->data)
	{
		count++;
		return count;
	}
	if (k < p->data)
	{
		count++;
		return asl(k, p->lchild);
	}
	else
	{
		count++;
		return asl(k, p->rchild);
	}
}
//对一个数data进行查找次数的计算

void menu()
{
	printf("---------------------------\n");
	printf("1.数据一BST的建立\n");
	printf("2.数据一BST的查找长度\n");
	printf("3.数据一BST的排序\n");
	printf("4.数据一BST的插入\n");
	printf("5.数据一BST的查找\n");
	printf("6.数据一BST的删除\n");
	printf("7.数据二BST的建立\n");
	printf("8.数据二BST的查找长度\n");
	printf("9.数据二BST的排序\n");
	printf("10.数据二BST的插入\n");
	printf("11.数据二BST的查找\n");
	printf("12.数据二BST的删除\n");
	printf("13.折半查找\n");
	printf("14.折半查找的查找长度\n");
	printf("---------------------------\n");
}
//菜单

int main()
{
	BST f1, f2,mm;
	int m, n, p, counter1 = 0, counter2 = 0;
	f1 = (bstnode*)malloc(sizeof(bstnode));
	f2 = (bstnode*)malloc(sizeof(bstnode));
	mm= (bstnode*)malloc(sizeof(bstnode));
	int a,pp;
	menu();
	while (1)
	{
		printf("请输入你的操作：");
		scanf(" %d", &a);
		switch (a)
		{
		case 1:
			createtest1();
			f1 = createbt1();
			printf("已成功建立数据一的BST\n");
			printf("\n");
			break;
		case 2:
			counter1 = 0;
			counter2 = 0;
			createtest1();
			f1 = createbt1();
			for (p = 1; p < 1025; p++)
			{
				count = 0;
				counter1 += asl(test1[p], f1);
			}
			printf("数据一asl成功查找长度%f\n",((float)counter1 / 1024));
			for (p = 0; p <= 2048; p += 2)
			{
				count = 0;
				counter2 += asl(p, f1);
			}
			printf("数据一asl失败查找长度%f\n",((float)counter2 / 1025));
			printf("\n");
			break;
		case 3:
			createtest1();
			f1 = createbt1();
			paixu(f1);
			printf("\n");
			break;
		case 4:
			printf("请输入你要插入的数：\n");
			scanf(" %d", &m);
			insertbst(m, f1);
			paixu(f1);
			printf("\n");
			break;
		case 5:
			printf("请输入你要查找的数：\n");
			scanf(" %d", &n);
			mm=searchbst(n, f1);
			if (mm != NULL)
				printf("查找成功\n");
			else
				printf("查找失败\n");
			printf("\n");
			break;
		case 6:
			printf("请输入你要删除的数：\n");
			scanf(" %d", &n);
			deleteb(n, f1);
			paixu(f1);
			printf("\n");
			break;
		case 7:
			createtest2();
			f2 = createbt2();
			printf("已成功建立数据二的BST\n");
			printf("\n");
			break;
		case 8:
			counter1 = 0;
			counter2 = 0;
			createtest2();
			f2 = createbt2();
			for (p = 1; p < 1025; p++)
			{
				count = 0;
				counter1 += asl(test2[p], f2);
			}
			printf("数据二asl成功查找长度%f\n", ((float)counter1 / 1024));
			for (p = 0; p <= 2048; p += 2)
			{
				count = 0;
				counter2 += asl(p, f2);
			}
			printf("数据二asl失败查找长度%f\n", ((float)counter2 / 1025));
			printf("\n");
			break;
		case 9:
			createtest2();
			f2 = createbt2();
			paixu(f1);
			printf("\n");
			break;
		case 10:
			printf("请输入你要插入的数：\n");
			scanf(" %d", &m);
			insertbst(m, f2);
			paixu(f2);
			printf("\n");
			break;
		case 11:
			printf("请输入你要查找的数：\n");
			scanf(" %d", &n);
			mm = searchbst(n, f2);
			if (mm != NULL)
				printf("查找成功\n");
			else
				printf("查找失败\n");
			printf("\n");
			break;
		case 12:
			printf("请输入你要删除的数：\n");
			scanf(" %d", &n);
			deleteb(n, f2);
			paixu(f2);
			printf("\n");
			break;
		case 13:
			printf("请输入需要折半查找的数：\n");
			scanf(" %d", &n);
			createtest1();
			pp=binsearch(test1, 1, 1024,n);
			if (pp >= 1 && pp <= 1024)
				printf("对应元素下表为%d\n", pp);
			else
				printf("查找失败\n");
			printf("\n");
			break;
		case 14:
			counter1 = 0;
			counter2 = 0;
			createtest1();
			for (p = 1; p < 1025; p++)
			{
				count = 0;
				counter1 += asl_2(test1, 1, 1024, test1[p]);
			}
			printf("折半asl成功查找长度%f\n", ((float)counter1 / 1024));
			for (p = 0; p <= 2048; p += 2)
			{
				count = 0;
				counter2 += asl_2(test1, 1, 1024, p);
			}
			printf("折半asl失败查找长度%f\n", ((float)counter2 / 1025));
			printf("\n");
			break;
		default:
			printf("请输入正确序号！\n");
			break;
		}
	}
}