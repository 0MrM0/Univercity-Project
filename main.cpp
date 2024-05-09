#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <algorithm>

using namespace std;

class Data_base
{
    // make Data_base class way can use it for inhirate
    protected:
        vector<string> User;
        vector<string> Pass;
        vector<int>    collegian_list = {0, 1, 2, 3, 4 ,5}; //techer just can make 5 list
        //0 in collegian_list for all list,other customize
        vector<double> collegian_point;
        vector<string> discription_descrptive;
        vector<string> discription_multiplechoice;
        vector<string> loginhistory;
    public:
        Data_base() {
            //make space by constructor & make some files use for collegian list
            fstream cl0("C:\\path\\to\\collegianlist0.csv");
            fstream cl1("C:\\path\\to\\collegianlist1.csv");
            fstream cl2("C:\\path\\to\\collegianlist2.csv");
            fstream cl3("C:\\path\\to\\collegianlist3.csv");
            fstream cl4("C:\\path\\to\\collegianlist4.csv");
            fstream cl5("C:\\path\\to\\collegianlist5.csv");
        }
        const string& getUser(size_t index) const {
            return User[index];
        }
        // const string& getPass(size_t index) const {
        //     return Pass[index];
        // }
        // Function to find a user and return its index
        int findUser(const string& username) const {
            auto it = find(User.begin(), User.end(), username);
            if (it != User.end()) {
                return distance(User.begin(), it);
            }
            return -1; // Return -1 if user is not found
        }
        // Function to get password using the index
        const string& getPass(int index) const {
                if (index >= 0 && index < Pass.size()) {
                    return Pass[index];
                }
                throw out_of_range("Index out of range"); // Handle out-of-range errors
        }
};

class Teacher : public Data_base {
    protected:
        vector<string> Descriptive_questions;
        vector<string> Descriptive_answer;
        vector<string> Multiplechoice_questions;
        vector<char>   Multiplechoice_answer;
    public:
        Teacher()
        {
            User.push_back("Dr.Lotfi");
            Pass.push_back("Lotfi123");
        }
};

class Collegian : public Teacher {
    public:
        vector<string> collegian;
        Collegian() {
            //Read data for
            ifstream file("C:\\path\\to\\collegianlist.csv");
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string col1, col2;
                getline(ss, col1, ','); // Get first column
                getline(ss, col2, ','); // Get second column
                // Remove spaces from col1 and col2 if necessary
                col1.erase(remove(col1.begin(), col1.end(), ' '), col1.end());
                col2.erase(remove(col2.begin(), col2.end(), ' '), col2.end());
                // Concatenate col1 and col2 and push back into the vector
                collegian.push_back(col1 + col2);
            }
            file.close();

            ifstream collegianUser("C:\\path\\to\\collegianUser.csv"); //for now just me in the list
            string collegianUserline;
            while (getline(collegianUser, collegianUserline)) {
                User.push_back(collegianUserline);
            }
            collegianUser.close();

            ifstream collegianPass("C:\\path\\to\\collegianPass.csv"); //for now just me in the list
            string collegianPassline;
            while (getline(collegianPass, collegianPassline)) {
                Pass.push_back(collegianPassline);
            }
            collegianPass.close();
        }
};

void Welcomemassage();
bool T_authenticateUser(Teacher& Lotfi, int& Passcunter, string& username, string& password);
bool C_authenticateUser(Collegian& Student, int& Passcunter, string& username, string& password);

int main()
{
    Welcomemassage();
    Teacher Lotfi;
    Collegian Student;
    string username;
    string password;
    char type;
    int Passcunter = 3;
    cout << "who you are?\n a)Teacher b)Callegian c)Admin" << endl;
    cin >> type;
    if (type == 'a') {
        bool isTAuthenticated = T_authenticateUser(Lotfi, Passcunter, username, password); //isTAuthenticated for teachers
        if (!isTAuthenticated) {
            // Handle authentication failure
        }
        // Continue with the rest of the program
    } else {
        bool isCAuthenticated = C_authenticateUser(Student, Passcunter, username, password); //isCAuthenticated for callegian
        if (!isCAuthenticated) {
            // Handle authentication failure
        }
        // Continue with the rest of the program
    }
    return 0;
}

void Welcomemassage() {
    ifstream inputfile("C:\\path\\to\\Welcome.txt");
    string welcomemassage;
    string firstLine;
    while (getline(inputfile, welcomemassage)){
        firstLine += welcomemassage + "\n";
    }
    cout << firstLine << endl;
    inputfile.close();
}
bool T_authenticateUser(Teacher& Lotfi, int& Passcunter, string& username, string& password) {
    do {
        cout << "Enter Username: " << endl;
        cin >> username;
    } while(Lotfi.getUser(0) != username);
    do {
        cout << "Enter Password: " << endl;
        cin >> password;
        if (password == "Forget") {
            // First need change something in Teacher class
            cout << "Success Password is changed" << endl; // For test
            Passcunter = 3;
        }
        else if (password != Lotfi.getPass(0) && Passcunter == 0) {
            cout << "Wrong pass! Try another 30 min" << endl; // Need get time from system
            break;
        }
        else if (password != Lotfi.getPass(0)) {
            cout << "Wrong pass! You have " << Passcunter << " try" << endl;
            cout << "Forget pass? (*hint* type \"Forget\" to check and change password)" << endl;
            Passcunter--;
        }
        if (password == Lotfi.getPass(0)) {
            cout << "Welcome " << Lotfi.getUser(0) << endl;
            return true;
        }
    } while (Passcunter >= 0);
    return false;
}
bool C_authenticateUser(Collegian& Student, int& Passcunter, string& username, string& password) {
    int userIndex = -1;
    do {
        cout << "Enter Username: " << endl;
        cin >> username;
        userIndex = Student.findUser(username);
        if (userIndex == -1) {
            cout << "Username not found. Please try again." << endl;
        }
    } while (userIndex == -1);
    do {
        cout << "Enter Password: " << endl;
        cin >> password;
        if (password == "Forget") {
            // First need to implement password change logic
            cout << "Success! Password has been changed." << endl; // For testing
            Passcunter = 3;
        }else if (password != Student.getPass(userIndex) && Passcunter == 0) {
            cout << "Wrong password! Try again in 30 minutes." << endl; // Need to get time from system
            break;
        }
        else if (password != Student.getPass(userIndex)) {
            cout << "Wrong password! You have " << Passcunter << " tries left." << endl;
            cout << "Forgot password? (*hint* type \"Forget\" to check and change password)" << endl;
            Passcunter--;
        }
        if (password == Student.getPass(userIndex)) {
            cout << "Welcome " << username << endl;
            return true;
        }
    } while (Passcunter >= 0);
    return false;
}
