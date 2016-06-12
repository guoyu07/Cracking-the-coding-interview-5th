/*二叉树的各种操作复习*/
#include <stdio.h>

#define BACK_ODER   -1
#define IN_ODER     0
#define PRE_ODER    1
#define LEVEL_ODER  2//层次化遍历
typedef struct _Node{
	char data;
	struct _Node *lchild;
	struct _Node *rchild;
} Node,*Tree;

/* 生成二叉树的普通方法
 * 按先序次序输入二叉树中结点的值
 * 构造二叉链表表示的二叉树T。输入空格表示空子树。 */
Node * CreateTree()
{
    char ch;
    Node *T;
    scanf("%c",&ch);
    if(ch==' ') /* 空 */
        return NULL;
    else
    {
        T=(Node *)malloc(sizeof(Node));
        if(!T)
            exit(0);
        T->data=ch; /* 生成根结点 */
        T->lchild = CreateTree(); /* 构造左子树 */
        T->rchild = CreateTree(); /* 构造右子树 */
    }
    return T;
}
/* 由先根序列和中根序列生成二叉树
 * 递归法。pre 是先跟序列，in是中根序列
 * pre_s是先根序列的起始，pre_e是先跟序列的结束
 * in_s是中根序列的起始,in_e是中根序列的结束
 */
Node *Convert(char pre[], int pre_s, int pre_e,
              char in [], int in_s , int in_e )
{


    int i = in_s;
    Node *p;
    if(in_s > in_e)return NULL;
    for(i=in_s;i<in_e&&in[i]!=pre[pre_s];i++);//找到中跟中的头所在位置
    p = (Node *)malloc(sizeof(Node));
    p->data = pre[pre_s];
    //注意以下递归过程是关键
    p->lchild = Convert(pre, pre_s+1, pre_s+i-in_s,
                        in,  in_s,i-1);
    p->rchild = Convert(pre, pre_s+i-in_s+1,pre_e,
                        in,  i+1,in_e);
    return p;
}
/* 求二叉树的度 */
int GetDegree(const Tree head)
{
    int degree = 0;
    int m,n;
    if(!head)return 0;

    if(head->lchild && head->rchild) return 2;
    else if(!head->lchild && !head->rchild) return 0;
    else {
        m = GetDegree(head->lchild) ;
        n = GetDegree(head->rchild) ;
        if(2==m || 2==n)return 2;
        else return 1;
    }
    return degree;
}
/* 求二叉树的高度 */
int GetHight(const Tree head)
{
    int m,n;
    if(!head)return 0;
    m = GetHight(head->lchild);
    n = GetHight(head->rchild);
    return 1 + (m > n ? m : n);
}
/* 输出二叉树中某个指定元素的祖父节点(包括自己)
 * 递归思想：如果那个节点在我的子树中，那么我是祖父节点
 * 返回值 ：1表示子树中有 ，0表示无 */
int GetGrandPa(const Tree head, const char e)
{
   if(!head)return 0;
   if(GetGrandPa(head->lchild,e) || GetGrandPa(head->rchild,e) || e==head->data)//子树中有此节点
   {
       printf("%c",head->data);
       return 1;
   }
   else return 0;
}

/* 层次化遍历，采用递归思想而不用队列。
 * 递归思想：把当前层遍历的同时把下一层存储好
 * nodes[]作为队列用,存储的当前层的节点
 * count记录当前层的元素个数 */
void LevTranverse(const Node* nodes[], int count)
{
    int i=0, j=0;
    Node *nextNodes[100] = {0};
    if(0 == count) return;
    for(i = 0,j=0; i<count; i++)
    {
        printf("%c\t",nodes[i]->data);
        if(nodes[i]->lchild)nextNodes[j++] = nodes[i]->lchild;
        if(nodes[i]->rchild)nextNodes[j++] = nodes[i]->rchild;
    }
    LevTranverse(nextNodes,j);
    return;
}

/* 遍历二叉树，参数oder控制遍历方式 */
void Tranverse(Node *head,int oder)
{
	if(!head)return ;
	if(LEVEL_ODER == oder)
	{
	    LevTranverse(&head,1);
        return;
	}
    if(PRE_ODER == oder) printf("%c\t",head->data);
	Tranverse(head->lchild,oder);
	if(IN_ODER == oder) printf("%c\t",head->data);
	Tranverse(head->rchild,oder);
	if(BACK_ODER == oder) printf("%c\t",head->data);
	return;
}


/* 构建二叉排序树 */
int InsertBiSearchTree(Node *head,char ch)
{
    Node *p,*pre,*newNode;
    if(NULL == head)return 1;
    p = head;
    while(p)
    {
        pre = p;
        if(ch == p->data)return 1;
        if(ch < p->data)p = p->lchild;
        else p = p->rchild;
    }
    newNode = (Node *)malloc(sizeof(Node));
    newNode->lchild = newNode->rchild = NULL;
    newNode->data = ch;
    if(ch < pre->data)pre->lchild = newNode;
    else pre->rchild = newNode;
    return 0;
}
Node* CreateBiSearchTree(void)
{
    char a;
    Node *p,*head,*q,*pre;
    scanf("%c",&a);
    if(' ' == a)return NULL;
    p = (Node *)malloc(sizeof(Node));
    p->lchild = p->rchild = NULL;
    p->data = a;
    head = p;
    while(1)
    {
        scanf("%c",&a);
        if(' ' == a)break;
        InsertBiSearchTree(head,a);
    }
    return  head;
}
/* 求一棵树的查找长度(查找成功) */
int GetSearchLength(Node *head,int hight)
{
    if(NULL == head)return 0;
    return hight
            + GetSearchLength(head->lchild,hight+1)
            + GetSearchLength(head->rchild,hight+1);

}

int main(int argc, char *argv[])
{
    char pre[]= "abcde";
	char in[] = "bcade";

	Node *head = Convert(pre,0,strlen(pre)-1,
                   in ,0,strlen(in)-1);

    printf("Hight : %d\n",GetHight(head));
    printf("Degree : %d\n",GetDegree(head));
    if(!GetGrandPa(head,'c'))printf("No grandpa !");printf("\n");
    Tranverse(head,LEVEL_ODER);printf("\n");

    printf("Now create BiSearchTree..\n");
    head = CreateBiSearchTree();
    Tranverse(head,IN_ODER);printf("\n");
    printf("%d\n",GetSearchLength(head,1));
    return 0;
}

