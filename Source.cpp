#include <iostream>
#include <string>

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isValidChar(char c) {
    std::string validChars = "._+-";
    return isLetter(c) || isDigit(c) || validChars.find(c) != std::string::npos;
}

bool isValidEmail(const std::string& email) {
    int state = 0;
    int atCount = 0; 
    int dotCount = 0; 
    int lastAt = 0;  

    for (int i = 0; i < email.length(); ++i) {
        char c = email[i];

        switch (state) {
        case 0: 
            if (isValidChar(c)) {
                state = 1; 
            }
            else if (c == '@' && i > 0) {
                state = 2; 
                atCount++;
                lastAt = i;
            }
            else {
                return false;
            }
            break;
        case 1: 
            if (c == '@' && i > 0) {
                state = 2; 
                atCount++;
                lastAt = i;
            }
            else if (!isValidChar(c)) {
                return false;
            }
            break;
        case 2: 
            if (isLetter(c) || isDigit(c) || c == '-') {
                state = 3; 
            }
            else {
                return false;
            }
            break;
        case 3: 
            if (c == '.') {
                dotCount++;
                state = 2; 
            }
            else if (!isLetter(c) && !isDigit(c) && c != '-') {
                return false;
            }
            break;
        }
    }

    return atCount == 1 && dotCount > 0 && lastAt < email.length() - 1;
}

int main() {
    std::string input;
    std::cout << "Ingrese un correo electrónico para validar: ";
    std::cin >> input;

    if (isValidEmail(input)) {
        std::cout << "El correo electrónico es válido.\n";
    }
    else {
        std::cout << "El correo electrónico no es válido.\n";
    }

    system("pause");
    return 0;
}