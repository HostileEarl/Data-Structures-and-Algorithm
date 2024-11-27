#include <iostream> 
#include <queue>     
#include <string>     
#include <thread>     
#include <chrono>     
#include <atomic>

using namespace std;

class Person {     
    public:         
        string name;         
        int ticket_number;         
        static int ticket_counter;        

        Person(string name) {             
            this->name = name;             
            this->ticket_number = ticket_counter++;     
        }    
};     

int Person::ticket_counter = 1;

class Queue {     
    private:         
        queue<Person> line;     
        atomic<bool> running;   

    public:
        Queue() : running(true) {}

        void enqueue(Person person) {             
            line.push(person);             
            cout << person.name << " added to the queue with Ticket #" << person.ticket_number << endl;             
            size();         
        }             

        void autoDequeue() {             
            while (running) {                 
                if (!isEmpty()) {                     
                    this_thread::sleep_for(chrono::minutes(1));
                    
                    if (!isEmpty()) { 
                        Person front_person = line.front();                     
                        cout << "\nAfter 1 minute...\n";                     
                        cout << "Dequeue: " << front_person.name << " received a ticket (Ticket #" << front_person.ticket_number << ")\n";                     
                        line.pop();                     
                        size();                     
                        peek();                 
                    }
                }             
            }         
        }

        void stopDequeueing() {
            running = false;
        }

        bool isEmpty() {             
            return line.empty();         
        }             

        void size() {             
            cout << "Queue size: " << line.size() << endl;         
        }             

        void peek() {             
            if (!isEmpty()) {                 
                Person next_person = line.front();                 
                cout << "Next in line: " << next_person.name << " (Ticket #" << next_person.ticket_number << ")\n";             
            } else {                 
                cout << "No one is in line.\n";             
            }         
        }             

        void position(const string& name_or_ticket) {             
            queue<Person> temp_queue = line;             
            int position = 1;             
            while (!temp_queue.empty()) {                 
                Person person = temp_queue.front();                 
                if (person.name == name_or_ticket || to_string(person.ticket_number) == name_or_ticket) {                     
                    cout << person.name << " is currently at position " << position << " in the queue.\n";                     
                    return;                 
                }                 
                temp_queue.pop();                 
                position++;             
            }             
            cout << name_or_ticket << " is not in the queue.\n";         
        }     
};     

int main() {         
    Queue queue;         
    int option;         
    string name;         

    cout << "Welcome to Olivia Rodrigo's Concert Ticketing System!\n";         

    
    thread dequeueThread(&Queue::autoDequeue, &queue);

    while (true) {             
        cout << "\n1. Enqueue a person\n";             
        cout << "2. Check your position in the queue\n";             
        cout << "3. Exit\n";             
        cout << "Choose an option: ";             
        cin >> option;             

        if (option == 1) {                 
            cout << "Enter the name: ";                 
            cin >> name;                 
            Person person(name);                 
            queue.enqueue(person);             
        } else if (option == 2) {                 
            cout << "Enter your name or ticket number: ";                 
            cin >> name;                 
            queue.position(name);             
        } else if (option == 3) {                 
            cout << "Exiting...\n";                 
            queue.stopDequeueing(); 
            break;             
        } else {                 
            cout << "Invalid option! Please try again.\n";             
        }         
    }

   
    dequeueThread.join();

    return 0;     
}
