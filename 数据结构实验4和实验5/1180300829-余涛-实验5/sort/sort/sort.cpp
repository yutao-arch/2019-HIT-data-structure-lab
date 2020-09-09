#include<stdio.h>
#include<stdlib.h>

#define max 101

struct records
{
	int key;
};

records a[max];

void createtest(records a[])
{
	int i, j, temp,k;
	for (i = 1; i < 101; i++)
	{
		a[i].key = i;
		//printf("%d %d   ", k, test[k]);
	}
	for (k = 1; k < 10000; k++)
	{
		i = rand() % max;
		j = rand() % max;
		if (i != 0 && j != 0)
		{
			temp = a[i].key;
			a[i].key = a[j].key;
			a[j].key = temp;
		}
	}
}
//产生待排序数组a

void swap(records &a, records &b)
{
	records temp;
	temp = a;
	a = b;
	b = temp;
}
//交换两个数

void bubblesort(int n)
{
	int sp = 0;
	for (int i = 1; i <= n-1; i++)
	{
		sp = 0;  //每趟排序标志位都置0
		for (int j = n; j >= i+1 ; j--)
		{
			if (a[j].key < a[j - 1].key)
			{
				swap(a[j], a[j - 1]);
				sp = 1;   //只要有发生交换，标志位为1；  
			}
		}
		if (sp == 0)  //如果标志位为0，就说明所有元素已经有序，直接返回
		{
			return;
		}
	}
}
//冒泡排序

int findpivot(int i, int j)  //返回a[i],a[j]总较大关键字的下标，若全相同则返回0
{
	int firstkey = a[i].key;
	int k;
	for (k = i + 1; k <= j; k++)  //从左到右查找不同的关键字
	{
		if (a[k].key > firstkey)
		{
			return k;     
		}
		else if (a[k].key < firstkey)
		{
			return i;
		}
	}
	return 0;
}
//找到数组a基准元素下标

int partition(int i, int j, int pivot)
{
	int l, r;
	do 
	{
		for (l = i; a[l].key < pivot; l++);
		for (r = j; a[r].key >= pivot; r--);
		if (l < r)
		{
			swap(a[l], a[r]);
		}
	} while (l <= r);
	return l;
}
//根据关键字划分两个序列

void quicksort(int i, int j)
{
	int pivot;
	int k;   //关键字大于等于pivot的记录在序列中的起始下标
	int pivotindex;  //关键字为pivot的记录在数组A中的下标
	pivotindex = findpivot(i, j);
	if (pivotindex != 0)
	{
		pivot = a[pivotindex].key;
		k = partition(i, j, pivot);
		quicksort(i, k - 1);
		quicksort(k, j);
	}
}
//对数组a的元素a[i]......a[j]进行快速排序

void selectsort(int n)
{
	int lowkey;    //当前最小关键字
	int i, j, lowindex;  //当前最小关键字的下标
	for (i = 1; i < n; i++)  //在A[i…n]中选择最小的关键字，与A[i]交换
	{
		lowindex = i;
		lowkey = a[i].key;
		for (j = i + 1; j <= n; j++)
		{
			if (a[j].key < lowkey)  //用当前最小关键字与每个关键字比较
			{
				lowkey = a[j].key;
				lowindex = j;
			}
		}
		swap(a[i], a[lowindex]);
	}
}
//直接选择排序

void pushdown(int first, int last)
{
	int r;
	r = first; //r是被下推到的适当位置，初始值为根first
	while (r <= last / 2)
	{
		if ((r == last / 2) && (last % 2 == 0)) //r有一个儿子在2*r上且为左儿子
		{
			if (a[r].key < a[2 * r].key)  //如果儿子比自己大就交换
			{
				swap(a[r], a[2 * r]);
			}
			r = last;  //结束循环
		}
		else if ((a[r].key < a[2 * r].key) && (a[2 * r].key >= a[2 * r + 1].key))
		{
			swap(a[r], a[2 * r]);   //左孩子比右孩子大，与左孩子交换
			r = 2 * r;
		}
		else if ((a[r].key < a[2 * r + 1].key) && (a[2 * r + 1].key > a[2 * r].key))
		{
			swap(a[r], a[2 * r + 1]);  //右孩子比左孩子大，与右孩子交换
			r = 2 * r + 1;
		}
		else
			r = last;
	}
}
//按照最大堆整理堆

void heapsort(int n)
{
	int i;
	for (i = n / 2; i >= 1; i--)  //初始建堆，从最右非叶结点开始
	{
		pushdown(i, n);     //整理堆，把以i为根，最大下标的叶为n
	}
	for (i = n; i >= 2; i--)
	{
		swap(a[1], a[i]);  //堆顶与当前堆中的下标最大的叶结点交换
		pushdown(1, i - 1); //整理堆把以1为根，最大叶下标为i - 1的完全二元树整理成堆
	}
}
//堆排序

void insertsort(int n)
{
	int i, j;
	a[0].key = -INT_MAX;
	for (i = 1; i <= n; i++)
	{
		j = i;
		while (a[j].key < a[j - 1].key)
		{
			swap(a[j], a[j - 1]);
			j = j - 1;
		}
	}
}
//插入排序

void shellsort(int n)
{
	int i, j, d;
	for (d = n / 2; d >= 1; d = d / 2)
	{
		for (i = d + 1; i <= n; i++)  //将A[i]插入到所属的子序列中
		{
			a[0].key = a[i].key;    //暂存待插入记录
			j = i - d;              //j指向所属子序列的最后一个记录
			while (j > 0 && a[0].key < a[j].key)
			{
				a[j + d] = a[j];   //记录后移d个位置
				j = j - d;         //比较同一子序列的前一个记录
			} 
			a[j + d] = a[0];
		}
	}
}
//希尔排序

void print()
{
	for (int i = 1; i <= max-1; i++)
	{
		printf("%d ",a[i].key);
	}
}
//打印排序数组

void merge(int s, int m, int t, records a[], records b[])
{
	int i = s, j = m + 1, k = s;  //置初值
	while (i <= m && j <= t)  //两个序列非空时，取小者输出到b[k]上
		b[k++] = (a[i].key <= a[j].key) ? a[i++] : a[j++];
	while (i <= m)    //若第一个子序列非空(未处理完)，则复制剩余部分到b
		b[k++] = a[i++];
	while (j <= t)    // 若第二个子序列非空(未处理完)，则复制剩余部分到b
		b[k++] = a[j++];
}
//将有序序列A[s],…,A[m]和A[m+1],…,A[t]合并为一个有序序列B[s],…,B[t]

void mergepass(int n, int h, records a[], records b[])
{
	int i, t;
	for (i = 1; i + 2 * h - 1 <= n; i += 2 * h)
	{
		merge(i, i + h - 1, i + 2 * h - 1, a, b);  //归并长度为h的两个有序子序列
	}
	if (i + h - 1 < n)  //尚有两个子序列，其中最后一个长度小于h
	{
		merge(i, i + h - 1, n, a, b);  //归并最后两个子序列
	}
	else  //若i<= n且i+h-1>= n 时，则剩余一个子序列轮空，直接复制
	{
		for (t = i; t <= n; t++)
		{
			b[t] = a[t];
		}
	}
}
//把a长度为h的相邻序列归并成长度为2h的序列

void mergesort(int n)
{
	int h = 1; //当前归并子序列的长度，初始为1
	records b[max];
	while (h < n)
	{
		mergepass(n, h, a, b);
		h = 2 * h;
		mergepass(n, h, b, a); //a、b互换位置
		h = 2 * h;
	}
}
//二路归并排序

void menu()
{
	printf("-----------------\n");
	printf("1.冒泡排序\n");
	printf("2.快速排序\n");
	printf("3.选择排序\n");
	printf("4.堆排序\n");
	printf("5.插入排序\n");
	printf("6.希尔排序\n");
	printf("7.二路归并排序\n");
	printf("-----------------\n");
}
//菜单

int main()
{
	int m;
	menu();
	while (1)
	{
		printf("请输入你的操作：");
		scanf(" %d", &m);
		switch (m)
		{
		case 1:
			printf("待排序数列为：\n");
			createtest(a);
			print();
			printf("\n");
			printf("冒泡排序后的数列为：\n");
			bubblesort(max - 1);
			print();
			printf("\n\n");
			break;
		case 2:
			printf("待排序数列为：\n");
			createtest(a);
			print();
			printf("\n");
			printf("快速排序后的数列为：\n");
			quicksort(1, max - 1);
			print();
			printf("\n\n");
			break;
		case 3:
			printf("待排序数列为：\n");
			createtest(a);
			print();
			printf("\n");
			printf("选择排序后的数列为：\n");
			selectsort(max - 1);
			print();
			printf("\n\n");
			break;
		case 4:
			printf("待排序数列为：\n");
			createtest(a);
			print();
			printf("\n");
			printf("堆排序后的数列为：\n");
			heapsort(max - 1);
			print();
			printf("\n\n");
			break;
		case 5:
			printf("待排序数列为：\n");
			createtest(a);
			print();
			printf("\n");
			printf("插入排序后的数列为：\n");
			insertsort(max-1);
			print();
			printf("\n\n");
			break;
		case 6:
			printf("待排序数列为：\n");
			createtest(a);
			print();
			printf("\n");
			printf("希尔排序后的数列为：\n");
			shellsort(max - 1);
			print();
			printf("\n\n");
			break;
		case 7:
			printf("待排序数列为：\n");
			createtest(a);
			print();
			printf("\n");
			printf("二路归并排序后的数列为：\n");
			mergesort(max-1);
			print();
			printf("\n\n");
			break;
		default:
			printf("请输入正确操作：\n\n");
			break;
		}
	}
	return 0;
}