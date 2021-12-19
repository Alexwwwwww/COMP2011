#include "city.h"

int main()	
{
    city c1(1,2,100,"city 1");
    c1.print();

    city c2(1,4,1000,"city 2");
    c2.print();

    city c3;
    c3.print();
    cout<<c1.distance(c2)<<endl;

    return 0;
}