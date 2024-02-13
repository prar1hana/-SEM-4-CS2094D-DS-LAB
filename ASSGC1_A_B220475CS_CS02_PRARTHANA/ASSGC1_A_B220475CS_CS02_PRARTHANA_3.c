#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    char name[50];
    char admitTime[50];
    int priority;
    
} Patient;

typedef struct {
    Patient* p;
    int size;
    int capacity;
    
} PriorityQueue;

void initializePriorityQueue(PriorityQueue* pq, int capacity) {
    pq->p = (Patient*)malloc(capacity * sizeof(Patient));
    pq->capacity = capacity;
    pq->size = 0;
}

void swap(Patient* x, Patient*y) {
    Patient z = *x;
    *x = *y;
    *y = z;
}

int comparePatients(Patient* a, Patient* b) {
    if (a->priority > b->priority)
        return 1;
    else if (a->priority < b->priority)
        return -1;
    else
        return strcmp(b->admitTime, a->admitTime);
}

void heapify(PriorityQueue* pq, int i) {

    int L = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;

    if (left < pq->size && comparePatients(&pq->p[left], &pq->p[L]) > 0)
        L = left;

    if (right < pq->size && comparePatients(&pq->p[right], &pq->p[L]) > 0)
        L = right;

    if (L != i) {
        swap(&pq->p[i], &pq->p[L]);
        heapify(pq, L);
    }
}

void admit(PriorityQueue* pq, char* patientName, int patientPriority, char* admitTime) {
    if (pq->size == pq->capacity) {
        return;
    }

    Patient newPatient;
    strcpy(newPatient.name, patientName);
    newPatient.priority = patientPriority;
    strcpy(newPatient.admitTime, admitTime);

    pq->p[pq->size] = newPatient;
    int i = pq->size;
    pq->size++;

    while (i > 0 && comparePatients(&pq->p[i], &pq->p[(i - 1) / 2]) > 0) {
        swap(&pq->p[i], &pq->p[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void treatNextPatient(PriorityQueue* pq) {
    if (pq->size == 0) {
        return;
    }

    Patient nextPatient = pq->p[0];
    printf("%s %d %s\n", nextPatient.name, nextPatient.priority, nextPatient.admitTime);

    pq->p[0] = pq->p[pq->size - 1];
    pq->size--;

    heapify(pq, 0);
}

void CheckNextPatient(PriorityQueue* pq) {
    if (pq->size == 0) {
        return;
    }
    Patient nextPatient = pq->p[0];
    printf("%s %d %s\n", nextPatient.name, nextPatient.priority, nextPatient.admitTime);
}

void dischargePatient(PriorityQueue* pq, char* patientName, char* admitTime) {
    int i;
    for (i = 0; i < pq->size; i++) {
        if (strcmp(pq->p[i].name, patientName) == 0 && strcmp(pq->p[i].admitTime, admitTime) == 0)
            break;
    }

    if (i == pq->size) {
        return;
    }

    pq->p[i] = pq->p[pq->size - 1];
    
    pq->size--;

    heapify(pq, i);
}

void CHANGE(PriorityQueue* pq, char* patientName, char* admitTime, int newPriority) {
    int i;
    for (i = 0; i < pq->size; i++) {
        if (strcmp(pq->p[i].name, patientName) == 0 && strcmp(pq->p[i].admitTime, admitTime) == 0)
            break;
    }

    if (i == pq->size) {
        return;
    }

    pq->p[i].priority = newPriority;

    while (i > 0 && comparePatients(&pq->p[i], &pq->p[(i - 1) / 2]) > 0) {
        swap(&pq->p[i], &pq->p[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void print(PriorityQueue* pq) {
    if (pq->size == 0) {
        return;
    }

    PriorityQueue temp;
    initializePriorityQueue(&temp, pq->size);
    memcpy(temp.p, pq->p, pq->size * sizeof(Patient));
    temp.size = pq->size;

    for (int i = temp.size / 2 - 1; i >= 0; i--)
        heapify(&temp, i);

    for (int i = temp.size - 1; i >= 0; i--) {
        Patient patient = temp.p[0];
        printf("%s %d %s\n", patient.name, patient.priority, patient.admitTime);

        temp.p[0] = temp.p[i];
        temp.size--;

        heapify(&temp, 0);
    }

    free(temp.p);
}

int main() {
    PriorityQueue pq;
    initializePriorityQueue(&pq, 50);

    char option;
    char patientName[50];
    int patientPriority;
    char admitTime[50];
    int newPriority;

    while (option != 'e') 
    {
        scanf(" %c", &option);

        switch (option) {
            case 'a':
                scanf("%s %d %s", patientName, &patientPriority, admitTime);
                admit(&pq, patientName, patientPriority, admitTime);
                break;
            case 't':
                treatNextPatient(&pq);
                break;
            case 'c':
                CheckNextPatient(&pq);
                break;
            case 'u':
                scanf("%s %s %d", patientName, admitTime, &newPriority);
                CHANGE(&pq, patientName, admitTime, newPriority);
                break;
            case 'p':
                print(&pq);
                break;
            case 'e':
                break;
            case 'd':
                scanf("%s %s", patientName, admitTime);
                dischargePatient(&pq, patientName, admitTime);
                break;
                
            default:
                break;
        }
    }

    free(pq.p);

    return 0;
}
