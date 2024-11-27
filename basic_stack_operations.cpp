#define DeseoStack

#include <iostream>



using namespace std;





class Stack {



    private:



        int top;

        int maxSize;

        int * stackArray;





    public:



        Stack (int size) {



            maxSize = size;



            stackArray = new int[maxSize];



            top = -1;



        }



    ~Stack() {



        delete[] stackArray;



    }





    bool isEmpty () { 

        return (top == -1);

       }



    bool isFull() {   

        return(top == maxSize-1);

      }



    void push(int value) {    



        if (isFull()) {

            cout << "Stack is full. Cannot push " << value << "." << endl;

            return;

        } else {

            stackArray[++top] = value;

            cout << "Pushed " << value << " onto the stack." << endl;

        }



     }



    void pop() {   



        if (isEmpty()) {

             cout << "Stack is empty. Cannot pop." << endl;

        } else {

            cout << "Popped " << stackArray[top--] << " from the stack." << endl;

        }



      } 



    int peek() {  



        if (isEmpty()) {

            cout << "Stack is empty. Nothing to peek." << endl;

            return -1;

        } else {

            return stackArray[top];



        }



       }



};





int main(){



    Stack stack (5);



    

    cout << "Is Empty?: " << stack.isEmpty() << endl;

    stack.push(10);

    stack.push(20);

    stack.push(30);

    stack.push(40);

    stack.push(50);



    cout << "Is Full?: " << stack.isFull() << endl;

    cout << "Top element: " << stack.peek() << endl;



    stack.pop();

    stack.pop();

    cout << "Top element after popping: " << stack.peek() << endl;



    stack.push(60);



    return 0;



}
