
#include"../../include.hpp"
using namespace std;
using namespace ROOT::Math;

Bs::Bs(){
}

Bs::Bs(string path_2dFieldMapData){
  Bs::Read2dFieldMap(path_2dFieldMapData);
}

void Bs::Read3dFieldMap(string ifn_dat,string unit_pos,string unit_B){
  ifstream InputFile(ifn_dat.c_str());
  double x,y,z,bx,by,bz;
  int line_header=7;//to skip header in input file
  int i_line = 0;
  while(InputFile >> x>>y>>z>>bx>>by>>bz){
    if(i_line < line_header){
      continue;
    }
    TVector3 pos(x,y,z);
    TVector3 b(bx,by,bz);
    if(unit_pos=="cm"){
      pos*=1.e-2;
    }
    if(unit_B=="gauss"){
      b*=1.e-4;
    }
    Bs::push_back(pos,b);
  }
}

Bs::operator vector<Bfield>(){
  return this->_B;
}

int Bs::MFEPs(){
  return this->_B.size();
}

Bfield Bs::at(int index)
{
  int Bs_size=this->_B.size();
  if(Bs_size<index){
      cout<<"error :Check the size of Bs"<<endl;
      abort;
    }
  Bfield __B= this->_B[index];
  return __B;
}

void Bs::push_back(TVector3 pos,TVector3 magneticfield,double phi)
{
  Bfield B_new;
  B_new.setB(magneticfield);
  B_new.setMFEP(pos);
  B_new.settheta(phi);
  this->_B.push_back(B_new);
}

double Bs::average()
{
  vector<Bfield> B_TG=this->_B;
  vector<double> Bz;
  for(Bfield B:B_TG)
    {
      Bz.push_back(B.Bz());
    }
  double average=Average(Bz);
  return average;
}

void Bs::subtract(cb coils)
{
  int n_MFEP=this->_B.size();
  if(n_MFEP==0)
    {
      puts("MFEP has been not set yet.");
      return;
    }
  TVector3 tempB_coil,B_TG_new,mfep;
  vector<double> bz_vec,br_vec;
  for(int i_MFEP=0;i_MFEP<n_MFEP;i_MFEP++)
    {
      mfep=this->_B[i_MFEP].MFEP();
      tempB_coil=coils.B(mfep);
      B_TG_new=this->_B[i_MFEP].B()-tempB_coil;
      this->_B[i_MFEP].setB(B_TG_new);
      bz_vec.push_back(B_TG_new.z());
      br_vec.push_back(this->_B[i_MFEP].Br());
    }
}

void Bs::addBs(Bs Bs_added,Bs Bs_add,double coefficient_added,double coefficient_add)
{
  Bs::clear();
  int size_added=Bs_added.MFEPs();
  int size_add=Bs_add.MFEPs();
  Bs Bs_new;
  TVector3 B_new,B_add,B_added;
  if(size_add!=size_added)
    {
      cout<<"cannot operate addition to objects with defferent sizes"<<endl;
      return;
    }
  //It costs much time to check all MFEPs are exactly same.

  for(int i_mfep=0;i_mfep<size_add;i_mfep++)
    {
      B_added=((vector<Bfield>)Bs_added)[i_mfep].B();
      B_add=((vector<Bfield>)Bs_add)[i_mfep].B();
      B_new=B_add*coefficient_add+B_added*coefficient_added;
      this->_B[i_mfep].setB(B_new);
    }
}

void Bs::add_coil(cb coils,double factor)
{
  double flux_add,flux_old,rho;
  TVector3 B_add,B_old,B_new,pos;
  for(int i_MFEP=0;i_MFEP< this->_B.size();i_MFEP++)
    {
      pos=this->_B[i_MFEP].MFEP();
      flux_old=this->_B[i_MFEP].flux();
      flux_add=coils.Flux(pos);
      B_add=coils.B(pos);
      B_add*=factor;
      B_old=this->_B[i_MFEP].B();
      this->_B[i_MFEP].setflux(flux_add+flux_old);
      B_new=B_add+B_old;
      this->_B[i_MFEP].setB(B_new);
    }
}

void Bs::clear()
{
  for(int i_MFEP=0;i_MFEP< this->_B.size();i_MFEP++)
    {
      this->_B[i_MFEP].setB(TVector3(0., 0., 0.));
      this->_B[i_MFEP].setflux(0.);
    }
}

Eigen::VectorXd Bs::Bs_eigen(string element)
{
  int n_MFEP=this->_B.size();
  Eigen::VectorXd B_eigen(n_MFEP);
  for(int i_MFEP=0;i_MFEP<n_MFEP;i_MFEP++)
    {
      TVector3 B=this->_B[i_MFEP].B();
      if(element=="Bx")
        {
          B_eigen(i_MFEP)=B.x();
        }
      if(element=="Bz")
        {
          B_eigen(i_MFEP)=B.z();
        }
      if(element=="B")
        {
          B_eigen(i_MFEP)=B.Mag()*(B.z()/abs(B.z()));
        }
      if(element=="Br")
        {
          TVector3 MFEP=this->_B[i_MFEP].MFEP();
          TVector3 RadialDirection(MFEP.x(),MFEP.y(),0.);
          double br=B.Dot(RadialDirection);
          B_eigen(i_MFEP)=br;
        }
    }
  return B_eigen;
}

void Bs::Eigen_Bs(Eigen::VectorXd B_eigen)
{
  double Bz;
  int n_Eigen=B_eigen.rows();
  int n_Bs=this->_B.size();
  if(n_Eigen!=n_Bs)
    {
      puts("size of Eigen::vector and Bs is different");
    }
  for(int i_MFEP=0;i_MFEP<n_Eigen;i_MFEP++)
    {
      Bz=B_eigen(i_MFEP);
      TVector3 B(0.,0.,Bz);
      this->_B[i_MFEP].setB(B);
    }
}

Bs::operator vector<double>()
{
  vector<double> _Bs_vec;
  double Bz;

  for(Bfield B:this->_B)
    {
      Bz=B.Bz();
      _Bs_vec.push_back(Bz);
    }
  return _Bs_vec;
}

void Bs::Read2dFieldMap(string path_to_FieldMapFile)
{
  ifstream InputFile(path_to_FieldMapFile.c_str());
  if(InputFile.fail())
    {
      puts("MFEP data was not found.");
      abort;
    }
  double x, y=0., z;
  double Br, By=0., Bz;

  while(InputFile >> x >> z >> Bz >> Br)
    {
      // if(x/100 < 5.e-2)
      //   {
      //     puts("hello");
      //     continue;
      //   }
      TVector3 pos(x/100.,y/100.,z/100.);
      TVector3 B(Br/1.e4,By,Bz/1.e4);
      Bs::push_back(pos, B);
    }
}

void Bs::DirectionBlinding()
{
  for(Bfield &_b:this->_B)
    {
      _b.DirectionBlinding();
    }
}

void Bs::out(const char* ofn_dat){
  ofstream OutputFile(ofn_dat);
  for(Bfield b:this->_B)
    {
      auto mfep=b.MFEP();
      auto B=b.B();
      OutputFile<<mfep.x()<<"\t"<<mfep.y()<<"\t"<<mfep.z()<<"\t";
      OutputFile<<B.x()<<"\t"<<B.y()<<"\t"<<B.z()<<endl;
    }
}

void Bs::push_back(TVector3 mfep,int channel,double theta,TVector3 B)
{
  Bfield B_new;
  B_new.setB(B);
  B_new.setMFEP(mfep);
  B_new.settheta(theta);
  B_new.SetChannel(channel);
  this->_B.push_back(B_new);  
}

double Bs::max(string element){
  vector<double> list;
  for(Bfield b: this->_B){
    double value;
    if(element=="|B|"){
      value = b.B().Mag();
    }
    else if(element=="Bz"){
      value = b.Bz();
    }
    else{
      cout << "argument " << element << " is invalid" << endl;
      return nan("");
    }
    list.push_back(value);
  }
  double MaxValue = *max_element(list.begin(), list.end());
  return MaxValue;
}









