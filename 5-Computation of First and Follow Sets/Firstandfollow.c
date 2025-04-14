#include <stdio.h>
#include <string.h>
#include <ctype.h> // To use isupper() and islower()

int n, m = 0, p, i = 0, j = 0;
char a[10][10], f[10];

void follow(char c);
void first(char c);

int main()
{
    int i, z;
    char c, ch;

// Clear screen (alternative to clrscr)
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf("Enter the number of productions:\n");
    scanf("%d", &n);
    printf("Enter the productions:\n");
    for (i = 0; i < n; i++)
        scanf("%s%c", a[i], &ch); // Read each production

    do
    {
        m = 0;
        printf("Enter the element whose first & follow is to be found: ");
        scanf(" %c", &c); // Space before %c to consume any leftover newline
        first(c);
        printf("First(%c)={", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");

        strcpy(f, " "); // Clear the array
        m = 0;
        follow(c);
        printf("Follow(%c)={", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");

        printf("Continue (0/1)? ");
        scanf("%d", &z);
    } while (z == 1);

    return 0;
}

void first(char c)
{
    int k;
    if (!isupper(c)) // Check if the character is not an uppercase letter
        f[m++] = c;  // If it's a terminal, add to the first set

    for (k = 0; k < n; k++)
    {
        if (a[k][0] == c)
        {                       // Check productions for the non-terminal
            if (a[k][2] == '$') // If production is empty, find follow
                follow(a[k][0]);
            else if (islower(a[k][2])) // If the second character is terminal
                f[m++] = a[k][2];
            else // Otherwise, find the first of the next non-terminal
                first(a[k][2]);
        }
    }
}

void follow(char c)
{
    if (a[0][0] == c) // If the starting symbol is the non-terminal
        f[m++] = '$'; // Add $ to the follow set

    for (i = 0; i < n; i++)
    {
        for (j = 2; j < strlen(a[i]); j++)
        {
            if (a[i][j] == c)
            {                                            // If the non-terminal is found in the production
                if (a[i][j + 1] != '\0')                 // If it's not the last character
                    first(a[i][j + 1]);                  // Add first of the next symbol
                if (a[i][j + 1] == '\0' && c != a[i][0]) // If it's the last character, follow the LHS
                    follow(a[i][0]);
            }
        }
    }
}
