#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};

typedef struct Node *node;

int lr = 0;
int rr = 0;

int maxm(int a, int b)
{
    return (a > b) ? a : b;
}

int height(node T)
{
    if (T == NULL)
        return 0;
    return T->height;
}
int getBalance(node T) 
{ 
    if (T == NULL) 
        return 0; 
    return height(T->left) - height(T->right); 
} 

node left_rotate(node T)
{
    node trl = T->right->left;
    node tr = T->right;
    
    T->right = trl;
    tr->left = T;
    //T = tr;
    T->height = 1 + maxm(height(T->left), height(T->right));
    tr->left->height = 1 + maxm(height(tr->left->left), height(tr->left->right));
    //T->left->height = 1 + maxm(height(T->left->left), height(T->left->right));
    lr += 1;
    return tr;
}

node right_rotate(node T)
{   
    node tl = T->left;
    node tlr = tl->right;
    
    T->left = tlr;
    tl->right = T;
    //T = tl;
    T->height = 1 + maxm(height(T->left), height(T->right));
    tl->right->height = 1 + maxm(height(tl->right->left), height(tl->right->right));
    //T->right->height = 1 + maxm(height(T->right->left), height(T->right->right));
    rr += 1;
    return tl;
}

int is_present(node T, int key)
{
    if (T == NULL)
        return -1;
    else if (T->data > key)
        return is_present(T->left, key);
    else if (T->data < key)
        return is_present(T->right, key);
    else
        return 1;
}

void avl_find(node T, int key)
{
    int p = is_present(T, key);
    if (p == -1)
    {
        printf("-1\n");
        return;
    }
    else
    {
        while (T->data != key)
        {
            if (T->data > key)
            {
                printf("%d ", T->data);
                T = T->left;
            }
            else if (T->data < key)
            {
                printf("%d ", T->data);
                T = T->right;
            }
        }
        printf("%d\n", T->data);
    }
    return;
}

node avl_insert(node T, int key)
{
    if (T == NULL)
    {
        T = (node)malloc(sizeof(struct Node));
        T->data = key;
        T->left = NULL;
        T->right = NULL;
        T->height = 1;
        return T;
    }
    
    else if (T->data > key)
        T->left = avl_insert(T->left, key);
    else if (T->data < key)
        T->right = avl_insert(T->right, key);
    else //key already exists
        return T;

    T->height = 1 + maxm(height(T->left), height(T->right));

    int balance = getBalance(T); 
    
    //LL
    if (balance < -1 && key > T->right->data)
        T = left_rotate(T);

    //RR
    else if (balance > 1 && key < T->left->data)
        T = right_rotate(T);

    //LR
    if (balance > 1 && key > T->left->data)
    {
        T->left = left_rotate(T->left);
        return right_rotate(T);
    }

    //RL
    if (balance < -1 && key < T->right->data)
    {
        T->right = right_rotate(T->right);
        return left_rotate(T);
    }

    return T;
}

void avl_preorder(node T)
{
    if (T != NULL)
    {
        printf("%d ", T->data);
        avl_preorder(T->left);
        avl_preorder(T->right);
    }
    else
        return;
}

void avl_cal(node T)
{
    printf("%d %d\n", lr, rr);
}

int main()
{
    node T = NULL;
    int key;
    char option;

    do
    {
        scanf(" %c", &option);

        switch (option)
        {
            case 'i':
                scanf("%d", &key);
                T = avl_insert(T, key);
                break;
    
            case 'x':
                scanf("%d", &key);
                avl_find(T, key);
                break;
    
            case 'p':
                avl_preorder(T);
                printf("\n");
                break;
    
            case 's':
                avl_cal(T);
                break;
    
            case 'e':
                exit(0);
    
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }
    while (1);

    return 0;
}