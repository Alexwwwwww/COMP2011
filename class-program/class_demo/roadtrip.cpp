#include "roadtrip.h"

int main()	
{
    roadtrip r('r');
    r.print();
    cout<<"You will meet "<<r.potential_meets()<<" people!!!"<<endl;
    cout<<"The total distance of your trip is: "<<r.total_distance()<<"!!!"<<endl;

    return 0;
}