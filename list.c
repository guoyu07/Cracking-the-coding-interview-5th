#include <stdio.h>
#include <stdlib.h>

struct grade{
	int score;
	struct grade *next;
};

typedef struct grade NODE;
struct grade *create();
void insert(NODE *head, NODE *pnew, int i);
void pdelete(NODE *head, int i);
void display(NODE *head);
void Pfree(NODE *head);	

int main(int argc, char *argv[]){
	struct grade *head, *pnew;
	head = create();
	if(head == NULL)
		return 0;
	printf("输出创建的链表");
	display(head);
	pnew = (NODE *)malloc(sizeof(NODE));
	if(pnew == NULL){
		printf("创建失败！");
		return 0;
	}
	pnew->score = 88;
	insert(head, pnew, 3);	//将新节点插入节点3的后边
	printf("插入后的链表：");
	display(head);
	pdelete(head, 4);	//删除节点3
	printf("删除后的节点：");
	display(head);
	Pfree(head);
	return 0;
}

struct grade *create(){
	NODE *head, *tail, *pnew;
	int score;
	head = (NODE *)malloc(sizeof(NODE));
	if(head == NULL){
		printf("创建失败! ");
		return NULL;
	}
	head->next = NULL;	//头节点指针域置null
	tail = head;		//开始时尾指针指向头节点
	printf("输入学生成绩：");
	while(1){
		scanf("%d", &score);
		if(score < 0)	//成绩为负时推出循环
			break;
		pnew = (NODE *)malloc(sizeof(NODE));	//创建新节点
		if(pnew == NULL){
			printf("创建失败");
			return NULL;
		}
		pnew->score = score;//新节点数据域存放输入的成绩
		pnew->next=NULL;	//新节点指针域置NULL
		tail->next = pnew;	//新节点插入到表尾
		tail=pnew;		//为指针指向当前的尾节点
	}
	return head;			//返回创建链表的头指针
}

void insert(NODE *head, NODE *pnew, int i){
	NODE *p;
	int j;

	p = head;
	for(j = 0; j < i; j++)
		p = p->next;		//p指针指向要插入的第i个节点
	if(p == NULL)		{
		printf("插入的节点不存在");
		return;
	}

	pnew->next = p->next;	//插入节点的指针域指向第i个节点的后续节点
	p->next = pnew;			//将第i个节点的指针域指向插入的新节点
}

void pdelete(NODE *head, int i){
	NODE *p, *q;
	int j;
	if(i == 0)				//删除的是头指针，返回
		return;
	p = head;
	for(j = 1; j < i && p->next != NULL; j++)
		p = p->next;		//将p指向要删除的第i个节点的前驱节点
	if(p->next == NULL){
		printf("不存在!");
		return;
	}
	q = p->next;			//q指向待删除的节点
	p->next = q->next;		//删除节点i
	free(q);
}

void display(NODE *head){
	NODE *p;
	for(p = head->next; p != NULL; p = p->next)
		printf("%d ", p->score);
	printf("\n");
}

void pfree(NODE *head){
	NODE *p, *q;

	p = head;
	while(p->next != NULL){//每次删除头节点的后继节点
		q = p->next;
		p->next = q->next;
		free(q);
	}

	free(head);				//最后删除头节点
}

void Pfree(NODE *head){
	NODE *p, *q;
	p = head;
	while(p->next != NULL){
		q = p->next;
		p->next = q->next;
		free(q);
	}
	free(p);
}