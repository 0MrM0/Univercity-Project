#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include  <chrono>
#include <ctime>
#include <algorithm>

using namespace std;

class Data_base
{
    // make Data_base class way can use it for inhirate
    protected:
        static vector<string> User;
        static  vector<string> Pass;
        vector<int> collegian_list = {0, 1, 2, 3, 4 ,5}; //techer just can make 5 list
        //0 in collegian_list for all list,other customize
        static vector<double> collegian_point;
        static vector<string> discription_descrptive;
        static vector<string> discription_multiplechoice;
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
        const string& getpass(size_t index) const {
            return Pass[index];
        }
};

class Teacher : public Data_base {
    protected:
        vector<string> Descriptive_questions;
        vector<string> Descriptive_answer;
        vector<string> Multiplechoice_questions;
        vector<char>   Multiplechoice_answer;
    public:
        Teacher() {}
};

class Collegian : public Teacher {
    public:
        vector<string> collegian;
        Collegian() {
            ifstream collegianUser("C:\\path\\to\\collegianUser.csv");
            string collegianUserline;
            while (getline(collegianUser, collegianUserline)) {
                collegian.push_back(collegianUserline);
                   User.push_back(collegianUserline);
            }
            collegianUser.close();
            ifstream collegianPass("C:\\path\\to\\collegianPass.csv");
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
    ifstream inputfile("C:\\path\\to\\Welcome.csv");
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
    } while(username != "Dr.Lotfi");
    do {
        cout << "Enter Password: " << endl;
        cin >> password;
        if (password == "Forget") {
            // First need change something in Teacher class
            cout << "Success Password is changed" << endl; // For test
            Passcunter = 3;
        }
        else if ((password != "Lotfi123") && (Passcunter == 0)) {
            cout << "Wrong pass! Try another 30 min" << endl; // Need get time from system
            break;
        }
        else if (password != "Lotfi123") {
            cout << "Wrong pass! You have " << Passcunter << " try" << endl;
            cout << "Forget pass? (*hint* type \"Forget\" to check and change password)" << endl;
            Passcunter--;
        }
        if (password == "Lotfi123") {
            cout << "Welcome Dr.Lotfi" << endl;
            return true;
        }
    } while (Passcunter >= 0);
    return false;
}
bool C_authenticateUser(Collegian& Student, int& Passcunter, string& username, string& password) {
    bool calleguser = false;
    do {
        cout << "Enter Username: " << endl;
        cin >> username;
        // Find the index of the entered username in the User vector
        auto it = find(Student.User.begin(), Student.User.end(), username);
        if (it != Student.User.end()) {
            calleguser = true;
            size_t userIndex = distance(Student.User.begin(), it);
            do {
                cout << "Enter Password: " << endl;
                cin >> password;
                if (password == "Forget") {
                    // Implement password change logic here
                    cout << "Success Password is changed" << endl; // For test
                    Passcunter = 3;
                }
                else if (password != Student.getpass(userIndex) && Passcunter == 0) {
                    cout << "Wrong pass! Try another 30 min" << endl; // Implement wait logic here
                    break;
                }
                else if (password != Student.getpass(userIndex)) {
                    cout << "Wrong pass! You have " << Passcunter << " try" << endl;
                    cout << "Forget pass? (*hint* type \"Forget\" to check and change password)" << endl;
                    Passcunter--;
                }
                if (password == Student.getpass(userIndex)) {
                    cout << "Welcome " << Student.getUser(userIndex) << endl;
                    return true;
                }
            } while (Passcunter >= 0);
        }
        else {
            cout << "Username not found. Please try again." << endl;
        }
    } while (!calleguser);
    return false;
}