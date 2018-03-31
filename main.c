#include <stdio.h>
#include <stdlib.h>

#define ARRMALLOCSIZE 5
#define FALSE         0
#define TRUE          1 

typedef struct listNode
{
    int data;                   //数据域
    struct listNode *next;      //指针域
}linkList;

void initLinkList(linkList *tempList)
{
    tempList->next = NULL;      //指针域制空
}

int footCreateLinkList(linkList *tempList)
{
    int temp;
    linkList *node, *flag;                              //flag指针永远指向tempList尾部位置
    flag = tempList;
    node = (linkList *)malloc(sizeof(linkList));
    //创建失败
    if(!node)
        return FALSE;

    scanf("%d", &temp);
    while(temp != -1)
    {
        node->data = temp;
        node->next = flag->next;
        flag->next = node;
        flag = node;

        node = (linkList *)malloc(sizeof(linkList));
        //创建失败
        if(!node)
            return FALSE;
        scanf("%d", &temp);
    }
    free(node);
    return TRUE;
}//尾插法创建单链表

//返回dest-1位置开始的链表指针
linkList *searchLinkListDestBefore(linkList *tempList, int dest)
{
    linkList * p = tempList;
    int i = 0, linkListLength;

    linkListLength = getLinkListLength(tempList);

    //位置合法性判断
    if(dest < 0 || dest > linkListLength)
        return NULL;

    for(i = 0; i < dest; i++)
        p = p->next;
    return p;
}

//向链表的dest位置插入num 增
int insertLinkList(linkList *tempList, int dest, int num)
{
    linkList *p, *node;
    //调用上文说到的方法
    p = searchLinkListDestBefore(tempList, dest-1);                 //现在p指向dest-1节点
    if(!p)                                                          //dest-1位置不存在判断
        return FALSE;

    node = (linkList *)malloc(sizeof(linkList));
    if(!node)
        return FALSE;

    node->data = num;                                               //dest不存在或不存在不影响
    node->next = p->next;
    p->next = node;

    return TRUE;
}

//删除链表中的第dest位置的值 删
int deleteLinkList(linkList *tempList, int dest)
{
    linkList *p = searchLinkListDestBefore(tempList, dest-1);       //现在p指向dest-1节点

    if(!p || !p->next)                                              //dest-1 或 dest位置不存在判断
        return FALSE;

    if(!p->next->next)                                              //dest存在，但为最后一个节点
        p->next = NULL;
    else                                                            //dest存在，为中间节点
        p->next = p->next->next;

    return TRUE;
}

//把链表dest位置的值改为num 改
int changeLinkList(linkList *tempList, int dest, int num)
{
    linkList *p = searchLinkListDestBefore(tempList, dest-1);       //现在p指向dest-1节点
    if(!p || !p->next)                                              //dest-1位置不存在判断
        return FALSE;

    p->next->data = num;

    return TRUE;
}

//[按值dest]查找,对应节点的位置存储在tempNode里--按值查找
int searchLinkListByValue(linkList *tempList, int num, resNode *tempNode)
{
    linkList *p = tempList->next;
    int j = 1;

    tempNode->length = 0;
    tempNode->arr = (int *)malloc(sizeof(int) * ARRMALLOCSIZE);
    //创建失败
    if(!tempNode->arr)
        return FALSE;
    //循环对链表进行遍历
    while(p)
    {
        //空间不足开辟空间
        if((!(tempNode->length % 5)) && tempNode->length != 0)
        {
            tempNode->arr = (int *)realloc(tempNode->arr,  sizeof(int) * (tempNode->length + 1) * ARRMALLOCSIZE);
            //创建失败
            if(!tempNode->arr)
                return FALSE;
        }
        if(p->data == num)
        {
            tempNode->arr[tempNode->length++] = j;
        }
        p = p->next;
        j++;
    }
    return TRUE;
}