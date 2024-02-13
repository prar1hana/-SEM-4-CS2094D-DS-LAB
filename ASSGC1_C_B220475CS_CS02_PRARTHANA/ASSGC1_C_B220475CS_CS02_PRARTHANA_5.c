#include <stdio.h>
/*Sample Input 1:
10 4
2 8 2 3 4 5 5 6 5 2
Sample Output 1:
3 4 4 3 3 2 3*/

// Define maximum array size
#define MAX_SIZE 2000000

// Global array to store frequency of elements
int freqArray[MAX_SIZE] = {0};

int main() {
    // Input variables for total elements and window size
    int totalElements, windowSize;
    scanf("%d %d", &totalElements, &windowSize);

    // Array to store the input elements
    int elementList[totalElements];
    
    // Input loop to read elements
    for (int i = 0; i < totalElements; i++) {
        scanf("%d", &elementList[i]);
    }

    // Variables to track unique elements in the current window
    int uniqueCount = 0;

    // Processing the initial window
    for (int i = 0; i < windowSize; i++) {
        if (freqArray[elementList[i]] == 0) {
            // Increment unique count if the element is encountered for the first time
            uniqueCount++;
        }
        freqArray[elementList[i]]++;
    }

    // Print the count of unique elements in the initial window
    printf("%d ", uniqueCount);

    // Processing subsequent windows
    for (int i = 1; i + windowSize - 1 < totalElements; i++) {
        if (freqArray[elementList[i - 1]] == 1) {
            // Decrement unique count if the outgoing element from the window is unique
            uniqueCount--;
        }

        if (freqArray[elementList[i + windowSize - 1]] == 0) {
            // Increment unique count if the incoming element to the window is unique
            uniqueCount++;
        }

        // Update frequency array for the outgoing and incoming elements
        freqArray[elementList[i - 1]]--;
        freqArray[elementList[i + windowSize - 1]]++;

        // Print the count of unique elements in the current window
        printf("%d ", uniqueCount);
    }

    // Print a newline at the end
    printf("\n");

    return 0;
}
