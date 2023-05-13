

#include"../src/include.hpp"
using namespace std;

//These functions are used to calculate magnetic field by current in arc.
//If you can use C++17, remove comment-outs in the first lines
//and add comment-out to line  "double value = nan("");"

double ellint_3_lib(double m,double alpha,double phase){
  double value = ellint_3(m, alpha, phase);
  //C++14 does not support ellint_3() function
  //  double value = nan("");
  return value;
}

double ellint_1_lib(double m,double phase)
{
  double value = ellint_1(m, phase);
  //C++14 does not support ellint_1() function
  //  double value = nan("");
  return value;
}

double legendre_lib(double n, double x)
{
  double value=legendre(n, x);
  //C++14 does not support legendre() function
  //  double value = nan("");
  return value;
}







