#include <iostream>
using namespace std;

int main() {
    double num1, num2;
    char operation;
    char choice;

    do{
        cout << "Enter first number: ";
        cin >> num1;
        cout << "Enter second number: ";
        cin >> num2;
        
        cout << "Enter operation (+,-,*,/): ";
        cin >> operation;

        switch (operation)
        {
        case '+':
            cout << "Result: " << num1 + num2 << endl;
            break;

        case '-':
            cout << "Result: " << num1 - num2 << endl;
            break;
        
        case '*':
            cout << "Result: " << num1 * num2 << endl;
            break;

        case '/':
        if (num2 !=0)
            cout << "Result: " << num1 / num2 << endl;
        else
            cout << "Error: Division by Zero" << endl;
            break;

        default:
            break;
        }
        cout << "Do you want to perform another calculation? (y/n): ";
        cin >> choice;
        
    } while (choice == 'y' || choice == 'Y');

    return 0;
}