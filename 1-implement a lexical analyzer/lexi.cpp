#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>

using namespace std;

// Define some common keywords and operators
unordered_set<string> keywords = {"if", "else", "while", "for", "int", "float", "char", "return"};
unordered_set<char> operators = {'+', '-', '*', '/', '=', '>', '<', '%'};
unordered_set<char> symbols = {';', ',', '(', ')', '{', '}'};

bool isKeyword(const string& word) {
    return keywords.find(word) != keywords.end();
}

bool isOperator(char ch) {
    return operators.find(ch) != operators.end();
}

bool isSymbol(char ch) {
    return symbols.find(ch) != symbols.end();
}

bool isConstant(const string& token) {
    for (char ch : token) {
        if (!isdigit(ch))
            return false;
    }
    return !token.empty();
}

void analyzeTokens(const string& input) {
    string token = "";

    for (size_t i = 0; i < input.length(); ++i) {
        char ch = input[i];

        // If space or delimiter found, analyze the current token
        if (isspace(ch) || isOperator(ch) || isSymbol(ch)) {
            if (!token.empty()) {
                if (isKeyword(token)) {
                    cout << token << " : Keyword\n";
                } else if (isConstant(token)) {
                    cout << token << " : Constant\n";
                } else if (isalpha(token[0])) {
                    cout << token << " : Identifier\n";
                } else {
                    cout << token << " : Unknown Token\n";
                }
                token.clear();
            }

            // Check for operator or symbol
            if (isOperator(ch)) {
                cout << ch << " : Operator\n";
            } else if (isSymbol(ch)) {
                cout << ch << " : Symbol\n";
            }
        } else {
            token += ch;
        }
    }

    // Analyze the last token if any
    if (!token.empty()) {
        if (isKeyword(token)) {
            cout << token << " : Keyword\n";
        } else if (isConstant(token)) {
            cout << token << " : Constant\n";
        } else if (isalpha(token[0])) {
            cout << token << " : Identifier\n";
        } else {
            cout << token << " : Unknown Token\n";
        }
    }
}

int main() {
    string input;
    cout << "Enter an expression: ";
    getline(cin, input);

    cout << "\n--- Lexical Analysis Result ---\n";
    analyzeTokens(input);

    return 0;
}

