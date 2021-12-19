#include <iostream>
#include <cstdlib>
using namespace std;

//****************************************************************************************************************************
int getSeatDistance(int numSeats, unsigned long long bitmap, int seatIndex)
{
    // Task 6 TODO
    int a[64],i,flag;//b[64] is used to store where i exist
    for(i=1;i<=numSeats;i++)
    {
        a[i-1]=bitmap>> numSeats-i & 1;//store the seat state
        //cout<<a[i-1]<<" ";
    }
    //cout<<endl;
    if (seatIndex<0 || seatIndex>numSeats-1)
    {
        //cout<<"Error: Number of seats out of range.";
        return -1;
    }    
    
    else
    {
        
        for(i=seatIndex;i<=numSeats-1;i++)      //for every 0, find all the possible 1 adjacent and keep the min value
        {
            if(a[i]==1)
            {
                flag=i-seatIndex;
                break;
            }    
        }
        for(i=seatIndex;i>=0;i--)      //for every 0, find all the possible 1 adjacent and keep the min value
        {
            if(a[i]==1)
            {
                if(seatIndex-i<flag)
                {
                    flag=seatIndex-i;
                }    
                break;
            }   
        }
        return flag;   
    }    
    
    // End of Task 6 TODO
}


  

    // End of Task 3 TODO
int main()
{
    int x,a;
    a=x=0;
    cout<<a<<"\n";
    cout<<"hello world\n";
    cout<<getSeatDistance(9,133,8);
    return 0;
}