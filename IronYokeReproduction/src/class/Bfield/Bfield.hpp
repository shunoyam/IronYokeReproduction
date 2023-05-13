

#pragma once

#include"../../include.hpp"

class Bfield
{
 private:
  TVector3 _B;
  TVector3 _MFEP;
  double _flux;
  double _theta;
  double _Br;
  int _channel;
public:
  void setB(TVector3 B);
  void setBz(double Bz);
  void setMFEP(TVector3 MFEP);
  void settheta(double theta);
  void setflux(double flux);
  void SetChannel(int channel);
  TVector3 B();
  double Bz();
  double Br();
  TVector3 MFEP();
  double theta();
  //get rotational angle of MFEP
  double flux();
  void DirectionBlinding();
  int channel();
  string UpperOrLower();
};

