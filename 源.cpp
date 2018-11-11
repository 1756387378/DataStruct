#define _CRT_SECURE_NO_WARNINGS
/*�������ز���*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int datatype;
typedef struct Inode
{
	datatype data;                                       /*���ݲ���*/
	struct Inode *pNext;                                 /*ָ��һ���ڵ��ָ�벿��*/
}LinkNode;

LinkNode *Create();                                      /*����Ĵ���*/
LinkNode *Insert(LinkNode *pHead);                       /*���������*/
LinkNode *Delete(LinkNode *pHead);                       /*����ɾ��*/
void Print(LinkNode *pHead);                             /*�������*/
void Search(LinkNode *pHead);                            /*���ݲ���*/
void Menu(LinkNode *pHead);                              /*���˵�*/
int iCount = 0;                                          /*ȫ�ֱ�����ʾ����ĳ���*/
void Destroy(LinkNode *pHead);                           /*��������*/
int n;

int main()
{
	LinkNode *pHead = NULL;
	Menu(pHead);
	return 0;
}

/*���˵�*/
void Menu(LinkNode *pHead)
{
	char ch;
	printf("\t\t1.��������\n\n");
	printf("\t\t2.����������ݺͱ�\n\n");
	printf("\t\t3.��������\n\n");
	printf("\t\t4.��������\n\n");
	printf("\t\t5.ɾ������\n\n");
	printf("\t\t6.�˳�\n\n");

	scanf("%c", &ch);
	switch (ch)
	{
	case '1':
		pHead = Create();                                    /*����������*/
		break;
	case '2':
		Print(pHead);                                        /*�������*/
		break;
	case '3':
		Search(pHead);                                       /*���ݲ���*/
		break;
	case '4':
		pHead = Insert(pHead);                               /*��������*/
		break;
	case '5':
		pHead = Delete(pHead);                               /*ɾ������*/
		break;
	case '6':
		Destroy(pHead);										/*��������*/
		exit(0);
	}
	system("cls");
	Menu(pHead);
}

/*����������*/
LinkNode *Create()                                         /*����ָ��ֵ�ĺ���*/
{
	LinkNode *pHead = NULL;                                /*��ʼ������ͷָ��Ϊ��*/
	LinkNode *pEnd = NULL, *pNew = NULL;                   /*pEndָ��ԭ��β���,pNewָ���´����Ľ��*/
	int i = 1;
	pEnd = pNew = (LinkNode*)malloc(sizeof(LinkNode));     /*(LinkNode*)�����ص�ַת��Ϊ�ṹ����ָ��*/
	printf("��������Ҫ����ĸ�����");
	scanf("%d", &n);
	while (i <= n)
	{
		printf("�������%d�����ݣ�",i);
		scanf("%d", &pNew->data);
		iCount++;
		if (iCount == 1)
		{
			pNew->pNext = NULL;                            /*ʹ��ָ��Ϊ��*/
			pEnd = pNew;                                   /*�����¼�����*/
			pHead = pNew;                                  /*ͷָ��ָ���׽��*/
		}
		else
		{
			pNew->pNext = NULL;                            /*�½���ָ��Ϊ��*/
			pEnd->pNext = pNew;                            /*ԭ����β���ָ���½��*/
			pEnd = pNew;                                   /*pEndָ���½��*/
		}
		pNew = (LinkNode*)malloc(sizeof(LinkNode));
		i++;
	}
	free(pNew);                                             /*�ͷ�û���õ��Ŀռ�*/
	return pHead;
};

/*���������*/
void Print(LinkNode *pHead)
{
	LinkNode *pTemp = NULL;                                 /*ѭ�����õ���ʱָ��*/
	int ilndex = 1;                                         /*��ʾ�����еĽ�����*/
	printf("------�������ܹ��� %d ������:-----\n", iCount);
	printf("\n");
	pTemp = pHead;                                          /*ָ��õ��׽��ĵ�ַ*/
	while (pTemp != NULL)
	{
		printf("�� %d ������:\n", ilndex);
		printf("����:%d\n", pTemp->data);
		printf("\n");
		pTemp = pTemp->pNext;                                /*�ƶ���ʱָ�뵽��һ�����*/
		ilndex++;                                            /*�����Լ�����*/
	}
	system("pause");
}

/*���ݲ���*/
void Search(LinkNode *pHead)
{
	int i = 1;
	datatype data;
	LinkNode *pTemp;
	pTemp = pHead;
	printf("��������Ҫ���ҵ����ݣ�");
	scanf("%d", &data);
	do {
		if (pTemp == NULL || pTemp->pNext == NULL)              /*����Ϊ�ջ��߱���������������û���ҵ�*/
		{
			printf("�����ݲ����ڣ�");
			break;
		}
		if (data == pTemp->data)
		{
			printf("������λ�ڵ� %d λ��\n", i);
			printf("��Ҫ���ҵ������ǣ�%d\n", pTemp->data);
			break;
		}
		i++;
		pTemp = pTemp->pNext;
	} while (pTemp != NULL);
	system("pause");
 }

/*��������*/
LinkNode *Insert(LinkNode *pHead)
{
	int i = 1, k;
	datatype data;
	LinkNode *pNew, *pTemp, *pPre;                                   /*ָ���·���Ŀռ䡢��ʱָ��*/
	pTemp = pHead;
	pPre = pTemp;
	printf("������λ�ã�");
	scanf("%d", &k);
	if (k > iCount + 1)
	{
		printf("����λ������");
		system("pause");
		return pHead;
	}
	else if (pTemp == NULL)
	{
		pNew = (LinkNode *)malloc(sizeof(LinkNode));              /*�����ڴ�ռ䣬������ָ����ڴ�ռ��ָ��*/
		printf("���������ݣ�");
		scanf("%d", &pNew->data);
		pHead = pNew;
		pNew->pNext = NULL;
		iCount++;
	}
	else
	{
		pNew = (LinkNode *)malloc(sizeof(LinkNode));              /*�����ڴ�ռ䣬������ָ����ڴ�ռ��ָ��*/
		printf("���������ݣ�");
		scanf("%d", &pNew->data);
		while (i <= iCount + 1)
		{
			if (k == 1)                                           /*�����һ��λ��*/
			{
				pHead = pNew;
				pNew->pNext = pTemp;
				break;
			}
			if (i == k)                                          /*����ǵ�һ��λ��*/
			{
				pPre->pNext = pNew;
				pNew->pNext = pTemp;
				break;
			}
			pPre = pTemp;
			pTemp = pTemp->pNext;
			i++;
		}
		iCount++;                                                 /*���������������*/
	}
	return pHead;
}

/*ɾ������*/
LinkNode *Delete(LinkNode *pHead)                                 /*pHead��ʾͷ��㣬ilndex��ʾҪɾ���Ľ���±�*/
{
	int i = 1;                                                   /*����ѭ������*/
	int k;
	LinkNode *pTemp;                                             /*��ʱָ��*/
	LinkNode *pPre;                                              /*��ʾҪɾ�����ǰ�Ľ��*/
	pTemp = pHead;                                               /*�õ�ͷ���*/
	pPre = pTemp;
	printf("��������Ҫɾ����λ�ã�");
	scanf("%d",&k);
	if (k > iCount || pHead == NULL)
	{
		printf("��λ�ò����ڣ�\n");
		system("pause");
		return pHead;
	}
	while (i <= iCount)
	{
		if (k == 1 && pTemp != NULL)                            /*ɾ��ͷ���*/
		{
			pHead = pTemp->pNext;
			break;
		}
		if (i == k && pTemp != NULL)                            /*ɾ����ͷ���*/
		{
			pPre->pNext = pTemp->pNext;                        /*����ɾ��������ߵĽ��*/
			break;
		}
		i++;
		pPre = pTemp;
		pTemp = pTemp->pNext;
	}
	free(pTemp);                                              /*�ͷŵ�Ҫɾ�������ڴ�ռ�*/
	iCount--;                                                 /*���������е�Ԫ�ظ���*/
	return pHead;
}
void Destroy(LinkNode *pHead)                                 /*��������*/
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