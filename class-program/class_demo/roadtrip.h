#include "city.h"

using namespace std;

class roadtrip{

    private:
        city* trip;
        int hops;

        void init_trip(){
            double x,y;
            char name[20];
            int population;
            cout<<"Enter the details of the "<<hops<< " cities"<<endl;
            for(int i=0;i<hops;i++){
                cout<<"City "<<(i+1)<<": "<<endl;
                cout<<"Enter city location (x y): ";
                cin>>x>>y;
                cout<<"Enter city name: ";
                cin>>name;
                cout<<"Enter population: ";
                cin>>population;
                trip[i].set(x,y,population,name);
                cout<<endl<<endl;
            }
        }

        void init_random_trip(){
            double x,y;
            char name[7] = {'c','i','t','y','_','x','\0'};
            char city_index = '0';
            int population;
            for(int i=0;i<hops;i++){
                x = 100*(((double)rand())/RAND_MAX);
                y = 100*(((double)rand())/RAND_MAX);
                name[5] = city_index+i;
                population = 100 + rand()%100;
                trip[i].set(x,y,population,name);
            }
        }

    public:
        roadtrip(int _hops=10){
            hops = _hops;
            trip = new city[hops];
            init_trip();
        }

        roadtrip(char c){
            if( c=='r' || c=='R'){
                srand(time(0));
                hops = 2 + rand()%9;
                trip = new city[hops];
                init_random_trip();
            }else{
                hops = 10;
                trip = new city[hops];
                init_trip();
            }
        }

        int potential_meets(){
            int sum=0;
            for(int i=0;i<hops;i++){
                sum+=trip[i].get_population();
            }
            return sum;
        }

        double total_distance(){
            double sum=0;
            for(int i=0;i<hops-1;i++){
                sum+=trip[i].distance(trip[i+1]);
            }
            return sum;
        }

        void print(){
            for(int i=0;i<hops;i++){
                trip[i].print();
                cout<<endl;
            }
        }

};