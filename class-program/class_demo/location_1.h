#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>

using namespace std;

class location{
  private:
    double x;
    double y;

  public:
    //constructor 

    location(){
        x=0.0; y=0.0;
    }
    
    location(const double _x, const double _y){
        set(_x,_y);
    }

    location(location& l){
        set(l.x,l.y);
    }

    //get
    double get_x() const { return x; }
    double get_y() const { return y; }

    //set
    void set(const double _x, const double _y){
        if(_x >= 0 && _y>=0){
            x = _x; y=_y;
        }else{
            x = -_x; y= -_y;
        }
    }

    void setRandom(){
        x = ((double)rand())/RAND_MAX;
        x = x*100.0;
        y = ((double)rand())/RAND_MAX;
        y = y*100;
    }

    void setRandom(const double min, const double max){
        x = ((double)rand())/RAND_MAX;
        x = min + x*(max-min);
        y = ((double)rand())/RAND_MAX;
        y = min+y*(max-min);
    }

    void setRandom(const double xmin, const double xmax, const double ymin, const double ymax){
        x = ((double)rand())/RAND_MAX;
        x = xmin + x*(xmax-xmin);
        y = ((double)rand())/RAND_MAX;
        y = ymin+y*(ymax-ymin);
    }
    
    void copy(const location& l) {
        set(l.x, l.y); 
    }

    void print() const{ 
        cout << "(" << x << ", " << y << ") " ; 
    }

    double distance(const location& l) {
        double xdiff = x - l.x;
        double ydiff = y - l.y;
        return sqrt(xdiff*xdiff + ydiff*ydiff);
    }
    
    double distance(const location& l, const double _x, const double _y) {
        double xdiff = _x - l.x; //cout<<xdiff<<", "<<xdiff*xdiff<<"\t";
        double ydiff = _y - l.y; //cout<<ydiff<<", "<<ydiff*ydiff<<"\t";
        double result = sqrt((xdiff*xdiff) + (ydiff*ydiff));
        //cout<<result<<endl;
        return result;
    }

    location* closest_location(location locs[], int len){
        int pos=0;
        double dist = distance(locs[0],x,y);
        for(int i=1;i<len;i++){
            if(distance(locs[i],x,y)<dist){
                dist = distance(locs[i],x,y);
                pos = i;
            }
        }
        cout<<&locs[pos]<<endl;
        return &locs[pos];
    }

};
