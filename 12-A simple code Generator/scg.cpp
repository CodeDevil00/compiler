#include <iostream>
#include <cstring>
using namespace std;

char reg[10][3] = {"R0", "R1", "R2", "R3", "R4", "R5"};
char stmt[10][10], code[50];
int output[15], nostmt = 0;

void icode(const char *op, const char *source, const char *dest, int out) {
    strcpy(code, "");  // Clear code buffer
    strcat(code, op);
    strcat(code, " ");
    strcat(code, source);
    strcat(code, " ");
    strcat(code, dest);
    output[nostmt] = out;
    cout << code << endl;
}

int main() {
    cout << "Enter the statements (END to end):\n";
    while (true) {
        cin >> stmt[nostmt];
        if (strcmp(stmt[nostmt], "END") == 0) break;
        nostmt++;
    }

    cout << "\nTHE INTERMEDIATE CODE IS:\n\n";

    for (int i = 0; i < nostmt; i++) {
        int rs = -1, rd = -1;

        // Find the registers for operands if already computed
        for (int j = 0; j < i; j++) {
            if (stmt[j][0] == stmt[i][2]) rs = output[j];
            if (stmt[j][0] == stmt[i][4]) rd = output[j];
        }

        // Load source operand into register if not already
        if (rs == -1) {
            char temp[2] = {stmt[i][2], '\0'};
            icode("MOV", temp, reg[i], i);
            rs = i;
        }

        // Load destination operand into register if not already
        if (rd == -1) {
            char temp[2] = {stmt[i][4], '\0'};
            icode("MOV", temp, reg[i + 1], i + 1);
            rd = i + 1;
        }

        // Perform the operation
        const char *op = "";
        switch (stmt[i][3]) {
            case '+': op = "ADD"; break;
            case '-': op = "SUB"; break;
            case '*': op = "MUL"; break;
            case '/': op = "DIV"; break;
        }

        icode(op, reg[rd], reg[rs], rs);

        // Move result into final destination variable
        char result[2] = {stmt[i][0], '\0'};
        icode("MOV", reg[rs], result, 0);
    }

    return 0;
}
