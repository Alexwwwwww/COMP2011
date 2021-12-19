#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
using namespace std;
 
int main()
{
    const int NUM_INIT=10;
    int id[NUM_INIT],name[NUM_INIT],grade[NUM_INIT];
    string str;
    const string filename="data1.txt";
    if(str=="")
    cout<<'h'<<endl;
    ifstream ifs("data1.txt");
    int i;

    if (ifs){
        cout << "ID" << "\t" << "Name" << "\t" << "Grade" << endl;
        while(!ifs.eof())
        {
            getline(ifs,str);
            cout<<str<<endl;
        }
        ifs.close();
        cout << "Initialization success!" << endl;
    }
    else{
        cerr << "Error: Cannot open " << filename << endl;
        exit(1);
    }
    return 0;
}