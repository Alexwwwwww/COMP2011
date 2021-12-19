#include "location.h"

int main()	
{
    srand(time(0));
    location l1;
    l1.set(1.0,1.0);
    
    location l2; 
    l2 = l1;
    location l3(l1);
    //location l4(2.0,5.0);

    //l1.print();
    //l2.print();
    //l3.print();
    //l4.print();

    
    
    //cout<<l1.get_x()<<", "<<l1.get_y()<<endl;

    location l4;
    l4.setRandom();
    l4.print();

    
    double x = l1.distance(l4);
    cout<<x<<endl;
    /* 
    

    location locs [3];
    for(int i=0;i<sizeof(locs)/sizeof(location);i++){
        locs[i].setRandom();
        locs[i].print();
        cout<<&locs[i]<<endl;
    }
    cout<<endl<<endl;
    
    
    location* closest;
    closest = l1.closest_location(locs,3);
    cout<<closest<<endl;
    
    (*closest).print();
    closest -> print();
    */
    return 0; 
    
} 