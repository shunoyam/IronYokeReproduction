
#include"../../include.hpp"
using namespace std;

void Bfield::setB(TVector3 __B)
{
  this->_B=__B;
  double x=this->_MFEP.x();
  double y=this->_MFEP.y();
  double rho=sqrt(x*x+y*y);
  double Br=(__B.x()*x+__B.y()*y)/rho;
  this->_Br=Br;
}

void Bfield::setBz(double _Bz)
{
  this->_B.SetZ(_Bz);
}

void Bfield::setMFEP(TVector3 __MFEP)
{
  this->_MFEP=__MFEP;
}

void Bfield::settheta(double theta)
{
  this->_theta=theta;
}

void Bfield::setflux(double flux)
{
  this->_flux=flux;
}

TVector3 Bfield::B()
{
  TVector3 __B=this->_B;
  return __B;  
}

double Bfield::Bz()
{
  double _Bz=this->_B.z();
  return _Bz;  
}

double Bfield::Br()
{
  return this->_Br;
}

TVector3 Bfield::MFEP()
{
  TVector3 __MFEP=this->_MFEP;
  return __MFEP;
}

double Bfield::theta()
{
  double _theta=this->_theta;
  while(TMath::Pi()<_theta)
    {
      _theta-=TMath::TwoPi();
    }
  while(_theta<-TMath::Pi())
    {
      _theta+=TMath::TwoPi();
    }
  return _theta;
}

double Bfield::flux()
{
  double flux=this->_flux;
  return flux;
}

void Bfield::DirectionBlinding()
{
  double magnitude=sqrt(this->_B.Mag2());
  this->_B.SetXYZ(0.,0.,magnitude);
}

void Bfield::SetChannel(int channel)
{
  _channel=channel;
}

int Bfield::channel()
{
  return _channel;
}

string Bfield::UpperOrLower()
{
  if(_channel==0 or _channel==1 or _channel==2)
    {
      return "lower";
    }
  if(_channel==3 or _channel==4)
    {
      return "upper";
    }
  return "error";
}




