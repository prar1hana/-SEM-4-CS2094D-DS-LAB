#include <stdio.h>
#include <stdlib.h>
/*5
Sample Input 2:
7
i 1
i 2
i 3
i 4
i 5
i 12
p 5
u 12 25
p 5
u 12 25
u 5 25
d 25
s 12
i 5
e
Sample Output 2:
5 12
5 2
5
-1
-1
4 2
-1
-1
*/

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int hashFunction(int key, int tableSize) {
    return key % tableSize;
}

void insert(Node** hashTable, int key, int tableSize) {
    int hashIndex = hashFunction(key, tableSize);
    Node* newNode = createNode(key);
    Node* temp = hashTable[hashIndex];

    // Check if key is already present in the hash table
    for (int i = 0; i < tableSize; i++) {
        Node* temp = hashTable[i];
        while (temp != NULL) {
            if (temp->data == key) {
                printf("-1\n");
                return;
            }
            temp = temp->next;
        }
    }

    // Insert key into the hash table
    if (temp == NULL) {
        hashTable[hashIndex] = newNode;
        return;
    }

    Node* prev = NULL;
    while (temp != NULL && temp->data < key) {
        prev = temp;
        temp = temp->next;
    }

    if (prev == NULL) {
        newNode->next = hashTable[hashIndex];
        hashTable[hashIndex] = newNode;
    } else {
        newNode->next = prev->next;
        prev->next = newNode;
    }
}
void search(Node** hashTable, int key, int tableSize) {
    int hashIndex = hashFunction(key, tableSize);
    Node* temp = hashTable[hashIndex];
    int pos = 1;

    while (temp != NULL) {
        if (temp->data == key) {
            printf("%d %d\n", hashIndex, pos);
            return;
        }
        temp = temp->next;
        pos++;
    }

    printf("-1\n");
}

void delete(Node** hashTable, int key, int tableSize) {
    int hashIndex = hashFunction(key, tableSize);
    Node* temp = hashTable[hashIndex];
    Node* prev = NULL;
    int pos = 1;

    while (temp != NULL) {
        if (temp->data == key) {
            if (prev == NULL) {
                hashTable[hashIndex] = temp->next;
            } else {
                prev->next = temp->next;
            }
            printf("%d %d\n", hashIndex, pos);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
        pos++;
    }

    printf("-1\n");
}

void update(Node** hashTable, int oldKey, int newKey, int tableSize) {
    // Check if newKey is already present in the hash table
    for (int i = 0; i < tableSize; i++) {
        Node* temp = hashTable[i];
        while (temp != NULL) {
            if (temp->data == newKey) {
                printf("-1\n");
                return;
            }
            temp = temp->next;
        }
    }

    // If newKey is not present, delete oldKey and insert newKey
    delete(hashTable, oldKey, tableSize);
    insert(hashTable, newKey, tableSize);
}

void printElementsInChain(Node** hashTable, int index) {
    Node* temp = hashTable[index];

    if (temp == NULL) {
        printf("-1\n");
        return;
    }

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int main() {
    int tableSize;
    scanf("%d", &tableSize);

    Node** hashTable = (Node**)calloc(tableSize, sizeof(Node));

    char operation;
    while (scanf(" %c", &operation) == 1) {
        if (operation == 'e') {
            break;
        }

        int key, oldKey, newKey, index;
        switch (operation) {
            case 'i':
                scanf("%d", &key);
                insert(hashTable, key, tableSize);
                break;
            case 'd':
                scanf("%d", &key);
                delete(hashTable, key, tableSize);
                break;
            case 'u':
                scanf("%d %d", &oldKey, &newKey);
                update(hashTable, oldKey, newKey, tableSize);
                break;
            case 's':
                scanf("%d", &key);
                search(hashTable, key, tableSize);
                break;
            case 'p':
                scanf("%d", &index);
                printElementsInChain(hashTable, index);
                break;
        }
    }

    for (int i = 0; i < tableSize; i++) {
        Node* temp = hashTable[i];
        while (temp != NULL) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }

    free(hashTable);

    return 0;
}