
#ifndef _IN_MOREGAUSS
#define _IN_MOREGAUSS

#include"../../src/include.hpp"
using namespace std;

void gauss_mesh();

void challenge_gauss(const char* ofn,int n,TVector3 mfep,double CurrentDensity,
                     double center_r,double width_r,
                     double width_z);

void challenge_mesh(const char* ofn,int n,TVector3 mfep,double CurrentDensity,
                    double center_r,double width_r,
                    double width_z);



#endif
