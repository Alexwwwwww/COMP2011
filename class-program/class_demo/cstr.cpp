#include <iostream>
using namespace std;

int main()
{
    char str[25]="Minato Kobashi";
    str[8]='\0';
    cout<<str<<endl<<sizeof(char);
}