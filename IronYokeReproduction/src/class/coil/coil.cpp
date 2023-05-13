

#include"../../include.hpp"

coil::coil(){ 
}

coil::coil(double I, double r, double z){
  coil::set(I, r, z);
}

//setter
void coil::set(double I, double r, double z){
  coil::setI(I);
  coil::setr(r);
  coil::setz(z);
}

void coil::setI(double I){
  this->_I = I;
}

void coil::setr(double r){
  if(r<0.){
    cout << "coil radius must be positive" << endl;
    return;
  }
  this->_r = r;
}

void coil::setz(double z){
  this->_z = z;
}

//getter
double coil::I(){
  return this->_I;
}

double coil::r(){
  return this->_r;
}

double coil::z(){
  return this->_z;
}

TVector3 coil::ResponseElement(TVector3 pos_MFEP){
  //think with cylindrical coordinate
  double rho = hypot(pos_MFEP.x(), pos_MFEP.y());
  double radi = coil::r();
  double  z_delta = pos_MFEP.z()-this->_z;
  //exception handling for magnetic field on the z axis
  if (rho<1.e-8)
    {
      double dominator = 2*pow(pow(radi, 2)+pow(z_delta, 2), 1.5);
      double Response_element_z = mu_0*pow(radi, 2)/dominator;
      TVector3 _ResponseElement(0., 0., Response_element_z);
      return _ResponseElement;
    }
  //calculate a_z and a_r by polynomial approximation for elliptic integral
  double k = (4.*radi*rho)/(pow(radi+rho, 2)+pow(z_delta, 2));
  double coef1_z = mu_0*sqrt(k)/(4.*TMath::Pi()*sqrt(radi*rho)); 
  double coef2_z_nume = (pow(radi, 2)-pow(rho, 2)-pow(z_delta, 2));
  double coef2_z_domi = (pow(radi-rho, 2)+pow(z_delta, 2));
  double coef2_z = coef2_z_nume/coef2_z_domi;
  double a_z = coef1_z*(coef2_z*elliptic_integral_2(k)+elliptic_integral_1(k)); 
  double coef1_r = mu_0*z_delta*sqrt(k)/(4.*TMath::Pi()*rho*sqrt(radi*rho));
  double coef2_r = (pow(radi, 2)+pow(rho, 2)+pow(z_delta, 2))/(pow(radi-rho, 2)+pow(z_delta, 2));
  double a_r = coef1_r*(coef2_r*elliptic_integral_2(k)-elliptic_integral_1(k));
 
  //from a_z and a_r to 3D
  TVector3 _Response_element(a_r*pos_MFEP.x()/rho, a_r*pos_MFEP.y()/rho, a_z);
  return _Response_element;
}

TVector3 coil::b(TVector3 pos_MFEP)
{
  auto ResponseElement = coil::ResponseElement(pos_MFEP);
  TVector3 _B = this->_I * ResponseElement;
  return _B;
}

double coil::flux (TVector3 pos_MFEP)
{
  pos_MFEP.SetZ(pos_MFEP.z()-this->_z);
  double rho = hypot(pos_MFEP.x(), pos_MFEP.y());
  if(rho == 0.)
    {
      return 0.;
    }
  double Delta = hypot(rho+this->_r, pos_MFEP.z());
  double k = 4. * this->_r * rho / pow(Delta, 2.); 
  double coef = mu_0 * this->_I * this->_r / (TMath::Pi()*Delta*k);
  double Aphi = -coef*((k-2.)*elliptic_integral_1(k)+2.*elliptic_integral_2(k));
  double flux = 2.*TMath::Pi()*rho*Aphi;
  return flux;
}

