//please read the "Important requirements" for what you CANNOT do
#include <iostream>
using namespace std;

const int MAX_SIZE = 12;

//this function simply returns you the maximum of the two given integers a and b
//you can use it if you want, but do NOT modify this function
int max(int a, int b)
{
    return a>b?a:b;
}

//this function returns true if the given cell (x,y) is a doctor (for the infectWithPower simulation) and returns false otherwise
//you can use it if you want, but do NOT modify this function
bool isDoctor(char map[][MAX_SIZE], int width, int height, int x, int y)
{
    if(x<0 || x>=width || y<0 || y>=height)
        return false;
    else
        return map[y][x] >= 'A' && map[y][x] <= 'I';
}

//this function returns true if the given cell (x,y) is infected (for the infectWithPower simulation) and returns false otherwise
//you can use it if you want, but do NOT modify this function
bool isInfected(char map[][MAX_SIZE],  int width, int height, int x, int y)
{
    if(x<0 || x>=width || y<0 || y>=height)
        return false;
    return map[y][x] >= '0' && map[y][x] <= '9';
}


void printMap(char map[][MAX_SIZE], int width, int height, int x=0, int y=0)
{
    if(y==height)
    return;
    else
    {
        if(x==width)
        {   
            cout<<endl; 
            printMap(map,width,height,0,y+1);
            return;
        }
        else
        {
            cout<<map[y][x]<<" ";
        }  
   
        printMap(map,width,height,x+1,y);
    }
}

int countCharacter(char map[][MAX_SIZE], int width, int height, char c, int x=0, int y=0)
{
    if(y==height)
        return 0;
    else
    {   
        if(x==width)
        {    
            return countCharacter(map,width,height,c,0,y+1);
        }
        else
        {
            //cout<<"(x,y)="<<x<<","<<y<<'='<<map[y][x]<<endl;
            if(c==map[y][x])
                return countCharacter(map,width,height,c,x+1,y)+1;
            else
                return countCharacter(map,width,height,c,x+1,y);
        }  

    }
    return 0;
}

int infect(char map[][MAX_SIZE], int width, int height, int x, int y)
{
    if(x<0 || x>=width || y<0 || y>=height || map[y][x]!='p')
        return 0;
    else
    {
        map[y][x]='v';
        infect(map, width, height, x-1, y);
        infect(map, width, height, x+1, y);
        infect(map, width, height, x, y+1);
        infect(map, width, height, x, y-1);
        
    }
    return countCharacter(map,width,height,'v');
}

int getProtectionLevel(char map[][MAX_SIZE], int width, int height, int x, int y)
{
    int protection_level=0;
    if(map[y][x]=='.' || isDoctor(map,width, height, x, y))
    return 0;
    if(x<0 || x>=width || y<0 || y>=height)
    return 0;
    else
    {
        if(isDoctor(map,width, height, x+1, y))   //to check if there is doctor in adjacent space
            protection_level=max(map[y][x+1]-'A'+1,protection_level);    
        if(isDoctor(map,width, height, x, y+1))
            protection_level=max(map[y+1][x]-'A'+1,protection_level);
        if(isDoctor(map,width, height, x-1, y))
            protection_level=max(map[y][x-1]-'A'+1,protection_level); 
        if(isDoctor(map,width, height, x, y-1))   
            protection_level=max(map[y-1][x]-'A'+1,protection_level);

        return protection_level;
    }
}

void infectWithPower(char map[][MAX_SIZE], int width, int height, int x, int y, int power)
{
    if(power==0)   //this power is of type int
    return;
    if(x<0 || x>=width || y<0 || y>=height)
    return;
    if(map[y][x]=='.' || isDoctor(map,width, height, x, y))
    return;
    else
    {
        if(map[y][x]=='p')               //to check if it is p
            map[y][x]=power+48;              //change made on map is to change power into a char
        else if(map[y][x]<57)            // if this is already a number, keep the larger one    
            map[y][x]=max(power+48,map[y][x]);
            
        if(getProtectionLevel(map, width,  height,  x, y)>=map[y][x]-48) //getprotectionlevel is an integer
        {
            
            map[y][x]='p';
            return;
        }
        infectWithPower(map, width, height, x-1, y, power-1);
        infectWithPower(map, width, height, x, y-1, power-1);
        infectWithPower(map, width, height, x+1, y, power-1);
        infectWithPower(map, width, height, x, y+1, power-1);

    }
    
}

int random(int seed, int n)
{
    if(n<=0)
    return seed;
    else
    {
        seed=seed*seed;
        seed=seed/100;
        seed=seed%10000;
        return random(seed,n-1);
    }
}

void infectWithProbability(char map[][MAX_SIZE], int width, int height, int x, int y, int threshold, int seed, int n=1)
{
        if(threshold>seed && n>1)   
            return;
        if(map[y][x]>=48 && map[y][x]<58)      //see if it is already numbers (by comparing to ascii code)
        {
            map[y][x]=(map[y][x]>n+48)? n+48:map[y][x];  
            //return;
        }
        
        if(map[y][x]=='p')  
        {    
            map[y][x]=n+48;
        }
        
        if(map[y][x]=='.')
            return;
        else
        {
            infectWithProbability(map, width, height, x-1, y, threshold, random(seed,1), n+1);
            infectWithProbability(map, width, height, x, y-1, threshold, random(seed,1), n+1);
            infectWithProbability(map, width, height, x+1, y, threshold, random(seed,1), n+1);
            infectWithProbability(map, width, height, x, y+1, threshold, random(seed,1), n+1);
        }
}

int main()
{
    cout << "Welcome to the infection simulator!" << endl;
    cout << "Which test case do you want to run?" << endl;
    int testCaseNumber = 0;
    cin >> testCaseNumber;

    cout << "Running test case " << testCaseNumber << "... If you do not see a complete output below, that could mean runtime errors happened (e.g. infinite recursion). Check your code carefully." << endl;

    if(testCaseNumber == 1)
    {
        int width = 6;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.', '.'},
            {'p', 'p', 'p', '.', 'p', '.'},
            {'.', 'p', '.', 'p', 'p', '.'},
            {'p', 'p', '.', '.', '.', 'p'},
            {'.', 'p', '.', '.', 'p', '.'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 2)
    {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.'},
            {'p', 'p', 'p', '.', 'p'},
            {'.', 'p', '.', 'p', 'p'},
            {'p', 'p', '.', '.', '.'},
            {'.', 'p', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 3)
    {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.'},
            {'p', 'p', 'p', '.', 'p'},
            {'.', 'p', '.', 'p', 'p'},
            {'p', 'p', '.', '.', '.'},
            {'.', 'p', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        cout << "#infected = " << infect(map, width, height, 1, 1) << endl;
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 4)
    {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.'},
            {'p', 'p', 'p', '.', 'p'},
            {'.', 'p', '.', 'p', 'p'},
            {'p', 'p', '.', '.', '.'},
            {'.', 'p', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infect(map, width, height, 1, 1); 
        //this test case is very similar to the previous test case
        //the only difference is that we do not output the return value of the infect function
        //this is to give partial credits to students who could only modify the map correctly
        //but not getting a correct return value
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 5)
    {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', '.', 'p', 'p'},
            {'p', 'p', 'p', '.', '.'},
            {'p', 'p', '.', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'},
            {'p', '.', '.', '.', '.'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        cout << "#infected = " << infect(map, width, height, 4, 5) << endl;
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 6)
    {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.'},
            {'p', 'p', 'p', '.', 'p'},
            {'.', 'p', '.', 'p', 'p'},
            {'p', 'p', '.', '.', '.'},
            {'.', 'p', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        cout << "#infected = " << infect(map, width, height, 0, 0) << endl;
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 7)
    {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.'},
            {'p', 'p', 'p', '.', 'v'},
            {'.', 'p', '.', 'v', 'v'},
            {'p', 'p', '.', '.', '.'},
            {'.', 'p', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        cout << "# of p = " << countCharacter(map, width, height, 'p') << endl;
        cout << "# of v = " << countCharacter(map, width, height, 'v') << endl;
        cout << "# of . = " << countCharacter(map, width, height, '.') << endl;
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 8)
    {
        int width = 8;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p', '.', '.', '.'},
            {'.', 'p', 'p', 'B', 'p', '.', '.', 'p'},
            {'.', '.', '.', '.', 'p', 'p', '.', 'p'},
            {'.', '.', '.', '.', 'p', '.', '.', '.'}
        };
        cout << "========================" << endl;
        cout << "getProtectionLevel at (3,2) = " << getProtectionLevel(map, width, height, 3, 2) << endl;
        cout << "getProtectionLevel at (2,2) = " << getProtectionLevel(map, width, height, 2, 2) << endl;
        cout << "getProtectionLevel at (4,2) = " << getProtectionLevel(map, width, height, 4, 2) << endl;
        cout << "getProtectionLevel at (3,1) = " << getProtectionLevel(map, width, height, 3, 1) << endl;
        cout << "getProtectionLevel at (3,3) = " << getProtectionLevel(map, width, height, 3, 3) << endl;
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 9)
    {
        int width = 8;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'C', '.', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p', '.', '.', '.'},
            {'.', 'p', 'A', 'B', 'p', '.', '.', 'p'},
            {'.', '.', '.', '.', 'p', 'p', '.', 'p'},
            {'.', '.', '.', '.', 'p', '.', '.', '.'}
        };
        cout << "========================" << endl;
        cout << "getProtectionLevel at (3,2) = " << getProtectionLevel(map, width, height, 3, 2) << endl;
        cout << "getProtectionLevel at (2,2) = " << getProtectionLevel(map, width, height, 2, 2) << endl;
        cout << "getProtectionLevel at (4,2) = " << getProtectionLevel(map, width, height, 4, 2) << endl;
        cout << "getProtectionLevel at (3,1) = " << getProtectionLevel(map, width, height, 3, 1) << endl;
        cout << "getProtectionLevel at (3,3) = " << getProtectionLevel(map, width, height, 3, 3) << endl;
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 10)
    {
        int width = 8;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p', '.', '.', '.'},
            {'.', 'p', 'p', 'p', 'p', '.', '.', 'p'},
            {'.', '.', '.', '.', 'p', 'p', '.', 'p'},
            {'.', '.', '.', '.', 'p', '.', '.', '.'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithPower(map, width, height, 1, 1, 3);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 11)
    {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithPower(map, width, height, 3, 3, 8);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 12)
    {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'C', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithPower(map, width, height, 3, 3, 8);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 13)
    {
        cout << "========================" << endl;
        cout << "random(1234, 1) = " << random(1234, 1) << endl;
        cout << "random(1234, 2) = " << random(1234, 2) << endl;
        cout << "random(1234, 3) = " << random(1234, 3) << endl;
        cout << "random(1234, 4) = " << random(1234, 4) << endl;
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 14)
    {
        cout << "========================" << endl;
        cout << "random(1001, 1) = " << random(1001, 1) << endl;
        cout << "random(1001, 2) = " << random(1001, 2) << endl;
        cout << "random(1001, 3) = " << random(1001, 3) << endl;
        cout << "random(1001, 4) = " << random(1001, 4) << endl;
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 15)
    {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithProbability(map, width, height, 4, 4, 3200, 1234);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 16)
    {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', '.', '.', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithProbability(map, width, height, 4, 4, 3200, 1234);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }


    //THE FOLLOWING TEST CASES WON'T BE GIVEN BEFORE THE DEADLINE
    
    else if(testCaseNumber == 17)
    {
        int width = MAX_SIZE;
        int height = MAX_SIZE;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 18)
    {
        int width = 1;
        int height = 1;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
            {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'p', '.', '.'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 19)
    {
        int width = 5;
        int height = 6;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.'},
            {'p', 'p', 'p', '.', 'p'},
            {'.', 'p', '.', 'p', 'p'},
            {'p', 'p', '.', '.', '.'},
            {'.', 'p', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        cout << "#infected = " << infect(map, width, height, 0, 0) << endl;
        cout << "#infected = " << infect(map, width, height, 4, 6) << endl;
        cout << "#infected = " << infect(map, width, height, 5, 5) << endl;
        cout << "#infected = " << infect(map, width, height, -1, 0) << endl;
        cout << "#infected = " << infect(map, width, height, 0, -1) << endl;
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 20)
    {
        int width = 5;
        int height = 1;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        cout << "#infected = " << infect(map, width, height, 2, 0) << endl;
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 21)
    {
        int width = 5;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', '.', 'p', 'p'},
            {'p', '.', 'p', '.', 'p'},
            {'p', 'p', '.', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        cout << "#infected = " << infect(map, width, height, 2, 2) << endl;
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 22)
    {
        int width = MAX_SIZE;
        int height = MAX_SIZE;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.', '.', 'p', '.', 'p', '.', 'v', 'v'},
            {'p', 'p', 'p', '.', 'v', '.', 'p', '.', 'p', '.', 'v', 'v'},
            {'.', 'p', '.', 'v', 'v', '.', 'p', '.', 'p', '.', 'v', 'v'},
            {'.', 'p', '.', 'v', 'v', '.', 'p', '.', 'p', '.', 'v', 'v'},
            {'.', 'p', '.', 'v', 'v', '.', 'p', '.', 'p', '.', 'v', 'v'},
            {'p', 'p', '.', '.', '.', '.', 'p', '.', 'p', '.', 'v', 'v'},
            {'.', 'p', '.', '.', 'p', '.', 'p', '.', 'p', '.', 'v', 'v'},
            {'.', 'p', '.', '.', 'p', '.', 'p', '.', 'p', '.', 'v', 'v'},
            {'.', 'p', '.', '.', 'p', '.', 'p', '.', 'p', '.', 'v', 'v'},
            {'.', 'p', '.', '.', 'p', '.', 'p', '.', 'p', '.', 'v', 'v'},
            {'.', 'p', '.', '.', 'p', '.', 'p', '.', 'p', '.', 'v', 'v'},
            {'p', 'p', 'p', 'p', 'p', '.', 'p', '.', 'p', '.', 'v', 'v'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        cout << "# of p = " << countCharacter(map, width, height, 'p') << endl;
        cout << "# of v = " << countCharacter(map, width, height, 'v') << endl;
        cout << "# of . = " << countCharacter(map, width, height, '.') << endl;
        cout << "# of A = " << countCharacter(map, width, height, 'A') << endl;
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 23)
    {
        int width = 5;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'E', '.', 'p'},
            {'p', 'p', 'p', '.', 'p'},
            {'p', 'p', 'D', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p'}
        };
        cout << "========================" << endl;
        for(int i=0;i<width;i++)
        {
            for(int j=0;j<height;j++)
            {
                cout << "getProtectionLevel at (" << i << "," << j << ") = " << getProtectionLevel(map, width, height, i, j) << endl;
            }
        }
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 24)
    {
        int width = 5;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'A', 'p', 'C', 'p'},
            {'B', 'p', 'E', 'p', 'I'},
            {'p', 'A', 'p', 'J', 'p'},
            {'C', 'p', 'D', 'p', 'G'},
            {'p', 'F', 'p', 'G', 'p'}
        };
        cout << "========================" << endl;
        for(int i=0;i<width;i++)
        {
            for(int j=0;j<height;j++)
            {
                cout << "getProtectionLevel at (" << i << "," << j << ") = " << getProtectionLevel(map, width, height, i, j) << endl;
            }
        }
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 25)
    {
        int width = 8;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', '.', '.', '.', 'p'},
            {'p', 'p', 'p', 'p', 'p', '.', '.', '.'},
            {'.', 'p', 'p', 'p', 'p', '.', '.', 'p'},
            {'.', '.', '.', '.', 'p', 'p', '.', 'p'},
            {'.', '.', '.', '.', 'p', '.', '.', '.'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithPower(map, width, height, 0, 0, 4);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 26)
    {
        int width = 8;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', '.', 'p', '.'},
            {'.', 'p', 'p', 'p', 'p', '.', 'p', 'p'},
            {'.', '.', '.', '.', 'p', 'p', '.', 'p'},
            {'.', '.', '.', '.', 'p', '.', 'p', '.'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithPower(map, width, height, 4, 3, 6);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 27)
    {
        int width = 8;
        int height = 5;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'.', 'p', '.', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', '.', 'p', 'p'},
            {'.', 'p', 'p', 'p', 'p', '.', 'p', '.'},
            {'p', '.', '.', '.', 'p', 'p', '.', 'p'},
            {'p', 'p', 'p', '.', 'p', '.', 'p', '.'}
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithPower(map, width, height, 4, 3, 9);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 28)
    {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'A', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithPower(map, width, height, -1, 0, 8);
        infectWithPower(map, width, height, 0, -1, 8);
        infectWithPower(map, width, height, 8, 7, 8);
        infectWithPower(map, width, height, 7, 8, 8);
        infectWithPower(map, width, height, 0, 0, 8);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 29)
    {
        int width = 4;
        int height = 4;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithPower(map, width, height, 2, 2, 9);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 30)
    {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'A', 'p', 'B', 'p', 'C', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'D', 'p', 'E', 'p', 'F', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'G', 'p', 'H', 'p', 'I', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithPower(map, width, height, 4, 2, 9);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 31)
    {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'A', 'p', 'B', 'p', 'B', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'D', 'p', 'E', 'p', 'F', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'A', 'p', 'H', 'p', 'I', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithPower(map, width, height, 3, 4, 9);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 32)
    {
        cout << "========================" << endl;
        cout << "random(1234, 1) = " << random(1234, 1) << endl;
        cout << "random(1234, 2) = " << random(1234, 2) << endl;
        cout << "random(1234, 3) = " << random(1234, 3) << endl;
        cout << "random(1234, 4) = " << random(1234, 4) << endl;
        cout << "random(1234, 5) = " << random(1234, 5) << endl;
        cout << "random(1234, 6) = " << random(1234, 6) << endl;
        cout << "random(1234, 7) = " << random(1234, 7) << endl;
        cout << "random(1234, 8) = " << random(1234, 8) << endl;
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 33)
    {
        cout << "========================" << endl;
        cout << "random(2345, 1) = " << random(2345, 1) << endl;
        cout << "random(2345, 2) = " << random(2345, 2) << endl;
        cout << "random(2345, 3) = " << random(2345, 3) << endl;
        cout << "random(2345, 4) = " << random(2345, 4) << endl;
        cout << "random(2345, 5) = " << random(2345, 5) << endl;
        cout << "random(2345, 6) = " << random(2345, 6) << endl;
        cout << "random(2345, 7) = " << random(2345, 7) << endl;
        cout << "random(2345, 8) = " << random(2345, 8) << endl;
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 34)
    {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithProbability(map, width, height, 4, 4, 3215, 1234);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 35)
    {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', '.', '.', 'p', 'p'},
            {'p', 'p', '.', 'p', 'p', '.', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithProbability(map, width, height, 4, 4, 80, 2345);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 36)
    {
        int width = 8;
        int height = 8;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'A', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithProbability(map, width, height, -1, 0, 2000, 1234);
        infectWithProbability(map, width, height, 0, -1, 2000, 1234);
        infectWithProbability(map, width, height, 8, 7, 2000, 1234);
        infectWithProbability(map, width, height, 7, 8, 2000, 1234);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }
    else if(testCaseNumber == 37)
    {
        int width = 4;
        int height = 4;
        char map[MAX_SIZE][MAX_SIZE] = {
            {'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', 'p'},
            {'p', 'p', 'p', '.'},
            {'p', 'p', '.', 'p'},
        };
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
        infectWithProbability(map, width, height, 1, 1, 80, 2345);
        cout << "========================" << endl;
        printMap(map, width, height);
        cout << "========================" << endl;
    }

    return 0;
}
