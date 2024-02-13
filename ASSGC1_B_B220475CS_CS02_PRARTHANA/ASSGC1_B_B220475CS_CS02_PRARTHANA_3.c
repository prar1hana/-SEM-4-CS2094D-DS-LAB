#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node* left, *right;
} Node;

Node* newNode(int item) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

Node* insert(Node* node, int key) {
    if (node == NULL) return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}

Node* buildTreeFromParenthesis(char* str, int* start, int len) {
    if (*start >= len) return NULL;
    Node* node = NULL;

    int num = 0;
    while (*start < len && str[*start] != '(' && str[*start] != ')') {
        num = num * 10 + (str[*start] - '0');
        (*start)++;
    }
    node = newNode(num);

    if (*start < len && str[*start] == '(') {
        (*start)++;
        node->left = buildTreeFromParenthesis(str, start, len);
        if (*start < len && str[*start] == ')')
            (*start)++;
    }

    if (*start < len && str[*start] == '(') {
        (*start)++;
        node->right = buildTreeFromParenthesis(str, start, len);
        if (*start < len && str[*start] == ')')
            (*start)++;
    }

    return node;
}

void PrintRangeValues(Node* node, int k1, int k2) {
    if (node == NULL) return;
    if (k1 < node->key)
        PrintRangeValues(node->left, k1, k2);
    if (k1 <= node->key && k2 >= node->key)
        printf("%d ", node->key);
    if (k2 > node->key)
        PrintRangeValues(node->right, k1, k2);
}

int printAncestors(Node* root, int target) {
    if (root == NULL) return 0;
    if (root->key == target || printAncestors(root->left, target) || printAncestors(root->right, target)) {
        printf("%d ", root->key);
        return 1;
    }
    return 0;
}

int main() {
    Node* root = NULL;
    char str[100];
    scanf("%s", str);

    int start = 0;
    root = buildTreeFromParenthesis(str, &start, strlen(str));

    char command;
    int k1, k2;
    while (1) {
        scanf(" %c", &command);
        switch (command) {
            case 'p':
                scanf("%d %d", &k1, &k2);
                PrintRangeValues(root, k1, k2);
                printf("\n");
                break;
            case 'a':
                scanf("%d", &k1);
                if (!printAncestors(root, k1)) {
                    printf("Node not present.\n");
                }
                else {
                    printf("\n");
                }
                break;
            case 'e':
                exit(0);
        }
    }
    return 0;
}
