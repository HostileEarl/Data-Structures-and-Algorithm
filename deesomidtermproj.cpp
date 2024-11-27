#include <iostream>
#include <string>
#include <iomanip> 
#include <vector>

using namespace std;



struct Employee {
    string eID;
    string ePos;
    string eName;
};

vector<Employee> employees;

void AddRecord() {
    Employee emp;

    cin.ignore();

    cout << "Employee ID: ";
    getline(cin, emp.eID);
    cout << "Position: ";
    getline(cin, emp.ePos);
    cout << "Employee Name: ";
    getline(cin, emp.eName);

    employees.push_back(emp);
}

void ListRecord() {
    system("CLS");
    cout << "Current Record(s)" << endl;
    cout << "===============================================" << endl;

    cout << left << setw(5) << "No."
         << setw(10) << "ID"
         << setw(20) << "Position"
         << setw(20) << "Name" << endl;
    cout << "-----------------------------------------------" << endl;

    if (employees.empty()) {
        cout << "No Record Found!" << endl;
    } else {
        for (size_t i = 0; i < employees.size(); ++i) {
            cout << setw(5) << i + 1
                 << setw(10) << employees[i].eID
                 << setw(20) << employees[i].ePos
                 << setw(20) << employees[i].eName << endl;
        }
    }
    cout << "-----------------------------------------------" << endl;
}

void SearchRecord(const string& search) {
    system("CLS");
    cout << "Current Record(s)" << endl;
    cout << "===============================================" << endl;
    int counter = 0;

    for (size_t i = 0; i < employees.size(); ++i) {
        if (employees[i].eID == search) {
            counter++;
            cout << " " << counter << "      " << employees[i].eID << "        " << employees[i].ePos << "        " << employees[i].eName << endl;
            break;
        }
    }
    if (counter == 0) {
        cout << "No Record Found!" << endl;
    }
    cout << "-----------------------------------------------" << endl;
}

void UpdateRecord(const string& search) {
    bool found = false; 

    for (size_t i = 0; i < employees.size(); ++i) {
        if (employees[i].eID == search) {
            found = true; 

            
            cout << "Current Name: " << employees[i].eName << endl;
            cout << "New Employee Name: ";
            cin.ignore(); 
            getline(cin, employees[i].eName);

            
            cout << "Current Position: " << employees[i].ePos << endl;
            cout << "New Position: ";
            getline(cin, employees[i].ePos); 

            cout << "Update Successful!" << endl;
            break; 
        }
    }

    if (!found) {
        cout << "ID does not exist!" << endl; 
    }
}

void DeleteRecord(const string& search) {
    int counter = 0;

    for (size_t i = 0; i < employees.size(); ++i) {
        if (employees[i].eID == search) {
            counter++;
            employees.erase(employees.begin() + i);
            cout << "Successfully Deleted!" << endl;
            break;
        }
    }
    if (counter == 0) {
        cout << "ID Number does not exist!" << endl;
    }
}

int main() {
    
    string eID;
    int option;
    system("CLS");

    do {
        cout << "-----------EMPLOYEE MANAGEMENT SYSTEM----------\n";
        cout << "1. Create Records" << endl;
        cout << "2. Update Records" << endl;
        cout << "3. Delete Records" << endl;
        cout << "4. Search Records" << endl;
        cout << "5. Display All Records" << endl;
        cout << "6. Exit" << endl;
        cout << "===============================================" << endl;

        cout << "Select Option >> ";
        cin >> option;
        cin.ignore();

        switch (option) {
            case 1:
                AddRecord();
                system("CLS");
                break;
            case 2:
                cout << "Search by ID >> ";
                getline(cin, eID);
                UpdateRecord(eID);
                break;
            case 3:
                cout << "Search by ID >> ";
                getline(cin, eID);
                DeleteRecord(eID);
                system("CLS");
                break;
            case 4:
                cout << "Search by ID >> ";
                getline(cin, eID);
                SearchRecord(eID);
                break;
            case 5:
                ListRecord();
                break;
        }
    } while (option != 6);

    cout << "Exiting...." << endl;

    return 0;
}

