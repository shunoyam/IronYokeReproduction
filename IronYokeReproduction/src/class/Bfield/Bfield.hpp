

#pragma once

#include"../../include.hpp"

class Bfield
{
 private:
  TVector3 _B;
  TVector3 _MFEP;
  double _theta;
  double _Br;
public:
  void setB(TVector3 B);
  void setBz(double Bz);
  void setMFEP(TVector3 MFEP);
  void settheta(double theta);
  TVector3 B();
  double Bz();
  double Br();
  TVector3 MFEP();
  double theta();
  //get rotational angle of MFEP
  void DirectionBlinding();
};

