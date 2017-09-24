#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100

//Status 为函数的类型，其值是函数结果状态代码，如OK等
typedef int Status; 

// ElemType为数据元素类型，根据实际情况而定，这里假设为int 
typedef int ElemType; 

struct LNode               /* 结点定义 */     
 {
   int r[MAXSIZE+1];
   ElemType data;
   struct LNode *next;
   int length;
 };
 typedef struct LNode* LinkList; /* 表的头指针类型 */


LinkList Linkcreat(void);
void Union(LinkList La, LinkList Lb);
void MergeList(LinkList La, LinkList Lb,LinkList Lc);
int ListLength(LinkList L);
Status GetElem(LinkList L,int i, ElemType *e);
Status LocateElem(LinkList L,ElemType e);
void ListInsert(LinkList L, int i,ElemType e);
Status ListEmpty(LinkList L);
void printLink(LinkList L);
void printLinkTwo(LinkList L);
int InitList(LinkList L);
//void InsertSort(LinkList L)

#include<stdio.h>
#include<stdlib.h>
int main()
{
	struct LNode *La, *Lb, *Lc;
	int La_len, Lb_len, Lc_len;


	printf("请输入数据La：\n");
	La = Linkcreat();
	La_len = ListLength(La);
	printf("请输入数据Lb：\n");
	Lb = Linkcreat();
	Lb_len = ListLength(Lb);
	Union(La, Lb);
	printf("A∪B = ：\n");
	printLink(La);
	printf("%d, %d",La_len, Lb_len);
	printf("\n\n\n");
	
	printf("请输入数据La：\n");
	La = Linkcreat();
	La_len = ListLength(La);
	printf("请输入数据Lb：\n");
	Lb = Linkcreat();
	Lb_len = ListLength(Lb);
	Union(La, Lb);
	InitList(Lc);
	MergeList(La, Lb, Lc);
	printLink(Lc);
	Lc_len = ListLength(Lc);
	printf("A∪B = ：\n");
	getchar();
	printf("%d", Lc_len);
	
	return 0;
}


LinkList Linkcreat(void)
{
	int i = 0;
	struct LNode *p1, *p2, *Head;
	Head = NULL;
	p1 = p2 = (LinkList)malloc(sizeof(struct LNode));
	while (1)
	{
		scanf("%d", &p1->data);
		
		if ( Head == NULL)
		{
			Head = p1;
		}
		else
		{
			p2 ->next = p1;
		}
		p2 = p1;
		if (getchar() == '\n')
		{
			break;
		}
		p1 = (LinkList)malloc(sizeof(struct LNode));
	}
	p2->next = NULL;
	return Head;
}

int ListLength(LinkList L)
{
	int i = 0;

	
	while(L != NULL)
	{
		L = L -> next;
		i++;
	}
	
	return i;
}
  
 void Union(LinkList La, LinkList Lb) 
 { // 将所有在表Lb（代表B集合）中但不在La（代表A集合）中的数据元素插入到La中
   ElemType e;
   int La_len,Lb_len;
   int i;
	La_len = ListLength(La); // 求表La的长度
   Lb_len = ListLength(Lb);
   for(i = 1; i <= Lb_len; i++)
   {
     GetElem(Lb,i,&e); // 取表Lb中第i个数据元素赋给变量e
     if(!LocateElem(La, e)) // 表La中不存在和e相同的元素,则将e插入La中
       ListInsert(La, ++La_len, e);
   }
 }
 
 void MergeList(LinkList La, LinkList Lb, LinkList Lc) 
 { /* 已知表La和Lb中的数据元素按值非递减排列。 */
   /* 归并La和Lb得到新的表Lc,Lc的数据元素也按值非递减排列 */
   int i = 1;
   int j =1;
   int k=0;
   int ai, bj;
   int La_len, Lb_len;
   InitList(Lc);
   La_len=ListLength(La);
   Lb_len=ListLength(Lb);
   
   while(i<=La_len&&j<=Lb_len)          /* 表La和表Lb均非空 */
   {
     GetElem(La, i, &ai);
     GetElem(Lb, j, &bj);
     if(ai<=bj)
     {
       ListInsert(Lc, ++k, ai);
       ++i;
     }
     else
     {
       ListInsert(Lc, ++k, bj);
       ++j;
     }
   }
   while(i <=La_len)                /* 表La非空且表Lb空 */
   {
     GetElem(La,i++, &ai);
	 
     ListInsert(Lc,++k,ai);
   }
   while(j <=Lb_len)                /* 表Lb非空且表La空 */
   {
     GetElem(Lb,j++, &bj);
	 
     ListInsert(Lc,++k,bj);

   }
 }


int InitList(LinkList L){
	//LinkList *L;
	L = (LinkList *)malloc(sizeof(LinkList));
	if(!L){
		return -1;
	}
	(*L).length = 0;
	return 1;
}


 Status GetElem(LinkList L,int i,ElemType *e)
 { /* L为单链表的头指针。当第i个元素存在时,
      其值赋给e并返回OK,否则返回ERROR */
   int j = 1; /* j为计数器 */
   LinkList p = L; /* p指向第一个结点 */
   while(p&&j<i) /* 顺指针向后查找, 直到p指向第i个元素
                 或p为空 */
   {
     p=p->next;
     j++;
   } 	   
   if(!p||j>i)   /* 第i个元素不存在 */
     return ERROR;
   *e = p->data;   /* 取第i个元素 */
   return OK;
 }

Status ListEmpty(LinkList L)
{ /* 初始条件：链式存储的表L已存在。*/
  /*操作结果：若L为空表，则返回TRUE，否则返回FALSE */
    if(L->next)
            return FALSE;
    else
            return TRUE;
}

Status LocateElem(LinkList L,ElemType e)
{
	struct LNode *head;
	int i = 0;

	head = L;
	while(head != NULL)
	{
		if (head->data == e)
		{
			return OK;
		}
		head = head->next;  
	}
	return ERROR;
}

void ListInsert(LinkList L, int i,ElemType e)
{
	struct LNode *p1, *p2;
	int n = 1;

	p1 = L;
	while ( n < i - 1)
	{
		p1 = p1->next;
		n++;
	}
	p2 = (LinkList)malloc(sizeof(struct LNode));
	p2 ->data = e;
	p2 ->next = NULL;
	p1 ->next = p2;
}

void printLink(LinkList L)
{
	struct LNode *p1;

	p1 = L;
	while (p1 != NULL)
	{
		printf("%d ", p1->data);
		p1 = p1 ->next;
	}
	putchar('\n');
}

/*void printLinkTwo(LinkList L)
{
	int i;

	L.length = ListLength(L);
	for (i = 0; i < L.length; i++)
	{
		printf("%d ", L.data[i]);
	}
	putchar('\n');

}*/
