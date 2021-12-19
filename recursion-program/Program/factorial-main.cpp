#include <iostream>	/* File: factorial-main.cpp */
using namespace std;	

//int factorial(int);

int fun(const int a[],int i,int j,int k)
{
    if(i<j)
    {   if(a[i]==k)
            return i;
        else
        {
            return fun(a,i+1,j,k);
        }
    }
    else
    {
        return 0;
    }

}
int main()	
{
/*  int x;
    int result;

    while (cin >> x)
    {
        result = factorial(x);

        if (result < 0)
            cout << "Input must be >= 0" << endl;
        else
            cout << "factorial(" << x << ") = " << result << endl;
    }
    
    
    return 0;*/
    int a[]={0,1,2,3,4,5,6};
    int x=fun(a,0,7,1);cout<<x<<endl;
    int y=fun(a,0,7,5);cout<<y<<endl;
    
}
