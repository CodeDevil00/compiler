#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int k = 0, z = 0, i = 0, j = 0, c = 0;
char a[16], ac[20], stk[20], act[20];

void check();

int main() {
    printf("GRAMMAR is:\nE -> E+E\nE -> E*E\nE -> (E)\nE -> id\n");
    printf("Enter input string: ");
    fgets(a, sizeof(a), stdin);
    a[strcspn(a, "\n")] = '\0'; // remove newline

    c = strlen(a);
    strcpy(act, "SHIFT->");
    printf("Stack\t\tInput\t\tAction\n");

    while (j < c) {
        if (a[j] == 'i' && a[j + 1] == 'd') {
            stk[i++] = a[j];
            stk[i++] = a[j + 1];
            stk[i] = '\0';
            j += 2;
            printf("$%s\t\t%s$\t%sid\n", stk, a + j, act);
            check();
        } else {
            stk[i++] = a[j];
            stk[i] = '\0';
            j++;
            printf("$%s\t\t%s$\t%ssymbol\n", stk, a + j, act);
            check();
        }
    }

    return 0;
}

void check() {
    int reduced;
    do {
        reduced = 0;
        strcpy(ac, "REDUCE TO E");

        // Reduce id to E
        for (z = 0; z < i - 1; z++) {
            if (stk[z] == 'i' && stk[z + 1] == 'd') {
                stk[z] = 'E';
                memmove(&stk[z + 1], &stk[z + 2], strlen(&stk[z + 2]) + 1);
                i -= 1;
                printf("$%s\t\t%s$\t%s\n", stk, a + j, ac);
                reduced = 1;
                break;
            }
        }

        // Reduce E+E to E
        for (z = 0; z < i - 2; z++) {
            if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E') {
                stk[z] = 'E';
                memmove(&stk[z + 1], &stk[z + 3], strlen(&stk[z + 3]) + 1);
                i -= 2;
                printf("$%s\t\t%s$\t%s\n", stk, a + j, ac);
                reduced = 1;
                break;
            }
        }

        // Reduce E*E to E
        for (z = 0; z < i - 2; z++) {
            if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
                stk[z] = 'E';
                memmove(&stk[z + 1], &stk[z + 3], strlen(&stk[z + 3]) + 1);
                i -= 2;
                printf("$%s\t\t%s$\t%s\n", stk, a + j, ac);
                reduced = 1;
                break;
            }
        }

        // Reduce (E) to E
        for (z = 0; z < i - 2; z++) {
            if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')') {
                stk[z] = 'E';
                memmove(&stk[z + 1], &stk[z + 3], strlen(&stk[z + 3]) + 1);
                i -= 2;
                printf("$%s\t\t%s$\t%s\n", stk, a + j, ac);
                reduced = 1;
                break;
            }
        }

    } while (reduced);
}
