#include <iostream>
using namespace std;
const int MAX_SIZE=12;
void infectWithProbability(char map[][MAX_SIZE], int width, int height, int x, int y, int threshold, int seed, int n=1)
{       
        if(n==4)
        return;
        if(map[y][x]>=48 && map[y][x]<58)
        {
            map[y][x]=(map[y][x]>n+48)? n+48:map[y][x];
            return;
        }
        else if(map[y][x]=='.' )
            return;
        else
        {
            if(map[y][x]=='p')
                map[y][x]=n+48;
            if(threshold>seed && n>1)   
                return;
            
            infectWithProbability(map, width, height, x-1, y, threshold, seed, n+1);
            infectWithProbability(map, width, height, x, y-1, threshold, seed, n+1);
            infectWithProbability(map, width, height, x+1, y, threshold, seed, n+1);
            infectWithProbability(map, width, height, x, y+1, threshold, seed, n+1);
        }
    
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
int main()
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

    };
//cout << "# of p = " << countCharacter(map, width, height, 'p') << endl;
//cout << "# of v = " << countCharacter(map, width, height, 'v') << endl;
//cout << "# of . = " << countCharacter(map, width, height, '.') << endl;

}