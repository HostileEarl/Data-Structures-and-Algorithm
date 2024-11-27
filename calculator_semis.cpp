#include <iostream>

#include <string>

#include <stack>

#include <cctype>



using namespace std;



int getPrecedence(char ch) {

    switch (ch) {

        case '+':

        case '-': return 1;

        case '/': return 2;

        case '*':

        case '(':

        case ')': return 0;

        default: return -1;

    }

}



bool isDigit(char ch) {

    return isdigit(ch);

}



bool isOp(char ch) {

    return (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch =='(' || ch == ')');

}




int operate(int v1, int v2, char optr){

    if (optr == '+') return v1 + v2;

    if (optr == '-') return v1 - v2;

    if (optr == '*') return v1 * v2;

    if (optr == '/') return v1 / v2;

    return 0;

}



int evaluate(string str){

    stack<int> values;

    stack<char> optrs;



    int val = 0;

    bool buildingNumber = false;



    for (char spot : str) {

        if (isDigit(spot)){

            val = (val * 10) + (spot - '0');

            buildingNumber = true;

        } else {

            if (buildingNumber){

                values.push(val);

                val = 0;

                buildingNumber = false;

            }

            if (isOp(spot)){

                if (spot == '('){

                    optrs.push(spot);

                } else if (spot == ')'){

                    while (!optrs.empty() && optrs.top() != '('){

                        char optr = optrs.top(); optrs.pop();

                        int v2 = values.top(); values.pop();

                        int v1 = values.top(); values.pop();

                        values.push(operate(v1, v2,optr));

                    }

                    optrs.pop();

                } else {

                    while (!optrs.empty() && getPrecedence(optrs.top()) >= getPrecedence(spot)){

                        char optr = optrs.top(); optrs.pop();

                        int v2 = values.top(); values.pop();

                        int v1 = values.top(); values.pop();

                        values.push(operate(v1, v2, optr));

                    }

                    optrs.push(spot);

                }

            }

        }

    }



    if (buildingNumber){

        values.push(val);

    }



    while (!optrs.empty()){

        char op = optrs.top(); optrs.pop();

        int val2 = values.top(); values.pop();

        int val1 = values.top(); values.pop();

        values.push(operate(val1, val2,op));

    }



    return values.top();

}



int main(){

    string expression;

    cout << "Input: ";

    getline(cin, expression);

    cout << "Output: " << evaluate(expression) << endl;

    return 0;

}
