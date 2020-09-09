#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct GOODS
{
	char name[15];   //名称
	char brand[15];  //品牌
	double price;    //单价
	int amount;      //数量
	struct GOODS* next;
}goods;
//创造一个新的节点,为其赋值并且返回指向这个节点的指针
goods* Create_newnode()
{
	goods* p;
	p = (goods*)malloc(sizeof(goods));
	if (p == NULL)         //判断动态内存是否申请成功
	{
		printf("没有足够的内存可供分配");
	}
	p->next = NULL;
	strcpy(p->name, " ");
	strcpy(p->brand, " ");
	p->price = 1;
	p->amount = 0;
	return p;
}
//营业开始，从information.txt中读入家电信息
void Read_file(goods* head)
{
	FILE* fp;
	goods* p = head;
	goods* q;
	q = Create_newnode();
	char name[15], brand[15];
	int price = 0, amount = 0;
	fp = fopen("information.txt", "r");    //用只读方式打开文件information.txt
	if (fp == NULL)
	{
		printf("读入家电信息失败 \n");
		exit(0);
	}
	fseek(fp, 22, 0);
	while (fscanf(fp, "%s", q->name) != EOF)    //在未达到文件末尾前，依次从文件中读入节点的数据
	{
		fscanf(fp, "%s", q->brand);
		fscanf(fp, "%lf", &q->price);
		fscanf(fp, "%d\n", &q->amount);
		p->next = q;
		p = q;
		q = Create_newnode();
	}
	p->next = NULL;
	fclose(fp);
}
//进货，插入某种商品的数据，但同时得考虑是否进的是已有商品
void Insert_data(goods* head)
{
	goods* p = head;
	goods* s = head;
	goods* q;
	p=Create_newnode();
	printf("请分别输入进货家电的名称，品牌，单价，数量： \n");
	scanf("%s %s %lf %d", p->name, p->brand, &p->price, &p->amount);
	if (head->next == NULL)  //判断head是否为尾结点,若是，将它指向新建节点p
	{
		head->next = p;
	}
	else
	{
		while ((p->price)>(s->next->price)) //由于链表是单价升序排序，所以插入位置通过价格的比较即可确定为s->next之前
		{
			s = s->next;
			if (s->next == NULL)
			{
				break;
			}
		}
		if (s->next != NULL)          //若s不是尾结点
		{
			if (strcmp(p->name, s->next->name) == 0 && strcmp(p->brand, s->next->brand) == 0) //判断进货家电是否为已有商品，若是，则数量加一即可
			{
				s->next->amount += p->amount;
			}
			else        //在s->next之前插入新节点p
			{
				q = s->next;
				s->next = p;
				p->next = q;
			}
		}
		else    //若s为尾结点，则直接在节点后面插入新节点
		{
			s->next = p;
			p->next = NULL;
		}
	}
}
//无输入进货，为后面更新服务 
void Insert_data_noinput(goods* head,goods* p)
{
	goods* s = head;
	goods* q;
    if (head->next == NULL)  //判断head是否为尾结点,若是，将它指向新建节点p
	{
		head->next = p;
	}
	else
	{
		while ((p->price)>(s->next->price)) //由于链表是单价升序排序，所以插入位置通过价格的比较即可确定为s->next之前
		{
			s = s->next;
			if (s->next == NULL)
			{
				break;
			}
		}
		if (s->next != NULL)          //若s不是尾结点
		{
			if (strcmp(p->name, s->next->name) == 0 && strcmp(p->brand, s->next->brand) == 0) //判断进货家电是否为已有商品，若是，则数量加一即可
			{
				s->next->amount += p->amount;
			}
			else        //在s->next之前插入新节点p
			{
				q = s->next;
				s->next = p;
				p->next = q;
			}
		}
		else    //若s为尾结点，则直接在节点后面插入新节点
		{
			s->next = p;
			p->next = NULL;
		}
	}
}
//提货，同时考虑存货是否足够，对三种情况进行讨论
void Delete_data(goods* head)
{
	goods* q = head;
	goods* p = head;
	goods* s, * r;
	p=Create_newnode();
	printf("请分别输入提货家电的名称，品牌，单价，数量： \n");
	scanf("%s %s %lf %d", p->name, p->brand, &p->price, &p->amount);
	if (head->next == NULL)  //如果需要查询的家电在尾节点，则说明无此商品
	{
		printf("没有此商品 \n");
	}
	else
	{
		while (strcmp(q->next->brand, p->brand) != 0 || strcmp(q->next->name, p->name) != 0) //依次从头检索是否有待取货的商品直到表尾
		{
			q = q->next;
			if (q->next == NULL)
			{
				break;
			}
		}
		if (q->next != NULL)
		{
			if (q->next->amount == p->amount)  //如果待取货的数量与库存相等
			{
				if (q->next->next == NULL)  //如果到了表尾，则删除q->next,并释放q->next
				{
					s = q->next;
					q->next = NULL;
					free(s);
				}
				else     //若没有到达表尾，则删除q->next,并释放q->next
				{
					s = q->next->next;
					r = q->next;
					q->next = s;
					free(r);
				}
			}
			else   //若待取货的数量与库存不相等
			{
				if (q->next->amount < p->amount)  //若待取货的数量大于库存
					printf("库存紧缺，无法实现操作，请重新操作\n\n");
				else     //若待取货的数量小于库存，则用库存减去待取货的数量得剩余库存
					q->next->amount -= p->amount;
			}
		}
	}
}
//查询信息，即依次查询每个节点的信息
void Watch_data(goods* head)
{
	goods* p = head->next;
	printf("名称\t品牌\t单价\t\t数量:\n");
	while (p != NULL) //只要没到到表尾
	{
		printf("%s\t%s\t%lf\t%d\n", p->name, p->brand, p->price, p->amount);
		p = p->next;
	}
	printf("\n\n");
}
//更新信息，将变动的商品信息重新赋值
void Refresh_data(goods* head)
{
	goods* p;
	goods* s;
	goods* q = head;
	goods* m;
	goods* n=head;
	p = Create_newnode();
	printf("请分别输入更新家电的名称，品牌，单价，数量： \n");
	scanf("%s %s %lf %d", p->name, p->brand, &p->price, &p->amount);
	while (strcmp(q->next->brand, p->brand) != 0 || strcmp(q->next->name, p->name) != 0)   //寻找所需家电在链表的位置，若不相等，则q为下一个节点
	{
		q = q->next;
	}
	if (q->next->next == NULL)//若q->next到了表尾,则释放原节点，并执行无输入进货 
    {
		s=q->next;
		free(s);
		q->next=NULL;
		Insert_data_noinput(n,p); 
    }
	else//若没有到达表尾，则释放原节点，改变指针指向并执行无输入进货
	{
		s=q->next;
		m=s->next;
		free(s);
		q->next=m;
		Insert_data_noinput(n,p); 
    }
}	
//营业结束，向information.txt中写入家电信息
int Save_file(goods* head)//保存数据
{
	FILE* fp;
	goods* p = head->next;
	fp = fopen("information.txt", "w");  //以只写方式打开information.txt
	if (fp == NULL)
	{
		printf("写入家电信息失败\n");
		return -1;
	}
	fprintf(fp, "名称\t 品牌\t 价格\t 数量\n");
	while (p != NULL)
	{
		fprintf(fp, "%s\t %s\t %lf\t %d\n", p->name, p->brand, p->price, p->amount);
		p = p->next;
	}
	fprintf(fp, "\n");
	fclose(fp);
	return 0;
}
//创建表
void Create_list(goods* head)
{
	Read_file(head);
	printf("营业开始，商品信息已读入，请继续选择操作: \n");
}
//操作菜单
int Menu()
{
	int m;
	printf("***********************************\n");
	printf("w e l c o m e\n");
	printf("欢迎来到商场家电信息维护系统：\n");
	printf("1.营业开始\n");
	printf("2.进货\n");
	printf("3.提货\n");
	printf("4.查询信息\n");
	printf("5.更新信息\n");
	printf("6.退出系统\n\n");
	printf("***********************************\n");
	printf("请选择你要执行的操作：\n");
	scanf("%d", &m);
	printf("\n");
	return m;
}
int main()
{
	goods* head;
	char a;
	head = Create_newnode();
	printf("***********************************\n");
	printf("注意：请先选择1号来读入商品信息\n");
	while (1)
	{
		a = Menu();
		switch (a)
		{
		case 1:
			Create_list(head);
			break;
		case 2:
			Insert_data(head);
			break;
		case 3:
			Delete_data(head);
			break;
		case 4:
			Watch_data(head);
			break;
		case 5:
			Refresh_data(head);
			break;
		case 6:
			printf("营业结束,家电信息已保存\n");
			Save_file(head);
			exit(0);
		default:printf("请输入正确序号!\n");
		}
	}
	return 0;
}
