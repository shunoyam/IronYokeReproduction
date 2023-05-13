
#pragma once
#include"../../include.hpp"
using namespace std;

class coil{//filament loop coil
private:
  double _r;
  double _z;
  double _I;
public:
  coil();
  coil(double I, double r, double z);
  //setter
  void set(double I, double r, double z);
  void setI(double I);
  void setr(double r);
  void setz(double z);
  //getter
  double I();
  double r();
  double z();
  
  TVector3 ResponseElement(TVector3 pos_MFEP);
  //element of response matrix A
  TVector3 b(TVector3 pos_MFEP);
  double flux(TVector3 pos_MFEP);//magnetic flux(scalar)
  //for showing magnetic field uniformity
};



















