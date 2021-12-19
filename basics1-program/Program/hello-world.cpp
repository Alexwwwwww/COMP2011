/* 
 * File: hello-world.cpp
 * A common program used to demo a new language
 */

#include <iostream>     // Load info of a Standard C++ library
using namespace std;    // Standard C++ namespace
void func(char a[])
{
    cout<<sizeof(a)/28<<"haha"<<endl;
}
int main()              // Program's entry point
{
    /* Major program codes */
    char *p;
    char a[15]="Hello World!";
    int num=1;
    p=a;
    cout<<sizeof(p)<<endl;
    cout<<sizeof(a)<<endl;
    cout<<sizeof(&num)<<endl;
    func(a);
    cout << "Hello World!" << endl;
    a[0]='h';
    for(int i=0;i<=11;i++)
        cout<<a[i];
    cout<<endl<<a[19];
    return 0;           // A nice ending
}
