#include<stdio.h>
#include<stdlib.h>
#define mysize 200
typedef struct      //字符栈
{
	char data[mysize];
	int top;
	int base;
}STACK_zifu;

typedef struct      //数据栈
{
	float data[mysize];
	int top;
	int base;
}STACK_shuju;
//将字符栈置空
void Makenull_zifu(STACK_zifu* s)
{
	s->top = 0;
	s->base = 0;
}
//将数据栈置空
void Makenull_shuju(STACK_shuju* s)
{
	s->top = 0;
	s->base = 0;

}
//判断字符栈是否为空
int Empty_zifu(STACK_zifu* s)
{
	if (s->base == s->top)
		return 1;
	else
		return 0;

}
//判断数据栈是否为空
int Empty_shuju(STACK_shuju* s)
{
	if (s->base == s->top)
		return 1;
	else
		return 0;

}
//返回字符栈栈顶元素
char Top_zifu(STACK_zifu* s)
{
	if (s->top == s->base)
		return 0;
	return (s->data[s->top - 1]);

}
//返回数据栈栈顶元素
float Top_shuju(STACK_shuju* s)
{
	if (s->top == s->base)
		return 0;
	return (s->data[s->top - 1]);
}
//将字符x压入字符栈的栈顶
void Push_zifu(char x, STACK_zifu* s)
{
	s->data[s->top] = x;
	s->top++;
}
//将数据x压入字符栈的栈顶
void Push_shuju(float x, STACK_shuju* s)
{
	s->data[s->top] = x;
	s->top++;
}
//删除字符栈栈顶的元素并返回栈顶元素
char Pop_zifu(STACK_zifu* s)
{
	char e;
	if (s->base == s->top)
		return 0;
	else
	{
		e = s->data[s->top - 1];
		s->top--;
	}
	return e;
}
//删除数据栈栈顶的元素并返回栈顶元素
float Pop_shuju(STACK_shuju* s)
{
	float e;
	if (s->base == s->top)
		return 0;
	else
	{
		e = s->data[s->top - 1];
		s->top--;
	}
	return e;
}
//定义一个运算符组合包括(),+,-,*,/,%
char operation[8] = { '(',')','+','-','*','/','%','!' };  //'!'作为栈底标志 
//判断所测字符是否在已知运算符集合内,若是，则返回1
int Judge(char m, char* test)
{
	int p = 0, i;
	for (i = 0; i < 7; i++)
	{
		if (m == test[i])
		{
			p = 1;
		}
	}
	return p;
}
//判断两种运算符啊a,b的优先级
int Level(char a, char b)
{
	int i, the_a, the_b;
	switch (a)
	{
	case'!':
		the_a = 0;
		break;
	case'(':
		the_a = 1;
		break;
	case')':
		the_a = 1;
		break;
	case'+':
		the_a = 2;
		break;
	case'-':
		the_a = 2;
		break;
	case'*':
		the_a = 3;
		break;
	case'/':
		the_a = 3;
		break;
	case'%':
		the_a = 3;
		break;
	}
	switch (b)
	{
	case'!':
		the_a = 0;
		break;
	case'(':
		the_b = 1;
		break;
	case')':
		the_b = 1;
		break;
	case'+':
		the_b = 2;
		break;
	case'-':
		the_b = 2;
		break;
	case'*':
		the_b = 3;
		break;
	case'/':
		the_b = 3;
		break;
	case'%':
		the_b = 3;
		break;
	}
	if (the_a >= the_b)
		return 1;
	else
		return 0;
}
//将中缀表达式转化为后缀表达式
void Transform(char* s1, char* s2)
{
	STACK_zifu one;
	char ch;
	int i = 0, j = 0;
	Makenull_zifu(&one); //将one栈置空
	Push_zifu('!', &one);   //将'!'存入栈底 
	for (; s1[i] != '\0';)
	{
		if (Judge(s1[i], operation) == 0) //如果不是运算符就放入输出数组s2
		{
			while ((s1[i] >= '0' && s1[i] <= '9') || s1[i] == '.') //小数和整数的情况一起考虑
			{
				s2[j++] = s1[i];
				i++;
			}
			s2[j++] = ' ';   //存入一个空格
		}
		else    //如果是运算符
		{
			switch (s1[i])
			{
			case'(':
				i++;
				if (s1[i] == '-')  //判断是否为负数，若是，则将负数存在数组s2，若不是，则把运算符放入栈中
				{
					while (s1[i] != ')')
					{
						s2[j++] = s1[i];
						i++;
					}
					s2[j++] = ' ';//空格作为间隔
					i++;
				}
				else
				{
					i--;
					Push_zifu(s1[i], &one);
					i++;
				}
				break;
			case')':
				ch = Pop_zifu(&one);
				do             //输出)到(在栈中的所有运算符
				{
					s2[j++] = ch;
					s2[j++] = ' ';  //空格作为间隔
					ch = Pop_zifu(&one);
				} while (ch != '(');
				i++;
				break;
			default:
				while (Level(Top_zifu(&one), s1[i]) == 1)  //判断运算符的优先级，使栈顶元素永远优先级最高
				{
					s2[j++] = Pop_zifu(&one);
					s2[j++] = ' ';  //空格作为间隔
				}
				Push_zifu(s1[i], &one);
				i++;
			}
		}
	}
	for (; Top_zifu(&one) != '!';)   //s1扫描完成后，把栈中所有运算符存入数组s2,以最开始存入栈中的'!'作为标志
	{
		s2[j++] = Pop_zifu(&one);
		s2[j++] = ' ';   //空格作为间隔
	}
}
//对a与b执行运算符操作
float Handle(float a, char panduan, float b)
{
	int d, e;
	switch (panduan)
	{
	case'+':
		return a + b;
	case'-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		if (b == 0)
		{
			printf("不能完成除0运算 \n");
			return 0;
		}
		return a / b;
		break;
	case'%':
		d = (int)a;
		e = (int)b;
		if (e == 0)
		{
			printf("不能完成对0的取余运算\n");
			return 0;
		}
		return (float)(d % e);
		break;
	default:
		printf("出现错误\n");
		return 0;
	}
}
//计算后缀表达式的值
int main()
{
	STACK_shuju two;
	char c, ch;
	int i = 0, step = 0, j = 0;
	float a = 0, b = 0, s = 0;
	do
	{
		i = 0;
		char jianpan[200] = { 0 }, shuchu[200] = { 0 };
		Makenull_shuju(&two);
		printf("**************************************\n");
		printf("***请输入你想转化的一个中缀表达式：***\n");
		scanf("%s", jianpan);  //输入一个中缀表达式,对于负数的输入必须要加括号
		Transform(jianpan, shuchu);
		printf("********转化后的后缀表达式为：********\n");
		printf("%s\n", shuchu);  //输出转化后的后缀表达式
		ch = shuchu[0];
		while(ch != '\0')     //计算后缀表达式的值
		{
			if (Judge(shuchu[i], operation) == 0) //如果不是运算符则压入栈中
			{
				s = 0;
				a = b = step = 0;
				while (shuchu[i] >= '0' && shuchu[i] <= '9' && shuchu[i] != '.' && shuchu[i] != ' ')//算出小数点前面的整数数值
				{
					s = 10 * s + shuchu[i] - 48;
					i++;
				}
				if (shuchu[i] == '.')  //算出小数点后面的数值
				{
					i++;
					while (shuchu[i] >= '0' && shuchu[i] <= '9' && shuchu[i] != ' ')
					{
						b = 10 * b + shuchu[i] - 48;
						i++;
						step++;
					}
					for (j = 0; j < step; j++)
					{
						b = b / 10;
					}
				}
				a = s + b;   //将小数部分与整数部分相加
				Push_shuju(a, &two);
				ch = shuchu[++i];
			}
			else if (shuchu[i] == '-')     //判断-是减号还是负号
			{
				i++;
				if (shuchu[i] >= '0' && shuchu[i] <= '9')   //满足此条件为负号，计算出该负数，并压入堆栈
				{
					s = 0;
					a = b = step = 0;
					while (shuchu[i] >= '0' && shuchu[i] <= '9' && shuchu[i] != '.' && shuchu[i] != ' ')//算出小数点前面的整数数值
					{
						s = 10 * s + shuchu[i] - 48;
						i++;
					}

					if (shuchu[i] == '.')//算出小数点后面的数值
					{
						i++;
						while (shuchu[i] >= '0' && shuchu[i] <= '9' && shuchu[i] != ' ')
						{
							b = 10 * b + shuchu[i] - 48;
							i++;

							step++;
						}
						for (j = 0; j < step; j++)
						{
							b = b / 10;
						}
					}
					a = -(s + b);//整数部分和小数部分相加，赋于a并取反，得到负数值
					Push_shuju(a, &two);
					ch = shuchu[++i];
				}
				else            //当-为减号时，按运算符进行运算
				{
					b = Pop_shuju(&two);
					a = Pop_shuju(&two);
					Push_shuju(Handle(a, ch, b), &two);
					ch = shuchu[++i];
				}
			}
			else            //按相应的运算符进行计算
			{
				b = Pop_shuju(&two);
				a = Pop_shuju(&two);
				Push_shuju(Handle(a, ch, b), &two);
				i += 2;
				ch = shuchu[i];
			}
		}
		printf("******所得到的后缀表达式的值为：******\n%g\n", Top_shuju(&two));
		printf("**************************************\n");
		printf("想尝试更多的转化吗？输入'T'或't'可继续\n");
        getchar();
        c=getchar();
	}while(c == 'T'||c == 't');     //继续操作的判断
	return 0;
}
