/*
 * COMP2011 (Spring 2021) Programming Assignment 1
 *
 * Student name: FILL YOUR NAME HERE
 * Student ID: FILL YOUR STUDENT ID NUMBER HERE
 * Student email: FILL YOUR EMAIL HERE
 *
 */

#include <iostream>
#include <limits>
using namespace std;

// Global Constants
// You cannot modify these global constants
// You cannot use your own global variables
const int LONGLONG_SIZE = 64;
const long long ONE = 1;
// End of Global Constants

// Helper Functions
// Declare additional helper functions below when necessary

// End of Helper Functions

// Tasks
// Please write your code under the TODO tag
// You cannot change the function declarations

// Task 1
int initialize(int numSeats, unsigned long long &bitmap)
{
    // Task 1 TODO
    
    
    if(numSeats<1||numSeats>LONGLONG_SIZE)
    {
        cout<<"Error: Number of seats out of range."<<endl;
        return -1;
    }
    else
    {
        int i;
        char c;
        unsigned long long expon=1;
        bitmap=0;
        
        for(i=1;i<=numSeats-1;i++)
        expon*=2;
        
        for(i=0;i<=numSeats-1;i++)
        {
            cin>>c;
            if (c=='1')
                bitmap=bitmap+expon;
            else if(c!='0' && c!='1')
            {
                cout<<"Error: Illegal state input."<<endl;
                return -1;
            }
            
            expon/=2;

        } 
       // cout<<bitmap;
        return 0;
    }

  

    // End of Task 1 TODO
}

// Task 2
int getSeatState(int numSeats, unsigned long long bitmap, int seatIndex)
{
    // Task 2 TODO
    int c;
    if (seatIndex<0 || seatIndex>numSeats-1)
    {
        //cout<<"Error: Number of seats out of range.";
        return -1;
    }    
    else
    {
        c=bitmap >> (numSeats-seatIndex-1) & 1;//get seat correspond to index
        return c;
    }

    // End of Task 2 TODO
}

// Task 3
void printSeats(int numSeats, unsigned long long bitmap)
{
    // Task 3 TODO
    int i,c;
    for(i=numSeats-1;i>=0;i--)
    {
        c=bitmap >> i & 1;//to get every seat
        cout<<c;
    }
    cout<<endl;

    // End of Task 3 TODO
}


// Task 4
int setSeatOccupied(int numSeats, unsigned long long &bitmap, int seatIndex)
{
    // Task 4 TODO
    
    if (seatIndex<0 || seatIndex>numSeats-1)
    {
        //cout<<"Error: Number of seats out of range.";
        return -1;
    }
    else if ((bitmap>> ( numSeats-seatIndex-1) & 1)==1) //get and check bits and corresponding index
        
        return -1;
    else

    {    
        bitmap=bitmap | ONE << ( numSeats-seatIndex-1);  //get it occupied
        return 0;
    }    

    // End of Task 4 TODO
}

// Task 5
int setSeatEmpty(int numSeats, unsigned long long &bitmap, int seatIndex)
{
    // Task 5 TODO
    if (seatIndex<0 || seatIndex>numSeats-1)
    {    //cout<<"Error: Number of seats out of range.";
        return -1;
    }
    else if ((bitmap>> ( numSeats-seatIndex-1) & 1)==0)
        return -1;
    else
    {
        bitmap=bitmap & ~(ONE << ( numSeats-seatIndex-1));
        return 0;
    }

    // End of Task 5 TODO
}
// Task 6
int getSeatDistance(int numSeats, unsigned long long bitmap, int seatIndex)
{
    // Task 6 TODO
    int i,flag=numSeats;//b[64] is used to store where i exist

    if (seatIndex<0 || seatIndex>numSeats-1)
    {
        //cout<<"Error: Number of seats out of range.";
        return -1;
    }    
    
    else
    {
        
        if(bitmap==0)
            return numSeats;
        for(i=seatIndex;i<=numSeats-1;i++)      //for every 0, find all the possible 1 adjacent and keep the min value
        {
           
            if((bitmap>> numSeats-i-1 & 1)==1)
            {
                flag=i-seatIndex;
                break;
            }    
        }
       
        for(i=seatIndex;i>=0;i--)      //for every 0, find all the possible 1 adjacent and keep the min value
        {
           
            if((bitmap>> numSeats-i-1 & 1)==1)
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

// Task 7
int findSeat(int numSeats, unsigned long long bitmap)
{
    // Task 7 TODO
    int i,j,flag=0,max_dist=0,max_ind=0;//b[64] is used to store where i exist
    /*for(i=1;i<=numSeats;i++)
    {
        a[i-1]=bitmap>> numSeats-i & 1;//store the seat state
        //cout<<a[i-1]<<" ";
    }*/
    //no empty seats left

        if(bitmap==0)
            return 0;
        for (i=1;i<=numSeats-1;i++)
        {
            if((bitmap>> numSeats-i-1 & 1)==0)
            {
                flag=1;
                break;         //means there is at least one 0    
            }         
        }
        if (flag==0)
        return -1;             //flag is unchanged, seats are all occupided
        
        for (j=0;j<=numSeats-1;j++)
        {
            if(getSeatDistance(numSeats,bitmap, j)>max_dist)
            {
                max_dist=getSeatDistance(numSeats,bitmap, j);
                max_ind=j;
            }
            
            
        }
    //cout<<endl;    
    return max_ind;

    // End of Task 7 TODO
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED

void run_init(int &numSeats, unsigned long long &bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Initializing" << endl;
    cout << endl;
    int initResult = 0;
    do
    {
        cout << "? Enter the total number of seats:";
        cin >> numSeats;
        cout << "? Enter the initial state of seats:" << endl;
        initResult = initialize(numSeats, bitmap);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (initResult < 0);
    cout << "! Initialization succeeded!" << endl;
}

void run_getSeatState(int numSeats, unsigned long long bitmap)
{

    int seatIndex;
    int seatState;
    cout << "##################################################" << endl;
    cout << "# Query the current state of a seat" << endl;
    cout << endl;
    cout << "? Enter the index of queried seat:";
    cin >> seatIndex;
    seatState = getSeatState(numSeats, bitmap, seatIndex);
    if (seatState < 0)
    {
        cout << "! Error: Seat index out of bounds. Query failed." << endl;
    }
    else if (seatState == 0)
    {
        cout << "! The queried seat is empty." << endl;
    }
    else if (seatState == 1)
    {
        cout << "! The queried seat is occupied." << endl;
    }
}

void run_printSeats(int numSeats, unsigned long long bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Printing the current state" << endl;
    cout << endl;
    printSeats(numSeats, bitmap);
    cout << endl;
}

void run_setSeatOccupied(int numSeats, unsigned long long &bitmap)
{

    cout << "##################################################" << endl;
    cout << "# Marking a seat as occupied" << endl;
    cout << endl;
    int seatIndex;
    int result;
    cout << "? Enter the index of target seat:";
    cin >> seatIndex;
    result = setSeatOccupied(numSeats, bitmap, seatIndex);
    if (result < 0)
    {
        cout << "! Error: Failed to set seat state, seat index out of bounds or seat already occupied." << endl;
    }
    else
    {
        cout << "! Seat state set." << endl;
    }
}

void run_setSeatEmpty(int numSeats, unsigned long long &bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Marking a seat as empty" << endl;
    cout << endl;
    int seatIndex;
    int result;
    cout << "? Enter the index of target seat:";
    cin >> seatIndex;
    result = setSeatEmpty(numSeats, bitmap, seatIndex);
    if (result < 0)
    {
        cout << "! Error: Failed to set seat state, seat index out of bounds or seat is already empty." << endl;
    }
    else
    {
        cout << "! Seat state set." << endl;
    }
}

void run_getSeatDist(int numSeats, unsigned long long bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Calculating the closest distance to occupied seats" << endl;
    cout << endl;
    int seatIndex;
    int distance;
    cout << "? Enter the index of queried seat:";
    cin >> seatIndex;
    distance = getSeatDistance(numSeats, bitmap, seatIndex);
    if (distance < 0)
    {
        cout << "! Error: Seat index out of bounds. Query failed." << endl;
    }
    else
    {
        cout << "! The distance to closest occupied seat is " << distance << "." << endl;
    }
}

void run_findSeat(int numSeats, unsigned long long bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Finding an empty seat" << endl;
    cout << endl;
    int seatIndex = findSeat(numSeats, bitmap);
    if (seatIndex == -1)
    {
        cout << "! No empty seats left" << endl;
    }
    else
    {
        cout << "! The empty seat with maximum distance to closest person is at " << seatIndex << "." << endl;
    }
}

void run_option()
{
    int numSeats = 0;
    unsigned long long bitmap = 0;
    int option;
    cout << "==================================================" << endl;
    cout << "= Welcome to COMP2011 PA1 Seat Management System =" << endl;
    cout << "==================================================" << endl;

    run_init(numSeats, bitmap);

    while (true)
    {
        cout << "##################################################" << endl;
        cout << "# Main Menu" << endl;
        cout << endl;
        cout << "1 Initialize" << endl;
        cout << "2 Query the current state of a seat" << endl;
        cout << "3 Print the bitmap to screen" << endl;
        cout << "4 Change the state of a seat to OCCUPIED" << endl;
        cout << "5 Change the state of a seat to EMPTY" << endl;
        cout << "6 Calculate the closest distance from a seat to occupied seats" << endl;
        cout << "7 Find the empty seat with maximum distance to closest occupied seat" << endl;
        cout << "0 Exit" << endl;
        cout << endl;
        cout << "? Please enter an option (0-7): ";
        cin >> option;
        switch (option)
        {
        case 0:
            cout << "! Bye Bye." << endl;
            return;
        case 1:
            run_init(numSeats, bitmap);
            break;
        case 2:
            run_getSeatState(numSeats, bitmap);
            break;
        case 3:
            run_printSeats(numSeats, bitmap);
            break;
        case 4:
            run_setSeatOccupied(numSeats, bitmap);
            break;
        case 5:
            run_setSeatEmpty(numSeats, bitmap);
            break;
        case 6:
            run_getSeatDist(numSeats, bitmap);
            break;
        case 7:
            run_findSeat(numSeats, bitmap);
            break;
        default:
            cout << "Illegal Choice, please try again." << endl;
            break;
        }
        cout << "! Returning to main menu." << endl;
    }
}

int main()
{
    run_option();
    return 0;
}
