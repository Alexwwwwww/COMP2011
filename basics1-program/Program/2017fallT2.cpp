#include <iostream>   
using namespace std;   
   
int n = 10;   
   
void function(double a, int b, int& n) {   
   for (n = 1; n < 2; n++) {   
      double& n = a;   
      if (a > b) {   
              int& n = b;   
         n++;   
      } else   
         n = b;   
      n++;   
   }   
   n = a + b;   
   cout << "fn1"<< endl;   
}   
   
void function(double x, double y, int& number);   
   
int main() {   
   function(3.0, 3.3, n);   
   cout << n << endl;   
   return 0;   
}   
   
void function(double a, double b, int& n)  {   
   for (n = 1; n < 2; n++) {   //the n in the parameter list, n0
      double& n = a;  //n1 
      if (a > b) {   
         double& n = b;   //another new n2
         n++;   
      } else   
         n = b;   //n1
      n++;   //n1
   }   
   n = a + b;   //n0
   cout << "fn2" <<endl;   
}   