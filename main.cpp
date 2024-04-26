#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Data_base
{
    // make Data_base class way can use it for inhirate
    protected:
        vector<string> Username;
        vector<string> Pass;
        vector<string> collegian;
        vector<int>    collegian_list;
        vector<string> Descriptive_questions;
        vector<string> Descriptive_answer;
        vector<string> Multiplechoice_questions;
        vector<char>   Multiplechoice_answer;
        vector<double> collegian_point;
        vector<string> discription_descrptive;
        vector<string> discription_multiplechoice;
    public:
        void Data_base() {
            //make space by constactor
        };
};

int main()
{

    return 0;
}
