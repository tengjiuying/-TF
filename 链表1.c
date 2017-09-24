#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100

//Status Ϊ���������ͣ���ֵ�Ǻ������״̬���룬��OK��
typedef int Status; 

// ElemTypeΪ����Ԫ�����ͣ�����ʵ������������������Ϊint 
typedef int ElemType; 

struct LNode               /* ��㶨�� */     
 {
   int r[MAXSIZE+1];
   ElemType data;
   struct LNode *next;
   int length;
 };
 typedef struct LNode* LinkList; /* ���ͷָ������ */


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


	printf("����������La��\n");
	La = Linkcreat();
	La_len = ListLength(La);
	printf("����������Lb��\n");
	Lb = Linkcreat();
	Lb_len = ListLength(Lb);
	Union(La, Lb);
	printf("A��B = ��\n");
	printLink(La);
	printf("%d, %d",La_len, Lb_len);
	printf("\n\n\n");
	
	printf("����������La��\n");
	La = Linkcreat();
	La_len = ListLength(La);
	printf("����������Lb��\n");
	Lb = Linkcreat();
	Lb_len = ListLength(Lb);
	Union(La, Lb);
	InitList(Lc);
	MergeList(La, Lb, Lc);
	printLink(Lc);
	Lc_len = ListLength(Lc);
	printf("A��B = ��\n");
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
 { // �������ڱ�Lb������B���ϣ��е�����La������A���ϣ��е�����Ԫ�ز��뵽La��
   ElemType e;
   int La_len,Lb_len;
   int i;
	La_len = ListLength(La); // ���La�ĳ���
   Lb_len = ListLength(Lb);
   for(i = 1; i <= Lb_len; i++)
   {
     GetElem(Lb,i,&e); // ȡ��Lb�е�i������Ԫ�ظ�������e
     if(!LocateElem(La, e)) // ��La�в����ں�e��ͬ��Ԫ��,��e����La��
       ListInsert(La, ++La_len, e);
   }
 }
 
 void MergeList(LinkList La, LinkList Lb, LinkList Lc) 
 { /* ��֪��La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ����С� */
   /* �鲢La��Lb�õ��µı�Lc,Lc������Ԫ��Ҳ��ֵ�ǵݼ����� */
   int i = 1;
   int j =1;
   int k=0;
   int ai, bj;
   int La_len, Lb_len;
   InitList(Lc);
   La_len=ListLength(La);
   Lb_len=ListLength(Lb);
   
   while(i<=La_len&&j<=Lb_len)          /* ��La�ͱ�Lb���ǿ� */
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
   while(i <=La_len)                /* ��La�ǿ��ұ�Lb�� */
   {
     GetElem(La,i++, &ai);
	 
     ListInsert(Lc,++k,ai);
   }
   while(j <=Lb_len)                /* ��Lb�ǿ��ұ�La�� */
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
 { /* LΪ�������ͷָ�롣����i��Ԫ�ش���ʱ,
      ��ֵ����e������OK,���򷵻�ERROR */
   int j = 1; /* jΪ������ */
   LinkList p = L; /* pָ���һ����� */
   while(p&&j<i) /* ˳ָ��������, ֱ��pָ���i��Ԫ��
                 ��pΪ�� */
   {
     p=p->next;
     j++;
   } 	   
   if(!p||j>i)   /* ��i��Ԫ�ز����� */
     return ERROR;
   *e = p->data;   /* ȡ��i��Ԫ�� */
   return OK;
 }

Status ListEmpty(LinkList L)
{ /* ��ʼ��������ʽ�洢�ı�L�Ѵ��ڡ�*/
  /*�����������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
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
