#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAX_PRODUCTIONS 10
#define MAX_LENGTH 20

// Arrays to store the productions, first and follow sets
char st[MAX_PRODUCTIONS][MAX_LENGTH], ft[MAX_PRODUCTIONS][MAX_LENGTH], fol[MAX_PRODUCTIONS][MAX_LENGTH];

// Function declarations
void findFirst(int n);
void findFollow(int n);
void computeFirst(int i, int j, int n);
void computeFollow(int i, int j, int n);
int isInFollow(char* followSet, char ch);

int main() {
    int n, i, j, z;
    char c;

    printf("Enter the number of productions:\n");
    scanf("%d", &n);
    printf("Enter the productions in a grammar (@ for epsilon):\n");

    // Input productions
    for (i = 0; i < n; i++) {
        scanf("%s", st[i]);
    }

    // Initialize follow sets to empty strings
    for (i = 0; i < n; i++) {
        fol[i][0] = '\0';
    }

    // Compute First and Follow sets
    findFirst(n);
    findFollow(n);

    // Print First sets
    printf("first pos\n");
    for (i = 0; i < n; i++) {
        printf("FIRS[%c]=%s\n", st[i][0], ft[i]);
    }

    // Print Follow sets
    printf("follow pos\n");
    for (i = 0; i < n; i++) {
        printf("FOLLOW[%c]=%s\n", st[i][0], fol[i]);
    }

    // Simulate M[i,j] table output (M matrix)
    printf("\n");
    for (i = 0; i < n; i++) {
        int j = 3; // Start at the right-hand side of the production
        while (st[i][j] != '\0') {
            if ((st[i][j - 1] == '|') || (j == 3)) {
                char fin[MAX_LENGTH];
                int t = j;
                for (int p = 0; p <= 2; p++) {
                    fin[p] = st[i][p];
                }
                for (int p = 3; ((st[i][j] != '|') && (st[i][j] != '\0')); p++) {
                    fin[p] = st[i][j];
                    j++;
                }
                fin[j] = '\0';

                if (st[i][t] == '@') {
                    int a = 0, b = 0;
                    while (st[a][0] != st[i][0]) a++; // Find the production for the non-terminal
                    while (fol[a][b] != '\0') {
                        printf("M[%c,%c]=%s\n", st[i][0], fol[a][b], fin);
                        b++;
                    }
                } else if (!(isupper(st[i][t]))) {
                    printf("M[%c,%c]=%s\n", st[i][0], st[i][t], fin);
                } else {
                    int a = 0, b = 0;
                    while (st[a][0] != st[i][3]) a++; // Find the production for the non-terminal
                    while (ft[a][b] != '\0') {
                        printf("M[%c,%c]=%s\n", st[i][0], ft[a][b], fin);
                        b++;
                    }
                }
            }
            if (st[i][j] == '|') j++;
        }
    }

    return 0;
}

// Function to compute the First sets for each production
void findFirst(int n) {
    int i, j;
    // For each production, compute its First set
    for (i = 0; i < n; i++) {
        ft[i][0] = '\0'; // Initialize First set for the current production
        j = 3; // Start at the right-hand side of the production (after the arrow)

        while (st[i][j] != '\0') {
            if (islower(st[i][j])) { // Terminal character
                strncat(ft[i], &st[i][j], 1);
                break;
            } else if (isupper(st[i][j])) { // Non-terminal character
                computeFirst(i, j, n);
                break;
            } else if (st[i][j] == '@') { // Epsilon (empty string)
                strncat(ft[i], "@", 1);
                break;
            }
            j++;
        }
    }
}

// Helper function to compute the First set of a non-terminal
void computeFirst(int i, int j, int n) {
    int k, m;

    for (k = 0; k < n; k++) {
        if (st[k][0] == st[i][j]) {
            j = 3; // Start of the right-hand side of the production
            while (st[k][j] != '\0') {
                if (islower(st[k][j])) {
                    strncat(ft[i], &st[k][j], 1);
                    return;
                } else if (isupper(st[k][j])) {
                    computeFirst(k, j, n);
                    return;
                } else if (st[k][j] == '@') {
                    strncat(ft[i], "@", 1);
                    return;
                }
                j++;
            }
        }
    }
}

// Function to compute the Follow sets for each non-terminal
void findFollow(int n) {
    int i, j, k;

    // For Follow(A) of the starting symbol, add $ (end-of-input)
    fol[0][0] = '$';
    for (i = 0; i < n; i++) {
        j = 3; // Start of the right-hand side of the production
        while (st[i][j] != '\0') {
            if (isupper(st[i][j])) {
                computeFollow(i, j, n);
            }
            j++;
        }
    }
}

// Helper function to check if a character is already in the follow set
int isInFollow(char* followSet, char ch) {
    int i = 0;
    while (followSet[i] != '\0') {
        if (followSet[i] == ch) {
            return 1;
        }
        i++;
    }
    return 0;
}

// Function to compute the Follow set of a non-terminal
void computeFollow(int i, int j, int n) {
    int k, m, t;

    // For each production, we check if the current non-terminal is found
    // If so, we need to add follow sets accordingly.
    for (k = 0; k < n; k++) {
        for (t = 3; t < strlen(st[k]); t++) {
            if (st[k][t] == st[i][0]) { // Check if the non-terminal is in the production
                // If the next symbol is not a terminal or if it is epsilon
                if (st[k][t + 1] != '\0' && st[k][t + 1] != '|') {
                    computeFirst(k, t + 1, n); // Add the first of the next symbol
                } else if (st[k][t + 1] == '\0' && st[k][t] == st[i][0]) {
                    // If the production is the last one, propagate the follow set
                    computeFollow(k, t, n);
                }
            }
        }
    }
}
