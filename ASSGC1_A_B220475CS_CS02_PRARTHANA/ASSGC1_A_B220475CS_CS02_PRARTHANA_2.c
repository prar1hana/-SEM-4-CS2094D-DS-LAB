#include <stdio.h>
#include <stdlib.h>

struct L {
    int key;
    struct L* next;
};

typedef struct L* node;

void LIST_INSERT(node* L, node x) {
    if (*L == NULL) {
        *L = x;
    } else {
        node temp = *L;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = x;
    }
}

node CREATE_NODE(int k) {
    node newNode = (node)malloc(sizeof(struct L));
    newNode->key = k;
    newNode->next = NULL;
    return newNode;
}


void LIST_RDUPLICATE(node* L) {
    if (*L == NULL) {
        return;
    }

    int hash[100] = {0};
    node current = *L;
    node prev = NULL;

    while (current != NULL) 
    {
        if (hash[current->key] == 1) { //if we have found a duplicate
            
            if (prev == NULL) {
                // node at first is the duplicatee
                node temp = *L;
                *L = (*L)->next;
                free(temp);
                current = *L;
            } else {
                // the node at first isn't a duplicate
                prev->next = current->next;
                free(current);
                current = prev->next;
            }
        } else {
            //the number appeared for the first time
            hash[current->key] = 1;
            prev = current;
            current = current->next;
        }
    }
}
void LIST_DELETE(node* L, int i) {
    if (*L == NULL) {
        printf("-1\n");
        return;
    }
    if (i == 1) {
        node temp = *L;
        *L = (*L)->next;
        printf("%d\n", temp->key);
        free(temp);
        return;
    }

    node temp = *L;
    int count = 1;
    while (temp != NULL && count < i - 1) {
        temp = temp->next;
        count=count+1;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("-1\n");
        return;
    }
    node deletedNode = temp->next;
    temp->next = temp->next->next;
    printf("%d\n", deletedNode->key);
    free(deletedNode);
}
char LIST_PAL(node head) {
    node L = head;
    if (L == NULL) {
        return 'N';
    }

    int reverse[100];
    int n = 0;
    L = head;
    while (L != NULL) {
        reverse[n] = L->key;
        n++;
        L = L->next;
    }

    int i = 0;
    L = head;
    while (L != NULL) {
        if (L->key != reverse[n - i - 1])
            return 'N';
        i++;
        L = L->next;
    }

    return 'Y';
}

void LIST_DISPLAY(node L) {
    node temp = L;
    if(temp==NULL){
        printf("-1\n");
        return;}
    while (temp != NULL) {
        printf("%d ", temp->key);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    node L = NULL;
    char choice;
    int key, index;
    do {
        scanf(" %c", &choice);
        switch (choice) {
            case 'a':
                scanf("%d", &key);
                LIST_INSERT(&L, CREATE_NODE(key));
                break;
            
            case 'd':
                LIST_RDUPLICATE(&L);
                LIST_DISPLAY(L);
                break;
            
            case 'p':
                printf("%c\n", LIST_PAL(L));
                break;
                
            case 's':
                LIST_DISPLAY(L);
                break;
                
            case 'r':
                scanf("%d", &index);
                LIST_DELETE(&L, index);
                break;
            default:
                break;
        }
    } while (choice != 'e');
    return 1;
}
