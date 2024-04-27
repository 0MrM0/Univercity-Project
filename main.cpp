#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void Welcomemassage();
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
            fstream cl0("collegianlist0.txt");
            fstream cl1("collegianlist1.txt");
            fstream cl2("collegianlist2.txt");
            fstream cl3("collegianlist3.txt");
            fstream cl4("collegianlist4.txt");
            fstream cl5("collegianlist5.txt");
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
            ifstream file("collegianlist0.txt");
            string line;
            while (getline(file, line)) {
                collegian.push_back(line);
                User.push_back(line);
            }
            file.close();
        }
};

int main()
{
    Welcomemassage();
    Teacher Lotfi;
    string username;
    string password;
    do {
        cout << "Enter Username: " << endl;
        cin >> username;
    }while(username != Lotfi.User[0]);

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