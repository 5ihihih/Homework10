#include <stdio.h>
#include <stdlib.h>

/*정수, 왼쪽 자식 노드의 주소, 오른쪽 자식 노드의 주소를 갖는 구조를 선언*/
typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];	//스택의 크기는 20
int top = -1;					//top의 초기값은 -1
Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];	//큐의 크기는 20
int front = -1;					//front와 rear의 초기값은 -1
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
	printf("[----- [오인화] [2022078036] -----]");
	
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

/*노드를 초기화하는 함수*/
int initializeBST(Node** h) {

	/*빈 트리가 아니라면 모든 노드의 메모리 해제*/
	if(*h != NULL)
		freeBST(*h);

	/*헤드노드 선언 및 초기화*/
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

    /*스택의 top 초기값 설정*/
	top = -1;

    /*큐의 front, rear 초기값 설정*/
	front = rear = -1;

	return 1;
}

/*inorder방식으로 트리를 출력하는 함수*/
void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);	//리프노드가 나타날때까지 순환한다
		printf(" [%d] ", ptr->key);		//리프노드를 출력하고
		recursiveInorder(ptr->right);	//오른쪽 노드가 있는지 확인한다

		//이후 출력과 오른쪽 노드 확인을 반복한다
	}
}

/*stack을 이용한 inorder방식으로 트리를 출력하는 함수*/
void iterativeInorder(Node* node)
{
	for(;;)
	{   
        /*스텍에 왼쪽 자식 노드를 모두 삽입*/
		for(; node; node = node->left)
			push(node);

        /*스텍의 top에 위치한 원소를 가져온다*/
		node = pop();

        /*스텍에서 원소가 모두 제거되었다면 반복문 종료 */
		if(!node) break;
		printf(" [%d] ", node->key);    //스텍의 원소 출력

		node = node->right; //node가 오른쪽 자식노드를 가리키도록 한다
							//오른쪽 자식노드가 없다면 이전에 스텍에 저장된 원소가 출력되고
							//오른쪽 자식노드가 있다면 그 노드의 해당하는 값이 스텍에 삽입된 후 바로 출력된다 
	}
}


/*Queue를 이용해 레벨의 순서로 트리를 출력하는 함수*/
void levelOrder(Node* ptr)
{
	if(!ptr) return; //빈 트리일 경우 함수 종료

	enQueue(ptr);   //큐에 원소(노드) 삽입

	for(;;)
	{   
        /*큐의 첫번째 원소를 가져오고 큐에서 삭제한다*/
		ptr = deQueue();    
		if(ptr) {
			printf(" [%d] ", ptr->key);		//원소 출력
			//리프노드가 아니라면 큐에 원소(노드) 삽입
			if(ptr->left)	
				enQueue(ptr->left);
			if(ptr->right)
				enQueue(ptr->right);
		}
		else
			break;

	}

}


/*트리에 노드를 삽입하는 함수*/
int insert(Node* head, int key)
{
    /*삽입할 노드 생성*/
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

    /*빈 트리라면, 새로운 노드를 헤드노드의 왼쪽 자식노드로 설정*/
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {    //리프노드에 도달하면 반복 종료

		/*삽입할 노드의 키와 동일한 키가 있다면 리턴*/
		if(ptr->key == key) return 1;

        /*현재노드의 주소를 parentNode에 저장*/
		parentNode = ptr;

        /*현재 노드의 키가 새로운 노드의 키보다 작을 경우,
        ptr이 오른쪽 자식노드를 가리키도록 한다*/
		if(ptr->key < key)
			ptr = ptr->right;
        /*현재 노드의 키가 새로운 노드의 키보다 클 경우,
        ptr이 왼쪽 자식노드를 가리키도록 한다*/
		else
			ptr = ptr->left;
	}

    /*부모노드의 키가 새로운 노드의 키보다 클 경우,
    부모노드의 왼쪽 자식노드로 새로운 노드를 설정*/  
	if(parentNode->key > key)
		parentNode->left = newNode;
    /*부모노드의 키가 새로운 노드의 키보다 작을 경우,
    부모노드의 오른쪽 자식노드로 새로운 노드를 설정*/
	else
		parentNode->right = newNode;
	return 1;
}


/*노드를 제거하는 함수*/
int deleteNode(Node* head, int key)
{
    /*빈 노드인 경우, 함수 종료*/
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

	/*리프노드까지 탐색했거나 키를 찾으면 반복 종료*/
	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) {

			parent = ptr;	//부모노드의 주소를 저장

			/*키를 비교하며 탐색한다*/
			if(ptr->key > key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}

	/*키를 찾지 못했을 경우 함수 종료*/
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*키를 찾았을 경우*/
	/*키를 가진 노드가 리프노드일 경우*/
	if(ptr->left == NULL && ptr->right == NULL)
	{
		/*부모노드와 삭제할 노드의 연결을 끊는다*/
		if(parent != NULL) {
			if(parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		} else {
			head->left = NULL;

		}

		free(ptr);	/*노드의 메모리를 해제한다*/
		return 1;
	}

	/*삭제할 노드의 자식노드가 있을 경우*/
	if ((ptr->left == NULL || ptr->right == NULL))
	{
		Node* child;
		if (ptr->left != NULL)	/*왼쪽 자식 노드가 있다면, 왼쪽 자식 노드의 주소를 저장해 놓는다*/
			child = ptr->left;
		else					/*오른쪽 자식 노드가 있다면, 오른쪽 자식 노드의 주소를 저장해 놓는다*/
			child = ptr->right;

		if(parent != NULL)
		{
			if(parent->left == ptr)		/*삭제할 노드가 parent의 왼쪽 자식 노드인 경우*/
				parent->left = child;   /*왼쪽 자식 노드의 child를 parent와 연결한다*/
			else						/*삭제할 노드가 parent의 오른쪽 자식 노드인 경우*/
				parent->right = child;	/*오른쪽 자식 노드의 child를 parent와 연결한다*/
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child;
		}

		free(ptr);	//노드의 메모리 해제
		return 1;
	}

	
	/*삭제할 노드의 자식노드가 두개 모두 있을 경우
	(루트노드를 오른쪽 서브트리에서 가장 작은 원소로 한다)*/

	Node* candidate;   //제거할 노드
	parent = ptr;	

	candidate = ptr->right;	

	/*가장 작은 노드를 찾기 위해 왼쪽 자식 노드를 탐색한다*/
	while(candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}

	if (parent->right == candidate)	//위의 while문이 동작하지 않은 경우 
		parent->right = candidate->right;
	else //위의 while문이 동작한 경우
		parent->left = candidate->right;

	/*ptr의 key에 candidate의 key를 대입함으로써 인자로 받은 key를 제거한다*/
	ptr->key = candidate->key;

	free(candidate);	//메모리 해제
	return 1;
}


/*노드의 메모리를 해제하는 함수*/
void freeNode(Node* ptr)
{
    /*leaf노드가 나올때까지 함수를 recursive하고 
	왼쪽 오른쪽 순서로 헤드노드 이외의 모든 노드의 메모리를 해제한다*/
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

/*트리의 메모리를 해제하는 함수*/
int freeBST(Node* head)
{
    /*헤드노드만 있는 트리일 경우, 헤드노드의 메모리를 해제하고 리턴*/
	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);  //노드의 메모리 해제

	free(head); //헤드노드의 메모리 해제

	return 1;
}


/*스텍의 원소를 제거하는 함수*/
Node* pop()
{
    /*빈 스텍이라면 리턴 NULL*/
	if (top < 0) return NULL;
    /*top의 원소를 리턴하고 top을 하나 감소함*/
	return stack[top--];
}

/*스텍의 top에 원소를 삽입하는 함수*/
void push(Node* aNode)
{
    /*top을 하나 증가시키고 그곳에 노드 삽입*/
	stack[++top] = aNode;
}

/*스텍을 프린트하는 함수*/
void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}

/*큐의 원소를 제거하는 함수*/
Node* deQueue()
{
    /*빈 큐라면 리턴 NULL*/
	if (front == rear) {
		return NULL;
	}

    /*빈 큐가 아니라면, front의 위치를 하나 증가시킨 후 그곳의 원소 제거*/
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];

}

/*큐에 원소를 삽입하는 함수*/
void enQueue(Node* aNode)
{
    /*rear이 다음 위치를 가리키도록 한다*/
	rear = (rear + 1) % MAX_QUEUE_SIZE;
    /*공간이 없다면 함수 종료*/
	if (front == rear) {
		return;
	}

    /*공간이 있다면, rear의 위치에 원소 삽입*/
	queue[rear] = aNode;
}






