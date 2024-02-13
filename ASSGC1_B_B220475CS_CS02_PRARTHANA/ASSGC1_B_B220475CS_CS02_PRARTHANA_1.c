#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* buildTree(int in[], int pre[], int inStrt, int inEnd);

int search(int arr[], int strt, int end, int value);

void printPostorder(Node* node);

#define MAX_SIZE 1000

typedef struct Stack {
    int top;
    Node* array[MAX_SIZE];
} Stack;

Stack* createStack();

bool isStackEmpty(Stack* stack);

void push(Stack* stack, Node* node);

Node* pop(Stack* stack);

void zigzagTraversal(Node* root);

typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    Node** array;
} Queue;

Queue* createQueue(unsigned capacity);

bool isQueueEmpty(Queue* queue);

void enqueue(Queue* queue, Node* item);

Node* dequeue(Queue* queue);

void levelMax(Node* root);

int height(Node* node);

int diameter(Node* root);

int leftLeafSum(Node* root);

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);
    int in[n], pre[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &in[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &pre[i]);
    Node* root = buildTree(in, pre, 0, n - 1);
    char op;
    while (scanf(" %c", &op), op != 'e') {
        switch (op) {
            case 'p':
                printPostorder(root);
                break;
            case 'z':
                zigzagTraversal(root);
                break;
            case 'm':
                levelMax(root);
                break;
            case 'd':
                printf("%d", diameter(root));
                break;
            case 's':
                printf("%d", leftLeafSum(root));
                break;
        }
        printf("\n");
    }


    return 0;
}

Node* buildTree(int in[], int pre[], int inStrt, int inEnd) {
    static int preIndex = 0;
    if (inStrt > inEnd)
        return NULL;
    Node* tNode = newNode(pre[preIndex++]);
    if (inStrt == inEnd)
        return tNode;
    int inIndex = search(in, inStrt, inEnd, tNode->data);
    tNode->left = buildTree(in, pre, inStrt, inIndex - 1);
    tNode->right = buildTree(in, pre, inIndex + 1, inEnd);
    return tNode;
}

int search(int arr[], int strt, int end, int value) {
    int i;
    for (i = strt; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return i;
}

void printPostorder(Node* node) {
    if (node == NULL)
        return;
    printPostorder(node->left);
    printPostorder(node->right);
    printf("%d ", node->data);
}

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

bool isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, Node* node) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->array[++stack->top] = node;
}

Node* pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack underflow\n");
        return NULL;
    }
    return stack->array[stack->top--];
}

void zigzagTraversal(Node* root) {
    if (root == NULL)
        return;

    Stack* currentLevel = createStack();
    Stack* nextLevel = createStack();

    push(currentLevel, root);
    bool leftToRight = true;

    while (!isStackEmpty(currentLevel)) {
        Node* temp = pop(currentLevel);
        printf("%d ", temp->data);

        if (leftToRight) {
            if (temp->left)
                push(nextLevel, temp->left);
            if (temp->right)
                push(nextLevel, temp->right);
        } else {
            if (temp->right)
                push(nextLevel, temp->right);
            if (temp->left)
                push(nextLevel, temp->left);
        }

        if (isStackEmpty(currentLevel)) {
            leftToRight = !leftToRight;
            Stack* temp = currentLevel;
            currentLevel = nextLevel;
            nextLevel = temp;
        }
    }
}

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (Node**)malloc(queue->capacity * sizeof(Node*));
    return queue;
}

bool isQueueEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, Node* item) {
    if (queue->size == queue->capacity)
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

Node* dequeue(Queue* queue) {
    if (isQueueEmpty(queue))
        return NULL;
    Node* item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

void levelMax(Node* root) {
    if (root == NULL)
        return;

    Queue* queue = createQueue(MAX_SIZE);
    enqueue(queue, root);

    while (!isQueueEmpty(queue)) {
        int nodeCount = queue->size;
        int max = INT_MIN;

        while (nodeCount > 0) {
            Node* node = dequeue(queue);
            if (node->data > max)
                max = node->data;

            if (node->left != NULL)
                enqueue(queue, node->left);
            if (node->right != NULL)
                enqueue(queue, node->right);

            nodeCount--;
        }

        printf("%d ", max);
    }
}

int height(Node* node) {
    if (node == NULL)
        return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return max(leftHeight, rightHeight) + 1;
}

int diameter(Node* root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    int leftDiameter = diameter(root->left);
    int rightDiameter = diameter(root->right);

    int maxDiameter = max(leftDiameter, rightDiameter);

    return max(maxDiameter, leftHeight + rightHeight + 1);
}

int leftLeafSum(Node* root) {
    if (root == NULL)
        return 0;

    int sum = 0;
    if (root->left != NULL) {
        if (root->left->left == NULL && root->left->right == NULL)
            sum += root->left->data;
        else
            sum += leftLeafSum(root->left);
    }

    if (root->right != NULL)
        sum += leftLeafSum(root->right);

    return sum;
}
