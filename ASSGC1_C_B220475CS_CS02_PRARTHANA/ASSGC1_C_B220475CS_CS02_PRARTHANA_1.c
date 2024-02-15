#include <stdio.h>
#include <stdlib.h>
/*5 6
1 2 3 4 5
2 5 1 6 7 8
u A B
u B A
i A B
i B A
s A B
s B A
e

1 2 3 4 5 6 7 8
2 5 1 6 7 8 3 4
1 2 5
2 5 1
3 4
6 7 8
*/
#define MAX 200

int hashTable[MAX] = {0};  // Initialize hashTable array with zeros.

// Function to insert a key into the hash table using linear probing.
void insert(int key) {
    int index = key % MAX;
    while (hashTable[index]) {
        index = (index + 1) % MAX;  // Move to the next index if the current one is occupied.
    }
    hashTable[index] = key;  // Insert the key into the hash table.
}

// Function to search for a key in the hash table and return its index if found, -1 otherwise.
int search(int key) {
    int index = key % MAX;
    while (hashTable[index]) {
        if (hashTable[index] == key) {
            return index;  // Key found at this index.
        }
        index = (index + 1) % MAX;  // Move to the next index if the current one is occupied.
    }
    return -1;  // Key not found.
}

// Function to perform union of two arrays and print the result.
void unionArrays(int A[], int B[], int m, int n) {
    int printed = 0;
    for (int i = 0; i < m; i++) {
        if (search(A[i]) == -1) {
            insert(A[i]);
            printf("%d ", A[i]);
            printed = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        if (search(B[i]) == -1) {
            insert(B[i]);
            printf("%d ", B[i]);
            printed = 1;
        }
    }
    if (!printed) printf("-1");  // If no elements were printed, print -1.
    printf("\n");
}

// Function to perform intersection of two arrays and print the result.
void intersectionArrays(int B[], int A[], int n, int m) {
    int printed = 0;
    for (int i = 0; i < m; i++) {
        if (search(A[i]) == -1)  // Only insert if the element doesn't already exist in the hash table.
                insert(A[i]);
    }
    
    for (int i = 0; i < n; i++) {
        if (search(B[i]) != -1) {
            printf("%d ", B[i]);
            hashTable[search(B[i])] = 0;  // Mark the element as processed.
            printed = 1;
        }
    }
    if (!printed) printf("-1");  // If no elements were printed, print -1.
    printf("\n");
}

// Function to perform set difference of two arrays and print the result.
void setDifference(int A[], int B[], int m, int n) {
    int printed = 0;
    for (int i = 0; i < n; i++) {
        insert(B[i]);
    }
    for (int i = 0; i < m; i++) {
        if (search(A[i]) == -1) {
            printf("%d ", A[i]);
            printed = 1;
        }
    }
    if (!printed) printf("-1");  // If no elements were printed, print -1.
    printf("\n");
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int A[m], B[n];
    for (int i = 0; i < m; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }
    char operation;
    char array1, array2;
    while (scanf(" %c", &operation) == 1) {
        if (operation == 'e') {
            break;  // Exit the loop if 'e' is encountered.
        }
        scanf(" %c %c", &array1, &array2);
        if (operation == 'u') {
            if (array1 == 'A' && array2 == 'B') {
                unionArrays(A, B, m, n);
            } else {
                unionArrays(B, A, n, m);
            }
        } else if (operation == 'i') {
            if (array1 == 'A' && array2 == 'B') {
                intersectionArrays(A, B, m, n);
            } else {
                intersectionArrays(B, A, n, m);
            }
        } else if (operation == 's') {
            if (array1 == 'A' && array2 == 'B') {
                setDifference(A, B, m, n);
            } else {
                setDifference(B, A, n, m);
            }
        }
        // Clear the hashTable for the next operation.
        for (int i = 0; i < MAX; i++) {
            hashTable[i] = 0;
        }
    }
    return 1;
}
