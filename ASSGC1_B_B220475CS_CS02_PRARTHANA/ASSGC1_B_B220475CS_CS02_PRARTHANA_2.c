#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct BSTInfo {
    int size;
    int min;
    int max;
    int sum;
    int isBST;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct BSTInfo findMaxSumBSTHelper(struct Node* root) {
    if (root == NULL) {
        struct BSTInfo result = {0, INT_MAX, INT_MIN, 0, 1};
        return result;
    }

    struct BSTInfo left = findMaxSumBSTHelper(root->left);
    struct BSTInfo right = findMaxSumBSTHelper(root->right);

    struct BSTInfo current;
    current.size = left.size + right.size + 1;

    if (left.isBST && right.isBST && root->data > left.max && root->data < right.min) {
        current.min = (root->left != NULL) ? left.min : root->data;
        current.max = (root->right != NULL) ? right.max : root->data;
        current.sum = root->data + left.sum + right.sum;
        current.isBST = 1;
    } else {
        current.min = 0;
        current.max = 0;
        current.sum = max(left.sum, right.sum);
        current.isBST = 0;
    }

    return current;
}

int findMaxSumBST(struct Node* root) {
    struct BSTInfo result = findMaxSumBSTHelper(root);
    return result.sum;
}

struct Node* buildTreeFromParenthesis(char str[], int* index) {
    if (str[*index] == '\0' || str[*index] == ')') {
        (*index)++;
        return NULL;
    }

    int num = 0;
    while (str[*index] >= '0' && str[*index] <= '9') {
        num = num * 10 + (str[*index] - '0');
        (*index)++;
    }

    struct Node* root = newNode(num);

    // If next character is '(', it means there are children
    if (str[*index] == '(') {
        (*index)++;
        root->left = buildTreeFromParenthesis(str, index);
        // Move to the next character after the left subtree
        (*index)++;
        if (str[*index] == '(') {
            (*index)++;
            root->right = buildTreeFromParenthesis(str, index);
            // Move to the next character after the right subtree
            (*index)++;
        }
    }

    return root;
}

void printLevelOrder(struct Node* root) {
    if (root == NULL)  return;
    struct Node** queue = (struct Node**)malloc(sizeof(struct Node*)*104);
    int rear = 0;
    int front = 0;
    queue[rear] = root;
    rear++;
    while (rear != front)
    {
        struct Node* tempNode = queue[front];
        printf("%d ", tempNode->data);
        front++;
        if (tempNode->left)
        {
            queue[rear] = tempNode->left;
            rear++;
        }
        if (tempNode->right)
        {
            queue[rear] = tempNode->right;
            rear++;
        }
    }
    printf("\n");
}


void printRightView(struct Node* root) {
    if (root == NULL)
        return;
    struct Node** queue = (struct Node**)malloc(sizeof(struct Node*)*104);
    int rear = 0;
    int front = 0;
    queue[rear] = root;
    rear++;
    while (rear != front)
    {
        int count = rear - front;
        while (count--)
        {
            struct Node* tempNode = queue[front];
            front++;
            if (count == 0)
                printf("%d ", tempNode->data);
            if (tempNode->left)
            {
                queue[rear] = tempNode->left;
                rear++;
            }
            if (tempNode->right)
            {
                queue[rear] = tempNode->right;
                rear++;
            }
        }
    }
    printf("\n");
}

int main() {
    char input[100];
    scanf("%s", input);

    int index = 0;
    struct Node* root = buildTreeFromParenthesis(input, &index);

    char command;
    while(1) {
        scanf(" %c", &command);
        switch(command) {
            case 'l':
                printLevelOrder(root);
                break;
            case 'm':
                printf("%d\n", findMaxSumBST(root));
                break;
            case 'r':
                printRightView(root);
                break;
            case 'e':
                exit(0);
        }
    }
    return 0;
}
