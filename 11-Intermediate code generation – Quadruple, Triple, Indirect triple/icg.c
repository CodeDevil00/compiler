#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char prefix_string[MAX], infix_string[MAX], postfix_string[MAX];
int top;
char stack[MAX];

void push(char symbol);
char pop();
int isEmpty();
int precedence(char symbol);
int isOperator(char symbol);
void reverse_string(char *str);
void infix_to_postfix();
void infix_to_prefix();

int main() {
    int i, length;

    top = -1;

    printf("\nEnter an Expression in Infix format:\t");
    fgets(infix_string, MAX, stdin);
    infix_string[strcspn(infix_string, "\n")] = 0;  // Remove trailing newline

    infix_to_postfix();
    printf("\nExpression in Postfix Format:\t%s\n", postfix_string);

    reverse_string(infix_string);

    // Replace '(' with ')' and vice versa
    for (i = 0; i < strlen(infix_string); i++) {
        if (infix_string[i] == '(')
            infix_string[i] = ')';
        else if (infix_string[i] == ')')
            infix_string[i] = '(';
    }

    infix_to_postfix();  // Reuse same function
    reverse_string(postfix_string);
    strcpy(prefix_string, postfix_string);

    length = strlen(prefix_string);
    printf("\nExpression in Prefix Format:\t");
    for (i = 0; i < length; i++)
        if (prefix_string[i] != '(' && prefix_string[i] != ')')
            printf("%c", prefix_string[i]);

    printf("\n");
    return 0;
}

void infix_to_postfix() {
    int count, temp = 0;
    char symbol, next;

    top = -1;
    memset(postfix_string, 0, sizeof(postfix_string));

    for (count = 0; count < strlen(infix_string); count++) {
        symbol = infix_string[count];
        if (isspace(symbol))
            continue;

        if (!isOperator(symbol) && symbol != '(' && symbol != ')') {
            postfix_string[temp++] = symbol;
        } else {
            switch (symbol) {
                case '(':
                    push(symbol);
                    break;
                case ')':
                    while ((next = pop()) != '(')
                        postfix_string[temp++] = next;
                    break;
                default:
                    while (!isEmpty() && precedence(stack[top]) >= precedence(symbol))
                        postfix_string[temp++] = pop();
                    push(symbol);
                    break;
            }
        }
    }

    while (!isEmpty())
        postfix_string[temp++] = pop();

    postfix_string[temp] = '\0';
}

void reverse_string(char *str) {
    int i, j;
    char temp;
    int len = strlen(str);
    for (i = 0, j = len - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int precedence(char symbol) {
    switch (symbol) {
        case '+':
        case '-': return 1;
        case '*':
        case '/':
        case '%': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int isOperator(char symbol) {
    return symbol == '+' || symbol == '-' || symbol == '*' ||
           symbol == '/' || symbol == '%' || symbol == '^';
}

void push(char symbol) {
    if (top >= MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    stack[++top] = symbol;
}

char pop() {
    if (isEmpty()) {
        printf("Stack is Empty\n");
        exit(1);
    }
    return stack[top--];
}

int isEmpty() {
    return top == -1;
}
