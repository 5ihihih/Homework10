#include <stdio.h>
#include <stdlib.h>

/*����, ���� �ڽ� ����� �ּ�, ������ �ڽ� ����� �ּҸ� ���� ������ ����*/
typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];	//������ ũ��� 20
int top = -1;					//top�� �ʱⰪ�� -1
Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];	//ť�� ũ��� 20
int front = -1;					//front�� rear�� �ʱⰪ�� -1
int rear = -1;

int initializeBST(Node** h);
void recursiveInorder(Node* ptr);	 
int insert(Node* head, int key);   
int freeBST(Node* head); 
void iterativeInorder(Node* ptr);     
void levelOrder(Node* ptr);	          
int deleteNode(Node* head, int key); 
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);
void printStack();

int main()
{
	printf("[----- [����ȭ] [2022078036] -----]");
	
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;
		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;
		case 'l': case 'L':
			levelOrder(head->left);
			break;
		case 'p': case 'P':
			printStack();
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');

	return 1;
}

/*��带 �ʱ�ȭ�ϴ� �Լ�*/
int initializeBST(Node** h) {

	/*�� Ʈ���� �ƴ϶�� ��� ����� �޸� ����*/
	if(*h != NULL)
		freeBST(*h);

	/*����� ���� �� �ʱ�ȭ*/
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

    /*������ top �ʱⰪ ����*/
	top = -1;

    /*ť�� front, rear �ʱⰪ ����*/
	front = rear = -1;

	return 1;
}

/*inorder������� Ʈ���� ����ϴ� �Լ�*/
void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);	//������尡 ��Ÿ�������� ��ȯ�Ѵ�
		printf(" [%d] ", ptr->key);		//������带 ����ϰ�
		recursiveInorder(ptr->right);	//������ ��尡 �ִ��� Ȯ���Ѵ�

		//���� ��°� ������ ��� Ȯ���� �ݺ��Ѵ�
	}
}

/*stack�� �̿��� inorder������� Ʈ���� ����ϴ� �Լ�*/
void iterativeInorder(Node* node)
{
	for(;;)
	{   
        /*���ؿ� ���� �ڽ� ��带 ��� ����*/
		for(; node; node = node->left)
			push(node);

        /*������ top�� ��ġ�� ���Ҹ� �����´�*/
		node = pop();

        /*���ؿ��� ���Ұ� ��� ���ŵǾ��ٸ� �ݺ��� ���� */
		if(!node) break;
		printf(" [%d] ", node->key);    //������ ���� ���

		node = node->right; //node�� ������ �ڽĳ�带 ����Ű���� �Ѵ�
							//������ �ڽĳ�尡 ���ٸ� ������ ���ؿ� ����� ���Ұ� ��µǰ�
							//������ �ڽĳ�尡 �ִٸ� �� ����� �ش��ϴ� ���� ���ؿ� ���Ե� �� �ٷ� ��µȴ� 
	}
}


/*Queue�� �̿��� ������ ������ Ʈ���� ����ϴ� �Լ�*/
void levelOrder(Node* ptr)
{
	if(!ptr) return; //�� Ʈ���� ��� �Լ� ����

	enQueue(ptr);   //ť�� ����(���) ����

	for(;;)
	{   
        /*ť�� ù��° ���Ҹ� �������� ť���� �����Ѵ�*/
		ptr = deQueue();    
		if(ptr) {
			printf(" [%d] ", ptr->key);		//���� ���
			//������尡 �ƴ϶�� ť�� ����(���) ����
			if(ptr->left)	
				enQueue(ptr->left);
			if(ptr->right)
				enQueue(ptr->right);
		}
		else
			break;

	}

}


/*Ʈ���� ��带 �����ϴ� �Լ�*/
int insert(Node* head, int key)
{
    /*������ ��� ����*/
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

    /*�� Ʈ�����, ���ο� ��带 ������� ���� �ڽĳ��� ����*/
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {    //������忡 �����ϸ� �ݺ� ����

		/*������ ����� Ű�� ������ Ű�� �ִٸ� ����*/
		if(ptr->key == key) return 1;

        /*�������� �ּҸ� parentNode�� ����*/
		parentNode = ptr;

        /*���� ����� Ű�� ���ο� ����� Ű���� ���� ���,
        ptr�� ������ �ڽĳ�带 ����Ű���� �Ѵ�*/
		if(ptr->key < key)
			ptr = ptr->right;
        /*���� ����� Ű�� ���ο� ����� Ű���� Ŭ ���,
        ptr�� ���� �ڽĳ�带 ����Ű���� �Ѵ�*/
		else
			ptr = ptr->left;
	}

    /*�θ����� Ű�� ���ο� ����� Ű���� Ŭ ���,
    �θ����� ���� �ڽĳ��� ���ο� ��带 ����*/  
	if(parentNode->key > key)
		parentNode->left = newNode;
    /*�θ����� Ű�� ���ο� ����� Ű���� ���� ���,
    �θ����� ������ �ڽĳ��� ���ο� ��带 ����*/
	else
		parentNode->right = newNode;
	return 1;
}


/*��带 �����ϴ� �Լ�*/
int deleteNode(Node* head, int key)
{
    /*�� ����� ���, �Լ� ����*/
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left;

	Node* parent = NULL;
	Node* ptr = root;

	/*���������� Ž���߰ų� Ű�� ã���� �ݺ� ����*/
	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) {

			parent = ptr;	//�θ����� �ּҸ� ����

			/*Ű�� ���ϸ� Ž���Ѵ�*/
			if(ptr->key > key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}

	/*Ű�� ã�� ������ ��� �Լ� ����*/
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*Ű�� ã���� ���*/
	/*Ű�� ���� ��尡 ��������� ���*/
	if(ptr->left == NULL && ptr->right == NULL)
	{
		/*�θ���� ������ ����� ������ ���´�*/
		if(parent != NULL) {
			if(parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		} else {
			head->left = NULL;

		}

		free(ptr);	/*����� �޸𸮸� �����Ѵ�*/
		return 1;
	}

	/*������ ����� �ڽĳ�尡 ���� ���*/
	if ((ptr->left == NULL || ptr->right == NULL))
	{
		Node* child;
		if (ptr->left != NULL)	/*���� �ڽ� ��尡 �ִٸ�, ���� �ڽ� ����� �ּҸ� ������ ���´�*/
			child = ptr->left;
		else					/*������ �ڽ� ��尡 �ִٸ�, ������ �ڽ� ����� �ּҸ� ������ ���´�*/
			child = ptr->right;

		if(parent != NULL)
		{
			if(parent->left == ptr)		/*������ ��尡 parent�� ���� �ڽ� ����� ���*/
				parent->left = child;   /*���� �ڽ� ����� child�� parent�� �����Ѵ�*/
			else						/*������ ��尡 parent�� ������ �ڽ� ����� ���*/
				parent->right = child;	/*������ �ڽ� ����� child�� parent�� �����Ѵ�*/
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;
		}

		free(ptr);	//����� �޸� ����
		return 1;
	}

	
	/*������ ����� �ڽĳ�尡 �ΰ� ��� ���� ���
	(��Ʈ��带 ������ ����Ʈ������ ���� ���� ���ҷ� �Ѵ�)*/

	Node* candidate;   //������ ���
	parent = ptr;	

	candidate = ptr->right;	

	/*���� ���� ��带 ã�� ���� ���� �ڽ� ��带 Ž���Ѵ�*/
	while(candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}

	if (parent->right == candidate)	//���� while���� �������� ���� ��� 
		parent->right = candidate->right;
	else //���� while���� ������ ���
		parent->left = candidate->right;

	/*ptr�� key�� candidate�� key�� ���������ν� ���ڷ� ���� key�� �����Ѵ�*/
	ptr->key = candidate->key;

	free(candidate);	//�޸� ����
	return 1;
}


/*����� �޸𸮸� �����ϴ� �Լ�*/
void freeNode(Node* ptr)
{
    /*leaf��尡 ���ö����� �Լ��� recursive�ϰ� 
	���� ������ ������ ����� �̿��� ��� ����� �޸𸮸� �����Ѵ�*/
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

/*Ʈ���� �޸𸮸� �����ϴ� �Լ�*/
int freeBST(Node* head)
{
    /*����常 �ִ� Ʈ���� ���, ������� �޸𸮸� �����ϰ� ����*/
	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);  //����� �޸� ����

	free(head); //������� �޸� ����

	return 1;
}


/*������ ���Ҹ� �����ϴ� �Լ�*/
Node* pop()
{
    /*�� �����̶�� ���� NULL*/
	if (top < 0) return NULL;
    /*top�� ���Ҹ� �����ϰ� top�� �ϳ� ������*/
	return stack[top--];
}

/*������ top�� ���Ҹ� �����ϴ� �Լ�*/
void push(Node* aNode)
{
    /*top�� �ϳ� ������Ű�� �װ��� ��� ����*/
	stack[++top] = aNode;
}

/*������ ����Ʈ�ϴ� �Լ�*/
void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}

/*ť�� ���Ҹ� �����ϴ� �Լ�*/
Node* deQueue()
{
    /*�� ť��� ���� NULL*/
	if (front == rear) {
		return NULL;
	}

    /*�� ť�� �ƴ϶��, front�� ��ġ�� �ϳ� ������Ų �� �װ��� ���� ����*/
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];

}

/*ť�� ���Ҹ� �����ϴ� �Լ�*/
void enQueue(Node* aNode)
{
    /*rear�� ���� ��ġ�� ����Ű���� �Ѵ�*/
	rear = (rear + 1) % MAX_QUEUE_SIZE;
    /*������ ���ٸ� �Լ� ����*/
	if (front == rear) {
		return;
	}

    /*������ �ִٸ�, rear�� ��ġ�� ���� ����*/
	queue[rear] = aNode;
}






