#include <stdio.h>
#include <string.h>
int main()
{
    int i, j, n, k;
    int lrec = 0;
    char prod[100];
    char newprod1[100] = "";
    char newprod2[100] = "";
    char alpha[100] = "";
    char beta[100] = "";
    char sts[20] = "";
    scanf("%s", prod);
    sts[0] = prod[0]; // sts is Start Symbol
    int size = (int)(strlen(prod));
    for (i = 0; i < size; i++)
    {
        if (prod[i] == '|')
        {
            k = i;
        }
    }
    if (prod[3] == prod[0]) // E->E+T

    {
        lrec = 1;
    }
    if (lrec == 1)
    {
        int c = 0;
        k = k - 1;
        for (i = 4; i <= k; i++)
        {
            alpha[c] = prod[i];
            c++;
        }
        c = 0;
        for (i = k + 2; i < size; i++)
        {
            beta[c] = prod[i];
            c++;
        }
        strcat(newprod1, sts);                  //-,E //printf(strcat(newprod1,sts));
        strcat(newprod1, "->");                 //->
        strcat(newprod1, beta);                 // T
        strcat(newprod1, sts);                  // E
        strcat(newprod1, "'");                  // E'
        strcat(newprod2, sts);                  // E
        strcat(newprod2, "'");                  // E'
        strcat(newprod2, "->");                 //->
        strcat(newprod2, alpha);                //+T
        strcat(newprod2, sts);                  // E
        strcat(newprod2, "'");                  //'
        strcat(newprod2, "|e");                 //|e
        printf("\n%s\n%s", newprod1, newprod2); // E->TE' }
    }
}