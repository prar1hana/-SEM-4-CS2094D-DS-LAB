#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stack[100];
int itop;

void push(char op) {
    stack[itop] = op;
    itop++;
}

void pop() {
    if (itop > 0) {
        itop--;
    }
}

int main() {
    int n, ans = 0;

    scanf("%d", &n);

    if (n <= 0) {
        return 1;
    }

    char *str = (char *)malloc((n + 1) * sizeof(char));

    if (str == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    scanf("%s", str);

    if (strlen(str) != n) {
        printf("Error: Entered string length does not match specified size\n");
        free(str);
        return 1;
    }

    itop = 0;

    for (int i = 0; i < n; i++) {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '%' || str[i] == '/' || str[i] == '^' || str[i] == '(')
            push(str[i]);

        else if (str[i] == ')') {

            if (itop > 0 && stack[itop - 1] == '(') {
                ans = 1;
                printf("%d", ans);
                free(str);
                return 1;
            }

            while (itop > 0 && stack[itop - 1] != '(')
                pop();

            pop();
        }
    }

    if (itop > 0) {
        ans = 0;
    }

    printf("%d", ans);

    free(str);

    return 1;
}
