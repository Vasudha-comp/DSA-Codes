#include <iostream>
#include <fstream>
//#include <string>
// #include <vector>
using namespace std;

class Student {
private:
    string roll_number;
    string name;
    string division;
    string address;

public:
    Student(){}
    // Constructor
    Student(const string& roll, const string& n, const string& div, const string& addr)
        : roll_number(roll), name(n), division(div), address(addr) {}

    // Function to add student information to the file
    void addStudent() {
        ofstream file("student_info.txt", ios::app);
        if (file.is_open()) {
            file<<roll_number;
            file <<"\nRoll Number : "<< roll_number << "\n" <<"Name : " <<name << "\n" << "Division : "<<division << "\n" <<"Address : "<< address << "\n\n";
            cout << "Student information added successfully." << endl;
        } else {
            cerr << "Unable to open file." << endl;
        }
    }

    // Function to delete student information from the file
    void deleteStudent() {
        ifstream inFile("student_info.txt");
        ofstream tempFile("temp.txt");
        int flag = 0;
        string line;
        bool found = false;
        while (getline(inFile, line)) {
            if (line != roll_number && flag == 0) {
                tempFile << line << endl;
            } else {
                found = true;
                flag += 1;
                if(flag==6)
                    flag = 0;
            }
        }

        inFile.close();
        tempFile.close();

        remove("student_info.txt");
        rename("temp.txt", "student_info.txt");

        if (found) {
            cout << "Student information deleted successfully." << endl;
        } else {
            cout << "Student not found." << endl;
        }
    }

    // Function to display student information
    void displayStudent() {
        ifstream file("student_info.txt");
        string line;
        while (getline(file, line)) {
            cout<<line<<endl;
        }
    }


};

int main() {
    while (true) {
        cout << "\n1. Add Student\n2. Delete Student\n3. Display Student\n4. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string roll_number, name, division, address;
                cout << "Enter Roll Number: ";
                cin >> roll_number;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin,name);
                cout << "Enter Division: ";
                cin >> division;
                cout << "Enter Address: ";
                cin.ignore();
                getline(cin,address);
                Student newStudent(roll_number, name, division, address);
                newStudent.addStudent();
                break;
            }
            case 2: {
                string roll_number;
                cout << "Enter Roll Number to delete: ";
                cin >> roll_number;
                Student studentToDelete(roll_number, "", "", "");
                studentToDelete.deleteStudent();
                break;
            }
            case 3: {
                string roll_number;
                // cout << "Enter Roll Number to display: ";
                // cin >> roll_number;
                // Student studentToDisplay(roll_number, "", "", "");
                Student s;
                s.displayStudent();
                break;
            }
            case 4:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
