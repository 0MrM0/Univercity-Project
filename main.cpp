#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Data_base
{
    // make Data_base class way can use it for inhirate
    private:
        fstream cl0("collegianlist0.txt");
        fstream cl1("collegianlist1.txt");
        fstream cl2("collegianlist2.txt");
        fstream cl3("collegianlist3.txt");
        fstream cl4("collegianlist4.txt");
        fstream cl5("collegianlist5.txt");
    protected:
        vector<string> Username;
        vector<string> Pass;
        vector<int>    collegian_list = {0, 1, 2, 3, 4 ,5}; //techer just can make 5 list
        //0 in collegian_list for all list,other customize
        vector<double> collegian_point;
        vector<string> discription_descrptive;
        vector<string> discription_multiplechoice;
    public:
        Data_base() {
            //make space by constructor
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
            Username.push_back("Dr.Lotfi");
        }
};

class Collegian : public Teacher {
    public:
        vector<string> collegian;
        Collegian() {
            collegian.push_back(cl0);
        }
};

int main()
{

    return 0;
}
