#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
    public:
        Data_base() {
            //make space by constructor & make some files use for collegian list
            fstream cl0("C:\\path\\to\\collegianlist0.txt");
            fstream cl1("C:\\path\\to\\collegianlist1.txt");
            fstream cl2("C:\\path\\to\\collegianlist2.txt");
            fstream cl3("C:\\path\\to\\collegianlist3.txt");
            fstream cl4("C:\\path\\to\\collegianlist4.txt");
            fstream cl5("C:\\path\\to\\collegianlist5.txt");
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
            ifstream file("C:\\path\\to\\collegianlist0.txt"); //for now just me in the list
            string line;
            while (getline(file, line)) {
                collegian.push_back(line);
            }
            file.close();
            ifstream collegianUser("C:\\path\\to\\collegianUser.txt"); //for now just me in the list
            string collegianUserline;
            while (getline(collegianUser, collegianUserline)) {
                collegian.push_back(collegianUserline);
            }
            collegianUser.close();
            ifstream collegianPass("C:\\path\\to\\collegianPass.txt"); //for now just me in the list
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
        else if (password != Lotfi.getpass(0) && Passcunter == 0) {
            cout << "Wrong pass! Try another 30 min" << endl; // Need get time from system
            break;
        }
        else if (password != Lotfi.getpass(0)) {
            cout << "Wrong pass! You have " << Passcunter << " try" << endl;
            cout << "Forget pass? (*hint* type \"Forget\" to check and change password)" << endl;
            Passcunter--;
        }
        if (password == Lotfi.getpass(0)) {
            cout << "Welcome " << Lotfi.getUser(0) << endl;
            return true;
        }
    } while (Passcunter >= 0);
    return false;
}
bool C_authenticateUser(Collegian& Student, int& Passcunter, string& username, string& password){
    bool calleguser = false;
    do {
        cout << "Enter Username: " << endl;
        cin >> username;
        for (size_t i = 0; i < Student.collegian.size(); ++i) {
            if (Student.collegian[i] == username) {
                calleguser = true;
                break; // خروج از حلقه اگر نام کاربری پیدا شد
            }
        }
    } while(!calleguser);
    do {
        cout << "Enter Password: " << endl;
        cin >> password;
        if (password == "Forget") {
            // First need change something in Teacher class
            cout << "Success Password is changed" << endl; // For test
            Passcunter = 3;
        }
        else if (password != Student.getpass() && Passcunter == 0) {
            cout << "Wrong pass! Try another 30 min" << endl; // Need get time from system
            break;
        }
        else if (password != Student.getpass()) {
            cout << "Wrong pass! You have " << Passcunter << " try" << endl;
            cout << "Forget pass? (*hint* type \"Forget\" to check and change password)" << endl;
            Passcunter--;
        }
        if (password == Student.getpass()) {
            cout << "Welcome " << Student.getUser() << endl;
            return true;
        }
    } while (Passcunter >= 0);
    return false;
}