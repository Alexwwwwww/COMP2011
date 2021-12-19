#include <cstring>
#include "location.h"

using namespace std;

class city{
  private:
    location l;
    int population;
    char* name;
    

  public:
    //constructor 

    city(){}

    city(const double _x, const double _y, int _population, const char* _name){
        set(_x,_y,_population,_name);
    }

    ~city(){
        delete [] name;
    }

    //get
    location get_location(){ return l;}
    int get_population() const { return population; }
    char* getName(){return name;}

    //set
    void set(const double _x, const double _y, int _population, const char* _name){
        l.set(_x,_y);
        population = _population;
        name = new char [strlen(_name)+1]; 
        strcpy(name, _name);
    }
    
    void copy(const city& c) {
        cout<<"Copy"<<endl;
        set(c.l.get_x(), c.l.get_y(), c.population, c.name); 
    }

    void print() const{ 
        cout << "City " << name << " is located at "; 
        l.print();
        cout << "and has a population of " <<population<< " people"<< endl; 
    }

    double distance(const city& c) {
        return l.distance(c.l);
    }

};