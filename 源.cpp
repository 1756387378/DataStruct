#define _CRT_SECURE_NO_WARNINGS
/*链表的相关操作*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int datatype;
typedef struct Inode
{
	datatype data;                                       /*数据部分*/
	struct Inode *pNext;                                 /*指向一个节点的指针部分*/
}LinkNode;

LinkNode *Create();                                      /*链表的创建*/
LinkNode *Insert(LinkNode *pHead);                       /*结点插入操作*/
LinkNode *Delete(LinkNode *pHead);                       /*结点的删除*/
void Print(LinkNode *pHead);                             /*链表输出*/
void Search(LinkNode *pHead);                            /*数据查找*/
void Menu(LinkNode *pHead);                              /*主菜单*/
int iCount = 0;                                          /*全局变量表示链表的长度*/
void Destroy(LinkNode *pHead);                           /*销毁链表*/
int n;

int main()
{
	LinkNode *pHead = NULL;
	Menu(pHead);
	return 0;
}

/*主菜单*/
void Menu(LinkNode *pHead)
{
	char ch;
	printf("\t\t1.创建链表\n\n");
	printf("\t\t2.输出所有数据和表长\n\n");
	printf("\t\t3.查找数据\n\n");
	printf("\t\t4.插入数据\n\n");
	printf("\t\t5.删除数据\n\n");
	printf("\t\t6.退出\n\n");

	scanf("%c", &ch);
	switch (ch)
	{
	case '1':
		pHead = Create();                                    /*创建链表结点*/
		break;
	case '2':
		Print(pHead);                                        /*输出链表*/
		break;
	case '3':
		Search(pHead);                                       /*数据查找*/
		break;
	case '4':
		pHead = Insert(pHead);                               /*插入数据*/
		break;
	case '5':
		pHead = Delete(pHead);                               /*删除数据*/
		break;
	case '6':
		Destroy(pHead);										/*销毁链表*/
		exit(0);
	}
	system("cls");
	Menu(pHead);
}

/*创建链表部分*/
LinkNode *Create()                                         /*返回指针值的函数*/
{
	LinkNode *pHead = NULL;                                /*初始化链表头指针为空*/
	LinkNode *pEnd = NULL, *pNew = NULL;                   /*pEnd指向原来尾结点,pNew指向新创建的结点*/
	int i = 1;
	pEnd = pNew = (LinkNode*)malloc(sizeof(LinkNode));     /*(LinkNode*)将返回地址转换为结构类型指针*/
	printf("请输入你要储存的个数：");
	scanf("%d", &n);
	while (i <= n)
	{
		printf("请输入第%d个数据：",i);
		scanf("%d", &pNew->data);
		iCount++;
		if (iCount == 1)
		{
			pNew->pNext = NULL;                            /*使得指向为空*/
			pEnd = pNew;                                   /*跟踪新加入结点*/
			pHead = pNew;                                  /*头指针指向首结点*/
		}
		else
		{
			pNew->pNext = NULL;                            /*新结点的指针为空*/
			pEnd->pNext = pNew;                            /*原来的尾结点指向新结点*/
			pEnd = pNew;                                   /*pEnd指向新结点*/
		}
		pNew = (LinkNode*)malloc(sizeof(LinkNode));
		i++;
	}
	free(pNew);                                             /*释放没有用到的空间*/
	return pHead;
};

/*输出链表部分*/
void Print(LinkNode *pHead)
{
	LinkNode *pTemp = NULL;                                 /*循环所用的临时指针*/
	int ilndex = 1;                                         /*表示链表中的结点序号*/
	printf("------该链表总共有 %d 个数据:-----\n", iCount);
	printf("\n");
	pTemp = pHead;                                          /*指针得到首结点的地址*/
	while (pTemp != NULL)
	{
		printf("第 %d 个数据:\n", ilndex);
		printf("数据:%d\n", pTemp->data);
		printf("\n");
		pTemp = pTemp->pNext;                                /*移动临时指针到下一个结点*/
		ilndex++;                                            /*进行自加运算*/
	}
	system("pause");
}

/*数据查找*/
void Search(LinkNode *pHead)
{
	int i = 1;
	datatype data;
	LinkNode *pTemp;
	pTemp = pHead;
	printf("请输入你要查找的数据：");
	scanf("%d", &data);
	do {
		if (pTemp == NULL || pTemp->pNext == NULL)              /*链表为空或者遍历完整个来链表没有找到*/
		{
			printf("该数据不存在！");
			break;
		}
		if (data == pTemp->data)
		{
			printf("该数据位于第 %d 位置\n", i);
			printf("你要查找的数据是：%d\n", pTemp->data);
			break;
		}
		i++;
		pTemp = pTemp->pNext;
	} while (pTemp != NULL);
	system("pause");
 }

/*插入数据*/
LinkNode *Insert(LinkNode *pHead)
{
	int i = 1, k;
	datatype data;
	LinkNode *pNew, *pTemp, *pPre;                                   /*指向新分配的空间、临时指针*/
	pTemp = pHead;
	pPre = pTemp;
	printf("请输入位置：");
	scanf("%d", &k);
	if (k > iCount + 1)
	{
		printf("插入位置有误！");
		system("pause");
		return pHead;
	}
	else if (pTemp == NULL)
	{
		pNew = (LinkNode *)malloc(sizeof(LinkNode));              /*分配内存空间，并返回指向该内存空间的指针*/
		printf("请输入数据：");
		scanf("%d", &pNew->data);
		pHead = pNew;
		pNew->pNext = NULL;
		iCount++;
	}
	else
	{
		pNew = (LinkNode *)malloc(sizeof(LinkNode));              /*分配内存空间，并返回指向该内存空间的指针*/
		printf("请输入数据：");
		scanf("%d", &pNew->data);
		while (i <= iCount + 1)
		{
			if (k == 1)                                           /*插入第一个位置*/
			{
				pHead = pNew;
				pNew->pNext = pTemp;
				break;
			}
			if (i == k)                                          /*插入非第一个位置*/
			{
				pPre->pNext = pNew;
				pNew->pNext = pTemp;
				break;
			}
			pPre = pTemp;
			pTemp = pTemp->pNext;
			i++;
		}
		iCount++;                                                 /*增加链表结点的数量*/
	}
	return pHead;
}

/*删除数据*/
LinkNode *Delete(LinkNode *pHead)                                 /*pHead表示头结点，ilndex表示要删除的结点下标*/
{
	int i = 1;                                                   /*控制循环变量*/
	int k;
	LinkNode *pTemp;                                             /*临时指针*/
	LinkNode *pPre;                                              /*表示要删除结点前的结点*/
	pTemp = pHead;                                               /*得到头结点*/
	pPre = pTemp;
	printf("请输入你要删除的位置：");
	scanf("%d",&k);
	if (k > iCount || pHead == NULL)
	{
		printf("该位置不存在！\n");
		system("pause");
		return pHead;
	}
	while (i <= iCount)
	{
		if (k == 1 && pTemp != NULL)                            /*删除头结点*/
		{
			pHead = pTemp->pNext;
			break;
		}
		if (i == k && pTemp != NULL)                            /*删除非头结点*/
		{
			pPre->pNext = pTemp->pNext;                        /*连接删除结点两边的结点*/
			break;
		}
		i++;
		pPre = pTemp;
		pTemp = pTemp->pNext;
	}
	free(pTemp);                                              /*释放掉要删除结点的内存空间*/
	iCount--;                                                 /*减少链表中的元素个数*/
	return pHead;
}
void Destroy(LinkNode *pHead)                                 /*销毁链表*/
{
	LinkNode *pNew, *pTemp;
	pTemp = pHead;
	while (pTemp != NULL)
	{
		pNew = pTemp->pNext;
		free(pTemp);
		pTemp = pNew;
	}
	pTemp = NULL;
}