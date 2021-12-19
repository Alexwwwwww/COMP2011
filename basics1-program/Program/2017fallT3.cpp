#include <iostream>
using namespace std;

int findSmallestOdd(int array[], int size)
{
    //base case
if(size-1==0)
return(array[size-1]%2==0)?0:array[size-1];
int cur_small=findSmallestOdd(array, size-1);
if (cur_small==0 && array[size-1]%2==1)
return array[size-1];
if(array[size-1]%2==0 ||(array[size-1]%2==1 && array[size-1]>cur_small))
return cur_small;
else
return array[size-1];
}

int main()
{
    int a[]={10, 13, 11, 14, 12, 15, 7, 2, 5};
    int b[]={2,4,6,8,10};
    cout<<findSmallestOdd(a,sizeof(a)/sizeof(int))<<endl;
    cout<<findSmallestOdd(b,sizeof(b)/sizeof(int))<<endl;
}